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
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/GenericConv.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/Exprs/NullExpr.hpp"
#include "LikeMagic/Exprs/BottomPtrExpr.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"
#include "LikeMagic/Utility/TupleForEach.hpp"
#include "LikeMagic/Utility/KeyWrapper.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/GenericConv.hpp"
#include "LikeMagic/TypeConv/ToAbstractExpressionConv.hpp"
#include "LikeMagic/TypeConv/PtrDerefConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"
#include "LikeMagic/Exprs/NamespaceExpr.hpp"
#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"

#include <set>
#include <map>
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;

using namespace LM;

namespace LM {
    TypeSystem* type_system = NULL;
}

struct TypeSystem::Impl
{
    boost::unordered_map<TypeIndex, TypeMirror*> classes;
    TypeMirror* unknown_class;
    TypeConvGraph conv_graph;
    TypeInfoCache* dll_shared_typeinfo;
    TypeMirror* global_namespace;

    void add_ptr_convs(TypeIndex index)
    {
        TypeInfoPtr bare = index.get_info()->bare_type();
        add_conv_track<void>(bare);
        add_conv_track<void const>(bare->as_const_obj_type());

        auto bot_tag = BetterTypeInfo::create_index<BottomPtrType>().get_info();

        // allow unsafe_ptr_cast to convert to any type and nil (NULL) to any pointer type
        add_nochange_conv<BottomPtrType, void*>(bot_tag, bare->as_ptr());
        add_nochange_conv<BottomPtrType, void const*>(bot_tag, bare->as_ptr()->as_const_obj_type());

        // allow any ptr to be converted to void* or void const*
        add_nochange_conv<void*, void*>(bare->as_ptr(), BetterTypeInfo::create_index<void*>().get_info());
        add_nochange_conv<void const*, void const*>(bare->as_ptr()->as_const_obj_type(), BetterTypeInfo::create_index<void const*>().get_info());
    }

    template <typename From, typename To>
    void add_nochange_conv(TypeInfoPtr from, TypeInfoPtr to)
    {
        if (!(from->get_index() == to->get_index()))
            conv_graph.add_conv(from->get_index(), to->get_index(), new NoChangeConv<From, To>());
    }

    template <typename From, typename To>
    void add_generic_conv(TypeInfoPtr from, TypeInfoPtr to)
    {
        conv_graph.add_conv(from->get_index(), to->get_index(), new GenericConv<From, To>(from, to));
    }

    template <typename T>
    void add_conv_track(TypeInfoPtr type)
    {
        auto as_ptr_ref = type->as_ptr()->as_ref();
        auto as_ptr_const_ref = type->as_ptr()->as_const_ptr_type()->as_ref();
        auto as_ptr_const_val = type->as_ptr()->as_const_ptr_type();
        auto as_ptr_val = type->as_ptr();

        // Making a reference const does not change the implementation.
        add_nochange_conv<T*&, T*const&>(as_ptr_ref, as_ptr_const_ref);

        // Reciprocally convert const ref and const value with a generic conv.
        add_generic_conv<T*const&, T*const>(as_ptr_const_ref, as_ptr_const_val);
        add_generic_conv<T*const, T*const&>(as_ptr_const_val, as_ptr_const_ref);

        // Reciprocally convert const and nonconst ptr values with no change in the impl.
        add_nochange_conv<T*const, T*>(as_ptr_const_val, as_ptr_val);
        add_nochange_conv<T*, T*const>(as_ptr_val, as_ptr_const_val);

        // For the nonconst track, add all the conversions to the const track.
        // (These will be nop's if we are already on the const track)
        add_nochange_conv<T*&, T const*&>(as_ptr_ref, as_ptr_ref->as_const_obj_type());
        add_nochange_conv<T*const&, T const*const&>(as_ptr_const_ref, as_ptr_const_ref->as_const_obj_type());
        add_nochange_conv<T*const , T const*const >(as_ptr_const_val, as_ptr_const_val->as_const_obj_type());
        add_nochange_conv<T* , T const* >(as_ptr_val, as_ptr_val->as_const_obj_type());
    }
};

TypeSystem::TypeSystem()
    : impl(new TypeSystem::Impl)
{
    impl->dll_shared_typeinfo = new TypeInfoCache;
    TypeInfoCache::set_instance(impl->dll_shared_typeinfo);

    TypeIndex ns_type = NamespaceTypeInfo::create_index("namespace");
    impl->global_namespace = new TypeMirror("namespace", 0, ns_type, ns_type, ns_type);

    // Allow conversions from nil to any pointer.
    static TypeIndex nil_expr_type = BetterTypeInfo::create_index<BottomPtrType>();
    impl->conv_graph.add_type(nil_expr_type);
}

