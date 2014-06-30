// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/TypeConv/TypeConvGraph.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/CallTargets/ExprTarget.hpp"
#include "LikeMagic/Utility/TupleForEach.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"
#include "LikeMagic/CallTargets/DeleterCallTarget.hpp"

#include <set>
#include <map>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

namespace LM
{
    void create_type_info_cache();
    void delete_type_info_cache();
}

using namespace LM;

namespace LM {

TypeSystem::~TypeSystem()
{
}

class TypeSystemInstance : private TypeSystem
{
private:
    TypeSystemInstance();
    friend LIKEMAGIC_API TypeSystem* create_type_system();

    boost::unordered_map<std::size_t, TypeMirror*> classes;
    TypeMirror* unknown_class;
    TypeConvGraph conv_graph;
    TypeMirror* global_namespace_;

    void add_ptr_convs(TypeIndex index)
    {
        TypeInfo bare = index.get_info().class_type();
        //add_conv_track<void>(bare);
        //add_conv_track<void const>(bare.as_const_value());

        auto bottom_ptr_type = create_type_mirror("BottomPtr", size_t(0), create_bottom_ptr_type_index(), type_system->global_namespace().get_class_type());
        type_system->add_class(create_bottom_ptr_type_index(), bottom_ptr_type, type_system->global_namespace());

        // allow unsafe_ptr_cast to convert to any type and nil (NULL) to any pointer type
        add_nochange_conv(create_bottom_ptr_type_info(), bare.as_ptr_to_nonconst(), "bottom ptr unsafe cast to any ptr");
        add_nochange_conv(create_bottom_ptr_type_info(), bare.as_ptr_to_const(), "bottom ptr unsafe cast to any const ptr");

        // allow any ptr to be converted to void* or void const*
        add_nochange_conv(bare.as_ptr_to_nonconst(), TypId<void*>::restricted().get_info(), "any ptr to void ptr");
        add_nochange_conv(bare.as_ptr_to_const(), TypId<void const*>::restricted().get_info(), "any ptr to const void ptr");
    }

    void add_nochange_conv(TypeInfo from, TypeInfo to, std::string conv_name)
    {
        if (!(get_index(from) == get_index(to)))
            conv_graph.add_conv(get_index(from), get_index(to), new NoChangeConv(conv_name));
    }

    template <typename From, typename To>
    void add_static_cast_conv(TypeInfo from, TypeInfo to)
    {
        conv_graph.add_conv(get_index(from), get_index(to), new StaticCastConv<From, To>(from, to));
    }

    // Don't allow accidently making copies of this class
    TypeSystemInstance(TypeSystem const&) = delete;
    TypeSystem& operator =(TypeSystem const&) = delete;

    void add_conv(TypeInfo from_info, TypeInfo to_info);
    void add_common_conversions(TypeIndex type);

public:

    virtual ~TypeSystemInstance();
    virtual TypeMirror* get_class(TypeIndex type) const;
    virtual void add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_);
    virtual void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual bool has_direct_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual TypeMirror& global_namespace() const;
    virtual TypeMirror const* get_namespace(std::string full_name) const;
    virtual bool has_type(TypeIndex type) const;
    virtual std::vector<TypeIndex> list_class_types() const;
};

    LIKEMAGIC_API TypeSystem* create_type_system() { return new TypeSystemInstance(); }
    LIKEMAGIC_API TypeSystem* type_system = NULL;
}


TypeSystemInstance::TypeSystemInstance()
{
    create_type_info_cache();

    TypeIndex ns_type = create_namespace_type_index("");
    this->global_namespace_ = create_type_mirror("", size_t(0), ns_type, ns_type);
    this->classes[ns_type.get_id()] = this->global_namespace_;

    // Allow conversions from nil to any pointer.
    TypeIndex nil_expr_type = create_bottom_ptr_type_index();
    this->conv_graph.add_type(nil_expr_type);
}

TypeSystemInstance::~TypeSystemInstance()
{
    for (auto it=this->classes.begin(); it != this->classes.end(); it++)
    {
        delete it->second;
    }
    delete_type_info_cache();
}

TypeMirror& TypeSystemInstance::global_namespace() const
{
    return *(this->global_namespace_);
}

