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

#include "boost/unordered_map.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

#include "LikeMagic/CallTargets/ConstructorCallTarget.hpp"
#include "LikeMagic/CallTargets/DestructorCallTarget.hpp"
#include "LikeMagic/CallTargets/DelegateCallTarget.hpp"
#include "LikeMagic/CallTargets/ExtensionMethodCallTarget.hpp"
#include "LikeMagic/CallTargets/StaticMethodCallTarget.hpp"

// TODO:  Add virtual type index static_method_type(), ref_type(), and const_ref_type()
// to TypeMirror, and replace calls to generator factory with code that just uses these.
//#include "LikeMagic/Generators/GeneratorFactory.hpp"

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
void bind_nonmember_op(TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    class_.add_method(method_name,
        new LikeMagic::CallTargets::ExtensionMethodCallTarget<R, FirstArg, Args...>(
            reinterpret_cast<Target::F>(f)));
}

template <typename T>
void bind_built_in_operations(TypeMirror& class_)
{
    // In C++, any type can be deleted.
    auto deleter = new LikeMagic::CallTargets::DestructorCallTarget<T>();
    add_method("delete", deleter);

    // const cast
    bind_nonmember_op("remove_const", &operator_remove_const);
}

template <typename T>
void add_delegate_conv()
{
    // Allow the type to be reinterpreted as AbstractDelegate to work with DelegateCallGenerator.
    add_conv<T&, AbstractDelegate&, NoChangeConv>();
}

template <typename T, typename Base, template <typename From, typename To> class Converter=BaseConv>
void add_base(TypeMirror& class_, TypeMirror const& base_class)
{
    class_.add_base_abstr(&base_class);
    add_conv<T*, Base*, Converter>();
}

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...))
{
    typedef DelegateCallTarget_R_nonconst<R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<Target::F>(f),
           BetterTypeInfo::create_index<ObjT&>()));
}

template <typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, void (ObjT::*f)(Args...))
{
    typedef DelegateCallTarget_void_nonconst<Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<Target::F>(f),
           BetterTypeInfo::create_index<ObjT&>()));
}

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...) const)
{
    typedef DelegateCallTarget_R_const<R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<Target::F>(f),
           BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, void (ObjT::*f)(Args...) const)
{
    typedef DelegateCallTarget_void_const<Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<Target::F>(f),
           BetterTypeInfo::create_index<ObjT const&>()));
}

template <typename R, typename... Args>
void bind_static_method(TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    typedef StaticMethodCallTarget_R<R, Args...> Target;
    class_.add_method(method_name, new Target(reinterpret_cast<Target::F>(f)));
}

template <typename... Args>
void bind_static_method(TypeMirror& class_, std::string method_name, void (*f)(Args...))
{
    typedef StaticMethodCallTarget_void<Args...> Target;
    class_.add_method(method_name, new Target(reinterpret_cast<Target::F>(f)));
}

template <typename F>
void bind_field(TypeMirror& class_, std::string field_name, F f)
{
    auto setter = new LikeMagic::CallTargets::FieldSetterTarget<T, F>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new LikeMagic::CallTargets::FieldGetterTarget<T, F>(f);
    class_.add_method("get_" + field_name, getter);
    auto reffer = new LikeMagic::CallTargets::FieldReferenceTarget<T, F>(f);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename F>
void bind_array_field(TypeMirror& class_, std::string field_name, F f)
{
    auto setter = new LikeMagic::CallTargets::ArrayFieldSetterTarget<T, F>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new LikeMagic::CallTargets::ArrayFieldGetterTarget<T, F>(f);
    class_.add_method("get_" + field_name, getter);
    auto reffer = new LikeMagic::CallTargets::ArrayFieldReferenceTarget<T, F>(f);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename FieldAccessor>
void bind_custom_field(TypeMirror& class_, std::string field_name, FieldAccessor f)
{
    auto setter = new LikeMagic::CallTargets::CustomFieldSetterTarget<T&, FieldAccessor>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new LikeMagic::CallTargets::CustomFieldGetterTarget<T const&, FieldAccessor>(f);
    class_.add_method("get_" + field_name, getter);
}

template <typename From, typename To,
    template <typename From, typename To>
        class Converter = LikeMagic::TypeConv::ImplicitConv>
void add_conv()
{
    type_system->add_converter_variations(
        BetterTypeInfo::create_index<From>(),
        BetterTypeInfo::create_index<To>(),
            new Converter<From, To>);
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
    static TypeIndex type(BetterTypeInfo::create_index<T>());
    namespace_.add_method(name, new LikeMagic::CallTargets::ClassExprTarget<T>());
    if (type_system->get_class(type))
    {
        return *(type_system->get_class(type));
    }
    else
    {
        auto result = new LikeMagic::Mirrors::TypeMirror(name, *this, ns);
        type_system->add_class(type, result);
        result->add_base_abstr(proxy_methods);
        type_system->add_ptr_conversions(type, add_deref_ptr_conv);
        register_copyable_conv<T, is_copyable>();
        bind_built_in_operations<T>(*result);
        add_delegate_conv<T>();
        return *result;
    }
}

template <typename T>
BindingTarget<true> register_enum(std::string name, TypeMirror& namespace_)
{
    auto& result = register_class<T, true>(name, ns);
    result.bind_nonmember_op("==",    &EnumHelper<T>::equals);
    result.bind_nonmember_op("!=",    &EnumHelper<T>::not_equals);
    result.bind_nonmember_op("value", &EnumHelper<T>::value);
    result.bind_nonmember_op("asString", &EnumHelper<T>::asString);
    namespace_.add_method(name, new LikeMagic::CallTargets::ClassExprTarget<T>());
    return result;
}

}