TypeMirror& TypeSystem::global_namespace() const
{
    return *(impl->global_namespace);
}

void TypeSystem::add_class(TypeIndex index, TypeMirror* class_ptr)
{
    if (!index.is_class_type())
        throw std::logic_error("add_class type index has to be a class type!");

    if (!(index == class_ptr->get_class_type()))
        throw std::logic_error("add_class: Index=" + index.description() + " not the same as class_ptr type=" + class_ptr->get_class_type().description());

    // add_class also called for non-C++ type objects such as "namespace"
    //add_ptr_convs(index);

    impl->classes[index] = class_ptr;
}

TypeSystem::~TypeSystem()
{
    for (auto it=impl->classes.begin(); it != impl->classes.end(); it++)
    {
        delete it->second;
    }
}

ExprPtr TypeSystem::try_conv(ExprPtr from_expr, TypeIndex to_type) const
{
    try
    {
        return impl->conv_graph.wrap_expr(from_expr, from_expr->get_type(), to_type);
    }
    catch (std::logic_error const& le)
    {
        throw std::logic_error(le.what() + std::string(" Note: From expression is ") + from_expr->description());
    }
}

bool TypeSystem::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return impl->conv_graph.has_conv(from_type, to_type);
}

TypeMirror* TypeSystem::get_class(TypeIndex type) const
{
    auto iter = impl->classes.find(type);
    if (iter != impl->classes.end())
    {
        return iter->second;
    }
    else
    {
        //return unknown_class;
        throw std::logic_error("No class registered for type " + type.description());
    }
}

void TypeSystem::add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    impl->conv_graph.add_conv(from, to, conv);
}

void TypeSystem::add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    impl->conv_graph.add_conv(from, to, conv);

    // Add converters to make either type const.
    impl->add_ptr_convs(from);
    impl->add_ptr_convs(to);

    auto from_info = from.get_info();
    auto to_info = to.get_info();

    // Allow converting the object directly to its const form
    impl->conv_graph.add_conv(from, from_info->as_const_obj_type()->get_index(), new NoChangeConv<>);
    impl->conv_graph.add_conv(to, to_info->as_const_obj_type()->get_index(), new NoChangeConv<>);

    // Reuse this converter for just the "to" obj const
    impl->conv_graph.add_conv(from, to.get_info()->as_const_obj_type()->get_index(), conv);

    // Reuse this converter for both from and to as const
    impl->conv_graph.add_conv(from.get_info()->as_const_obj_type()->get_index(), to.get_info()->as_const_obj_type()->get_index(), conv);

    // Allow this expression type to be converted to an expression argument.
    TypeIndex as_expr_type = BetterTypeInfo::create_index<ExprPtr>();
    impl->conv_graph.add_conv(from, as_expr_type, new ToAbstractExpressionConv);
    impl->conv_graph.add_conv(from.get_info()->as_const_obj_type()->get_index(), as_expr_type, new ToAbstractExpressionConv);
    impl->conv_graph.add_conv(to, as_expr_type, new ToAbstractExpressionConv);
    impl->conv_graph.add_conv(to.get_info()->as_const_obj_type()->get_index(), as_expr_type, new ToAbstractExpressionConv);
}

void TypeSystem::add_ptr_conversions(TypeIndex from_type, bool auto_deref)
{
    auto from_nc = from_type.get_info();
    auto from_c =  from_type.get_info()->as_const_obj_type();

    // Allow passing the actual object to things that need the pointer to the object.
    impl->conv_graph.add_conv(from_nc->as_ref()->get_index(), from_nc->as_ptr()->get_index(), new AddrOfConv<Delegate&, Delegate*>);
    impl->conv_graph.add_conv( from_c->as_ref()->get_index(),  from_c->as_ptr()->get_index(), new AddrOfConv<Delegate&, Delegate*>);

    // Don't want to do this for types convertible to script types, e.g. int*,
    // because then you couldn't return an array; instead the first array element
    // could get converted to a script value if you had this enabled.
    if (auto_deref)
    {
        // Also allow converting pointers back to references.
        impl->conv_graph.add_conv(from_nc->as_ptr()->get_index(), from_nc->as_ref()->get_index(), new PtrDerefConv<Delegate*, Delegate&>);
        impl->conv_graph.add_conv( from_c->as_ptr()->get_index(),  from_c->as_ref()->get_index(), new PtrDerefConv<Delegate*, Delegate&>);
    }
}
