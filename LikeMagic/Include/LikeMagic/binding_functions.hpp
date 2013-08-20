// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"

#include "LikeMagic/Exprs/NamespaceExpr.hpp"
#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"

#include "LikeMagic/CallTargets/ExprTarget.hpp"
#include "LikeMagic/CallTargets/ConstructorTarget.hpp"
#include "LikeMagic/CallTargets/DestructorCallTarget.hpp"
#include "LikeMagic/CallTargets/DelegateCallTarget.hpp"
#include "LikeMagic/CallTargets/ExtensionMethodCallTarget.hpp"
#include "LikeMagic/CallTargets/StaticMethodCallTarget.hpp"
#include "LikeMagic/CallTargets/FieldSetterTarget.hpp"
#include "LikeMagic/CallTargets/FieldGetterTarget.hpp"
#include "LikeMagic/CallTargets/FieldReferenceTarget.hpp"
#include "LikeMagic/CallTargets/ArrayFieldSetterTarget.hpp"
#include "LikeMagic/CallTargets/ArrayFieldGetterTarget.hpp"
#include "LikeMagic/CallTargets/ArrayFieldReferenceTarget.hpp"

#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/BaseConv.hpp"

#include "LikeMagic/Utility/EnumHelper.hpp"
#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"

namespace LikeMagic {

std::string create_constructor_name(std::string prefix, std::string method_name);

template <typename From, typename To,
    template <typename From, typename To>
        class Converter = LikeMagic::TypeConv::ImplicitConv>
void add_conv()
{
    type_system->add_converter_variations(
        LikeMagic::Utility::BetterTypeInfo::create_index<From>(),
        LikeMagic::Utility::BetterTypeInfo::create_index<To>(),
            new Converter<From, To>);
}

template <typename T, typename... Args>
void bind_constructor(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, LikeMagic::Utility::TypePack<Args...>)
{
    static_assert(!boost::is_abstract<T>::value, "Cannot declare LikeMagic constructor on abstract class. To construct objects of this type, register a derived, concrete class and register its constructor.");

    auto target_new = new LikeMagic::CallTargets::ConstructorCallTarget<T, Args...>(false);
    class_.add_method(create_constructor_name("new", method_name), target_new);

    auto target_tmp = new LikeMagic::CallTargets::ConstructorCallTarget<T, Args...>(true);
    class_.add_method(create_constructor_name("tmp", method_name), target_tmp);
}

template <typename T>
T* operator_remove_const(T const * ptr)
{
    return const_cast<T*>(ptr);
}

// Also useful for defining "extension methods".
template <typename R, typename FirstArg, typename... Args>
void bind_nonmember_op(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, R (*f)(FirstArg, Args...))
{
    class_.add_method(method_name,
        new LikeMagic::CallTargets::ExtensionMethodCallTarget<R, FirstArg, Args...>(f));
}

template <typename T>
void bind_built_in_operations(LikeMagic::Mirrors::TypeMirror& class_)
{
    // In C++, any type can be deleted.
    auto deleter = new LikeMagic::CallTargets::DestructorCallTarget<T>();
    class_.add_method("delete", deleter);

    // const cast
    bind_nonmember_op(class_, "remove_const", &operator_remove_const<T>);
}

template <typename T>
void add_delegate_conv()
{
    // Allow the type to be reinterpreted as Delegate to work with DelegateCallGenerator.
    add_conv<T&, LikeMagic::CallTargets::Delegate&, LikeMagic::TypeConv::NoChangeConv>();
}

template <typename T, typename Base, template <typename From, typename To>
    class Converter=LikeMagic::TypeConv::BaseConv>
void add_base(LikeMagic::Mirrors::TypeMirror& class_, LikeMagic::Mirrors::TypeMirror const& base_class)
{
    class_.add_base(&base_class);
    add_conv<T*, Base*, Converter>();
}

template <typename ObjT, typename R, typename... Args>
void bind_method(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...))
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_R_nonconst<R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT&>()));
}

template <typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, void (ObjT::*f)(Args...))
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_void_nonconst<Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT&>()));
}