void TypeSystemInstance::add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_)
{
    TypeIndex class_index = get_class_index(index);
    TypeInfo class_info = class_index.get_info();
    TypeInfo ptr_to_nonconst = class_info.as_ptr_to_nonconst();
    TypeInfo ptr_to_const = class_info.as_ptr_to_const();
    TypeInfo ref_to_nonconst = class_info.as_ref_to_nonconst();
    TypeInfo ref_to_const = class_info.as_ref_to_const();
    TypeInfo const_value = class_info.as_const_value();
    TypeInfo nonconst_value = class_info.as_nonconst_value();

    // Add conversion to delegate type so that delegate call targets will work.
    add_conv(ref_to_nonconst.as_restricted(), TypId<LM::Delegate&>::restricted().get_info());
    add_conv(ref_to_nonconst.as_restricted(), TypId<LM::Delegate const&>::restricted().get_info());
    add_conv(ref_to_const.as_restricted(), TypId<LM::Delegate const&>::restricted().get_info());
    add_conv(nonconst_value.as_restricted(), TypId<LM::Delegate&>::restricted().get_info());
    add_conv(nonconst_value.as_restricted(), TypId<LM::Delegate const&>::restricted().get_info());
    add_conv(const_value.as_restricted(), TypId<LM::Delegate const&>::restricted().get_info());

    add_common_conversions(class_index);

    this->classes[class_index.get_id()] = class_ptr;

    auto deleter_target = new DeleterCallTarget();
    class_ptr->add_method("delete", deleter_target);

    ExprPtr class_expr = create_expr(nullptr, class_index);

    // TODO:  Create a "bool is_class_expr" field for expr.
    class_expr->set_disable_to_script(true);

    namespace_.add_method(
        class_ptr->get_class_name(), new LM::ExprTarget(
            class_expr));
}

ExprPtr TypeSystemInstance::try_conv(ExprPtr from_expr, TypeIndex to_type) const
{
    try
    {
        return this->conv_graph.wrap_expr(from_expr, from_expr->get_type(), to_type);
    }
    catch (std::logic_error const& le)
    {
        throw std::logic_error(le.what() + std::string(" (try_conv error, from expression was ") + from_expr->description() + ")");
    }
}

bool TypeSystemInstance::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return this->conv_graph.has_conv(from_type, to_type);
}

bool TypeSystemInstance::has_type(TypeIndex type) const
{
    return this->conv_graph.has_type(type);
}

TypeMirror* TypeSystemInstance::get_class(TypeIndex type) const
{
    TypeIndex class_type = get_class_index(type);
    auto iter = this->classes.find(class_type.get_id());
    if (iter != this->classes.end())
        return iter->second;
    else
        return nullptr;
}

bool TypeSystemInstance::has_direct_conv(TypeIndex  from_type, TypeIndex to_type) const
{
    return conv_graph.has_direct_conv(from_type, to_type);
}

void TypeSystemInstance::add_converter_simple(TypeIndex from_type, TypeIndex to_type, p_conv_t conv)
{
    if (from_type.get_info().is_restricted)
    {
        stringstream msg;
        msg << "add_converter_simple error from_type is restricted " << from_type.description() << " " << from_type.get_id()
            << " to " << to_type.description() << " " << to_type.get_id() << " conv='" << conv->description() << "'";
        cout << msg.str() << endl;
        throw std::logic_error(msg.str());
    }

    this->conv_graph.add_conv(from_type, to_type, conv);
    //this->conv_graph.add_conv(from_type, get_index(from_type.get_info().as_restricted()), conv);
    //this->conv_graph.add_conv(to_type, get_index(to_type.get_info().as_restricted()), conv);

    if (!this->conv_graph.has_type(from_type))
    {
        stringstream msg;
        msg << "add_converter_simple missing just-added from type for conversion from " << from_type.description() << " " << from_type.get_id() << " to " << to_type.description() << " " << to_type.get_id() << " conv='" << conv->description() << "'";
        cout << msg.str() << endl;
        //throw std::logic_error(msg.str());
    }

    if (!this->conv_graph.has_type(to_type))
    {
        stringstream msg;
        msg << "add_converter_simple missing just-added to type for conversion from " << from_type.description() << " " << from_type.get_id() << " to " << to_type.description() << " " << to_type.get_id() << " conv='" << conv->description() << "'";
        cout << msg.str() << endl;
        //throw std::logic_error(msg.str());
    }

    if (!has_conv(from_type, to_type))
    {
        bool test_again = has_conv(from_type, to_type);
        stringstream msg;
        msg << test_again;
        msg << "add_converter_simple missing just-added conversion from " << from_type.description() << " " << from_type.get_id() << " to " << to_type.description() << " " << to_type.get_id() << " conv='" << conv->description() << "'";
        cout << msg.str() << endl;
        //throw std::logic_error(msg.str());
    }
}

void TypeSystemInstance::add_conv(TypeInfo from_info, TypeInfo to_info)
{
    this->conv_graph.add_conv(
        get_index(from_info), get_index(to_info),
        new NoChangeConv("from " + from_info.description() + " to " + to_info.description()));
}

