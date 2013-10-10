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
#include "LikeMagic/Utility/KeyWrapper.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"
#include "LikeMagic/Utility/BottomPtrTypeInfo.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"
#include "LikeMagic/CallTargets/DeleterCallTarget.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"

#include <set>
#include <map>
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;

using namespace LM;

namespace LM {

TypeSystem::~TypeSystem() {}

class TypeSystemInstance : private TypeSystem
{
private:
    TypeSystemInstance();
    friend LIKEMAGIC_API TypeSystem* create_type_system();

    struct Impl;
    boost::shared_ptr<Impl> impl;

    // Don't allow accidently making copies of this class
    TypeSystemInstance(TypeSystem const&) = delete;
    TypeSystem& operator =(TypeSystem const&) = delete;

public:

    virtual ~TypeSystemInstance();
    virtual TypeMirror* get_class(TypeIndex type) const;
    virtual void add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_);
    virtual void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual TypeMirror& global_namespace() const;
    virtual TypeMirror const* get_namespace(std::string full_name) const;
};

    LIKEMAGIC_API TypeSystem* create_type_system() { return new TypeSystemInstance(); }
    LIKEMAGIC_API TypeSystem* type_system = NULL;
}

struct TypeSystemInstance::Impl
{
    boost::unordered_map<TypeIndex, TypeMirror*> classes;
    TypeMirror* unknown_class;
    TypeConvGraph conv_graph;
    TypeInfoCache type_info_cache;
    TypeMirror* global_namespace;

    void add_ptr_convs(TypeIndex index)
    {
        TypeInfoPtr bare = index.get_info()->class_type();
        add_conv_track<void>(bare);
        add_conv_track<void const>(bare->as_const());

        // allow unsafe_ptr_cast to convert to any type and nil (NULL) to any pointer type
        add_nochange_conv(create_bottom_ptr_type_info(), bare->as_ptr());
        add_nochange_conv(create_bottom_ptr_type_info(), bare->as_ptr()->as_const());

        // allow any ptr to be converted to void* or void const*
        add_nochange_conv(bare->as_ptr(), TypId<void*>::get().get_info());
        add_nochange_conv(bare->as_ptr()->as_const(), TypId<void const*>::get().get_info());
    }

    void add_nochange_conv(TypeInfoPtr from, TypeInfoPtr to)
    {
        if (!(get_index(from) == get_index(to)))
            conv_graph.add_conv(get_index(from), get_index(to), new NoChangeConv());
    }

    template <typename From, typename To>
    void add_static_cast_conv(TypeInfoPtr from, TypeInfoPtr to)
    {
        conv_graph.add_conv(get_index(from), get_index(to), new StaticCastConv<From, To>(from, to));
    }

    template <typename T>
    void add_conv_track(TypeInfoPtr type)
    {
        auto as_ptr = type->as_ptr();
        auto as_ptr_const = as_ptr->as_const();

        // Making a ptr const does not change the implementation.
        add_nochange_conv(as_ptr, as_ptr_const);
    }
};

TypeSystemInstance::TypeSystemInstance()
    : impl(new TypeSystemInstance::Impl)
{
    type_info_cache_instance = &(impl->type_info_cache);

    TypeIndex ns_type = create_namespace_type_index("");
    impl->global_namespace = create_type_mirror("", 0, ns_type);
    impl->classes[ns_type] = impl->global_namespace;

    // Allow conversions from nil to any pointer.
    TypeIndex nil_expr_type = create_bottom_ptr_type_index();
    impl->conv_graph.add_type(nil_expr_type);
}

TypeMirror& TypeSystemInstance::global_namespace() const
{
    return *(impl->global_namespace);
}

void TypeSystemInstance::add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_)
{
    cout << "add_class " << index.description() << endl;
    if (!index.is_class_type())
        throw std::logic_error("add_class type index has to be a class type!");

    if (!(index == class_ptr->get_class_type()))
        throw std::logic_error("add_class: Index=" + index.description() + " not the same as class_ptr type=" + class_ptr->get_class_type().description());

    // Add conversion to delegate type so that delegate call targets will work.
    impl->conv_graph.add_conv(index.as_ptr_type(),
        TypId<LM::Delegate*>::get(), new NoChangeConv());
    impl->conv_graph.add_conv(index.as_const_ptr_type(),
        TypId<LM::Delegate const*>::get(), new NoChangeConv());

    // Add conversion from nonconst pointer to const.
    impl->conv_graph.add_conv(
        index.as_ptr_type(),
        index.as_const_ptr_type(),
        new NoChangeConv());

    TypeIndex x = index.as_ptr_type();
    if (!impl->conv_graph.has_type(x))
        throw std::logic_error(std::string("Type just added is missing from conv_graph: ") + x.description());

    impl->classes[index] = class_ptr;

    auto deleter_target = new DeleterCallTarget();
    class_ptr->add_method("delete", deleter_target);

    namespace_.add_method(
        class_ptr->get_class_name(), new LM::ExprTarget(
            create_expr(class_ptr, index)));
}

TypeSystemInstance::~TypeSystemInstance()
{
    for (auto it=impl->classes.begin(); it != impl->classes.end(); it++)
    {
        delete it->second;
    }
}

ExprPtr TypeSystemInstance::try_conv(ExprPtr from_expr, TypeIndex to_type) const
{
    try
    {
        return impl->conv_graph.wrap_expr(from_expr, from_expr->get_type(), to_type);
    }
    catch (std::logic_error const& le)
    {
        throw std::logic_error(le.what() + std::string(" From expression was ") + from_expr->description());
    }
}

bool TypeSystemInstance::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return impl->conv_graph.has_conv(from_type, to_type);
}

TypeMirror* TypeSystemInstance::get_class(TypeIndex type) const
{
    auto iter = impl->classes.find(type.class_type());
    if (iter != impl->classes.end())
    {
        return iter->second;
    }
    else
    {
        return nullptr;
    }
}

void TypeSystemInstance::add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    impl->conv_graph.add_conv(from, to, conv);
}

void TypeSystemInstance::add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    impl->conv_graph.add_conv(from, to, conv);

    // Add converters to make either type const.
    impl->add_ptr_convs(from);
    impl->add_ptr_convs(to);

    auto from_info = from.get_info();
    auto to_info = to.get_info();

    // Allow converting the object directly to its const form
    impl->conv_graph.add_conv(from, from.as_const_type(), new NoChangeConv);
    impl->conv_graph.add_conv(to, to.as_const_type(), new NoChangeConv);

    // Reuse this converter for just the "to" obj const
    impl->conv_graph.add_conv(from, to.as_const_type(), conv);

    // Reuse this converter for both from and to as const
    impl->conv_graph.add_conv(from.as_const_type(), to.as_const_type(), conv);
}

TypeMirror const* TypeSystemInstance::get_namespace(std::string full_name) const
{
    if (full_name.substr(0, 2) != "::" && full_name != "")
        throw std::logic_error(std::string("get_namespace full_name must begin with :: in namespace ") + full_name);

    return type_system->get_class(
        create_namespace_type_index(full_name));
}
