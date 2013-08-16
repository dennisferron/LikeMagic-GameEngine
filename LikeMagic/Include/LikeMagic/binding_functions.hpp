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
#include "LikeMagic/CallTargets/ConstructorCallTarget.hpp"
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

template <bool is_copyable>
struct BindingTarget
{
    TypeMirror& mirror;
    BindingTarget(TypeMirror& mirror_) : mirror(mirror_) {}
};

std::string create_constructor_name(std::string prefix, std::string method_name)
{
    if (method_name.substr(0, 3) == "new")
        return prefix + method_name.substr(3);
    else
        return prefix + "_" + method_name;
}

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

template <typename T, bool is_copyable, typename... Args>
void add_constructor(BindingTarget<is_copyable> class_, std::string prefix, std::string method_name)
{
    auto target = new LikeMagic::CallTargets::ConstructorCallTarget<T, is_copyable, Args...>();
    class_.mirror.add_method(create_constructor_name(prefix, method_name), target);
}

template <typename T, bool is_copyable, typename... Args>
void bind_constructor(BindingTarget<is_copyable> class_, std::string method_name="new")
{
    static_assert(!boost::is_abstract<T>::value, "Cannot declare LikeMagic constructor on abstract class. To construct objects of this type, register a derived, concrete class and register its constructor.");
    add_constructor<T*, Args...>(class_, "new", method_name);
    add_constructor<T, Args...>(class_, "tmp", method_name);
    add_constructor<T&, Args...>(class_, "ref", method_name);
    if (!has_method(alt_name(class_, "ptr", method_name), 0))
        add_constructor<T*&>(class_, "ptr", method_name);
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
void bind_built_in_operations(TypeMirror& class_)
{
    // In C++, any type can be deleted.
    auto deleter = new LikeMagic::CallTargets::DestructorCallTarget<T>();
    add_method("delete", deleter);

    // const cast
    bind_nonmember_op("remove_const", &operator_remove_const<T>);
}

template <typename T>
void add_delegate_conv()
{
    // Allow the type to be reinterpreted as Delegate to work with DelegateCallGenerator.
    add_conv<T&, LikeMagic::CallTargets::Delegate&, LikeMagic::TypeConv::NoChangeConv>();
}

template <typename T, typename Base, template <typename From, typename To>
    class Converter=LikeMagic::TypeConv::BaseConv>
void add_base(TypeMirror& class_, TypeMirror const& base_class)
{
    class_.add_base(&base_class);
    add_conv<T*, Base*, Converter>();
}

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...))
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

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...) const)
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_R_const<R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, void (ObjT::*f)(Args...) const)
{
    typedef LikeMagic::CallTargets::DelegateCallTarget_void_const<Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           LikeMagic::Utility::BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename R, typename... Args>
void bind_static_method(TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    typedef LikeMagic::CallTargets::StaticMethodCallTarget_R<R, Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename... Args>
void bind_static_method(TypeMirror& class_, std::string method_name, void (*f)(Args...))
{
    typedef LikeMagic::CallTargets::StaticMethodCallTarget_void<Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename T, typename R>
void bind_field(TypeMirror& class_, std::string field_name, R(T::*f))
{
    auto setter = new LikeMagic::CallTargets::FieldSetterTarget<R>(f, class_.get_const_ref_type());
    class_.add_method("set_" + field_name, setter);
    auto getter = new LikeMagic::CallTargets::FieldGetterTarget<R>(f, class_.get_ref_type());
    class_.add_method("get_" + field_name, getter);
    auto reffer = new LikeMagic::CallTargets::FieldReferenceTarget<R>(f, class_.get_ref_type());
    class_.add_method("ref_" + field_name, reffer);
}

template <typename T, typename R, int N>
void bind_array_field(TypeMirror& class_, std::string field_name, R(T::*f)[N])
{
    auto setter = new LikeMagic::CallTargets::ArrayFieldSetterTarget<R>(f, class_.get_const_ref_type());
    class_.add_method("set_" + field_name, setter);
    auto getter = new LikeMagic::CallTargets::ArrayFieldGetterTarget<R>(f, class_.get_ref_type());
    class_.add_method("get_" + field_name, getter);
    auto reffer = new LikeMagic::CallTargets::ArrayFieldReferenceTarget<R>(f, class_.get_ref_type());
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
BindingTarget<is_copyable> register_class(std::string name, TypeMirror& namespace_)
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
BindingTarget<true> register_enum(std::string name, TypeMirror& namespace_)
{
    auto& result = register_class<T, true>(name, namespace_);
    result.bind_nonmember_op("==",    &LikeMagic::Utility::EnumHelper<T>::equals);
    result.bind_nonmember_op("!=",    &LikeMagic::Utility::EnumHelper<T>::not_equals);
    result.bind_nonmember_op("value", &LikeMagic::Utility::EnumHelper<T>::value);
    result.bind_nonmember_op("asString", &LikeMagic::Utility::EnumHelper<T>::asString);
    return result;
}

}