void TypeSystemInstance::add_common_conversions(TypeIndex type)
{
    TypeInfo type_info = type.get_info();
    TypeInfo value_nonconst = type_info.as_nonconst_value();
    TypeInfo value_const = type_info.as_const_value();

    add_conv(value_nonconst, value_nonconst.as_restricted());
    add_conv(value_nonconst, value_const.as_restricted());
    add_conv(value_const, value_const.as_restricted());

    TypeInfo ptr_to_nonconst = type_info.as_ptr_to_nonconst();
    TypeInfo ref_to_nonconst = type_info.as_ref_to_nonconst();

    add_conv(ptr_to_nonconst, ref_to_nonconst.as_restricted());
    add_conv(ref_to_nonconst, ptr_to_nonconst.as_restricted());

    TypeInfo ptr_to_const = type_info.as_ptr_to_const();
    TypeInfo ref_to_const = type_info.as_ref_to_const();

    add_conv(ptr_to_const, ref_to_const.as_restricted());
    add_conv(ref_to_const, ptr_to_const.as_restricted());

    add_conv(ptr_to_nonconst, ref_to_const.as_restricted());
    add_conv(ref_to_nonconst, ptr_to_const.as_restricted());

    add_conv(ptr_to_const, ptr_to_const.as_restricted());
    add_conv(ref_to_const, ref_to_const.as_restricted());
    add_conv(ptr_to_nonconst, ptr_to_nonconst.as_restricted());
    add_conv(ref_to_nonconst, ref_to_nonconst.as_restricted());

    TypeInfo const_ref_to_ptr_to_nonconst = ptr_to_nonconst.as_ref_to_nonconst();
    TypeInfo const_ref_to_ptr_to_const = ptr_to_nonconst.as_ref_to_const();

    add_conv(ptr_to_nonconst, const_ref_to_ptr_to_nonconst.as_restricted());
    add_conv(ptr_to_nonconst, const_ref_to_ptr_to_const.as_restricted());
    add_conv(ptr_to_const, const_ref_to_ptr_to_const.as_restricted());

    // These have to be restricted because if refs can be converted
    // to value then they can be auto-converted to script which we don't want.
    add_conv(ref_to_const, value_nonconst.as_restricted());
    add_conv(ref_to_const, value_const.as_restricted());
    add_conv(ref_to_nonconst, value_nonconst.as_restricted());
    add_conv(ref_to_nonconst, value_const.as_restricted());
    add_conv(ptr_to_const, value_nonconst.as_restricted());
    add_conv(ptr_to_const, value_const.as_restricted());
    add_conv(ptr_to_nonconst, value_nonconst.as_restricted());
    add_conv(ptr_to_nonconst, value_const.as_restricted());

    // These are allowed because Term<T> can be called as ref.
    add_conv(value_nonconst, ref_to_nonconst.as_restricted());
    add_conv(value_nonconst, ref_to_const.as_restricted());
    add_conv(value_const, ref_to_const.as_restricted());
    add_conv(value_nonconst, ptr_to_nonconst.as_restricted());
    add_conv(value_nonconst, ptr_to_const.as_restricted());
    add_conv(value_const, ptr_to_const.as_restricted());

    // Anything can be converted to it's const form without restriction.
    add_conv(ref_to_nonconst, ref_to_const);
    add_conv(ptr_to_nonconst, ptr_to_const);
    add_conv(value_nonconst, value_const);

    add_conv(ref_to_nonconst, ref_to_const.as_restricted());
    add_conv(ptr_to_nonconst, ptr_to_const.as_restricted());

    TypeInfo nil_expr_type = create_bottom_ptr_type_info();
    add_conv(nil_expr_type, ptr_to_nonconst.as_restricted());
    add_conv(nil_expr_type, ptr_to_const.as_restricted());
}

void TypeSystemInstance::add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    this->conv_graph.add_conv(from, to, conv);

/*
    // Add converters to make either type const.
    this->add_ptr_convs(from);
    this->add_ptr_convs(to);
*/
    auto from_info = from.get_info();
    auto to_info = to.get_info();

    // Reuse this converter for just the "to" obj const
    this->conv_graph.add_conv(from, get_index(to_info.as_const_value()), conv);

    // Reuse this converter for both from and to as const
    this->conv_graph.add_conv(get_index(from_info.as_const_value()), get_index(to_info.as_const_value()), conv);
}

TypeMirror const* TypeSystemInstance::get_namespace(std::string full_name) const
{
    if (full_name.substr(0, 2) != "::" && full_name != "")
        throw std::logic_error(std::string("get_namespace full_name must begin with :: in namespace ") + full_name);

    return type_system->get_class(
        create_namespace_type_index(full_name));
}

std::vector<TypeIndex> TypeSystemInstance::list_class_types() const
{
    std::vector<TypeIndex> result;

    for (auto kv : this->classes)
        result.push_back(kv.second->get_class_type());

    return result;
}