template <typename ObjT, typename R, typename... Args>
void bind_method(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...) const)
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_R_const<R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename ObjT, typename... Args>
void bind_method(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, void (ObjT::*f)(Args...) const)
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_void_const<Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename R, typename... Args>
void bind_static_method(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    typedef LikeMagic::CallTargets::StaticMethodCallTarget_R<R, Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename... Args>
void bind_static_method(LikeMagic::Mirrors::TypeMirror& class_, std::string method_name, void (*f)(Args...))
{
    typedef LikeMagic::CallTargets::StaticMethodCallTarget_void<Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename T, typename R>
void bind_field(LikeMagic::Mirrors::TypeMirror& class_, std::string field_name, R(T::*f))
{
    typedef LikeMagic::CallTargets::FieldSetterTarget<R> SetterTarget;
    auto setter = new SetterTarget(reinterpret_cast<typename SetterTarget::F>(f), class_.get_const_ref_type());
    class_.add_method("set_" + field_name, setter);

    typedef LikeMagic::CallTargets::FieldGetterTarget<R> GetterTarget;
    auto getter = new GetterTarget(reinterpret_cast<typename GetterTarget::F>(f), class_.get_ref_type());
    class_.add_method("get_" + field_name, getter);

    typedef LikeMagic::CallTargets::FieldReferenceTarget<R> RefferTarget;
    auto reffer = new RefferTarget(reinterpret_cast<typename RefferTarget::F>(f), class_.get_ref_type());
    class_.add_method("ref_" + field_name, reffer);
}

template <typename T, typename R, size_t N>
void bind_array_field(LikeMagic::Mirrors::TypeMirror& class_, std::string field_name, R(T::*f)[N])
{
    typedef LikeMagic::CallTargets::ArrayFieldSetterTarget<R> SetterTarget;
    auto setter = new SetterTarget(reinterpret_cast<typename SetterTarget::F>(f), class_.get_const_ref_type(), N);
    class_.add_method("set_" + field_name, setter);

    typedef LikeMagic::CallTargets::ArrayFieldGetterTarget<R> GetterTarget;
    auto getter = new GetterTarget(reinterpret_cast<typename GetterTarget::F>(f), class_.get_ref_type(), N);
    class_.add_method("get_" + field_name, getter);

    typedef LikeMagic::CallTargets::ArrayFieldReferenceTarget<R> RefferTarget;
    auto reffer = new RefferTarget(reinterpret_cast<typename RefferTarget::F>(f), class_.get_ref_type(), N);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename T, bool is_copyable>
typename boost::enable_if_c<is_copyable>::type
register_copyable_conv()
{
    add_conv<T const&, T>();
}

template <typename T, bool is_copyable>
typename boost::disable_if_c<is_copyable>::type
register_copyable_conv()
{
}

template <typename T, bool is_copyable=!boost::is_abstract<T>::value, bool add_deref_ptr_conv=true>
LikeMagic::Mirrors::TypeMirror& register_class(std::string name, TypeMirror& namespace_)
{
    static const TypeIndex class_type(LikeMagic::Utility::BetterTypeInfo::create_index<T>());
    static const TypeIndex ref_type(LikeMagic::Utility::BetterTypeInfo::create_index<T&>());
    static const TypeIndex const_ref_type(LikeMagic::Utility::BetterTypeInfo::create_index<T const&>());

    namespace_.add_method
    (
        name, new LikeMagic::CallTargets::ExprTarget
        (
            LikeMagic::Exprs::NamespaceExpr::create
            (
                LikeMagic::Utility::NamespaceTypeInfo::create_index(name), class_type
            )
        )
    );

    if (type_system->get_class(class_type))
    {
        return *(type_system->get_class(class_type));
    }
    else
    {
        auto result = new LikeMagic::Mirrors::TypeMirror(name, sizeof(T), class_type, ref_type, const_ref_type);
        type_system->add_class(class_type, result);
        //result->add_base(proxy_methods);
        type_system->add_ptr_conversions(class_type, add_deref_ptr_conv);
        register_copyable_conv<T, is_copyable>();
        bind_built_in_operations<T>(*result);
        add_delegate_conv<T>();
        return *result;
    }
}

template <typename T>
LikeMagic::Mirrors::TypeMirror& register_enum(std::string name, TypeMirror& namespace_)
{
    auto& result = register_class<T, true>(name, namespace_);
    bind_nonmember_op(result, "==",    &LikeMagic::Utility::EnumHelper<T>::equals);
    bind_nonmember_op(result, "!=",    &LikeMagic::Utility::EnumHelper<T>::not_equals);
    bind_nonmember_op(result, "value", &LikeMagic::Utility::EnumHelper<T>::value);
    bind_nonmember_op(result, "asString", &LikeMagic::Utility::EnumHelper<T>::asString);
    return result;
}

LikeMagic::Mirrors::TypeMirror& register_namespace(std::string name, TypeMirror& parent_namespace_);

}
