// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "TypeSystem.hpp"

#include "boost/unordered_map.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

namespace LikeMagic {

std::string create_constructor_name(std::string prefix, std::string method_name)
{
    if (method_name.substr(0, 3) == "new")
        return prefix + method_name.substr(3);
    else
        return prefix + "_" + method_name;
}

template <typename T, typename... Args>
void add_constructor(TypeMirror& class_, std::string prefix, std::string method_name)
{
    auto target = new ConstructorCallTarget<T, is_copyable, Args...>();
    class_.add_method(create_constructor_name(prefix, method_name), target);
}

template <typename T, typename... Args>
void bind_constructor(TypeMirror& class_, std::string method_name="new")
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

template <typename T>
void bind_built_in_operations(TypeMirror& class_)
{
    // In C++, any type can be deleted.
    auto deleter = new DestructorCallTarget<T>();
    add_method("delete", deleter);

    // const cast
    bind_nonmember_op("remove_const", &operator_remove_const);
}

template <typename T>
void add_delegate_conv()
{
    // Allow the type to be reinterpreted as AbstractDelegate to work with DelegateCallGenerator.
    type_system->add_conv<T&, AbstractDelegate&, NoChangeConv>();
}

template <typename T, typename Base, template <typename From, typename To> class Converter=BaseConv>
void add_base(TypeMirror& class_, TypeMirror const& base_class)
{
    class_.add_base_abstr(&base_class);
    type_system->add_conv<T*, Base*, Converter>();
}

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...))
{
    typedef R (AbstractDelegate::*DelgFuncPtr)(Args...);
    auto calltarget = GeneratorFactory<MemberKind::member_nonconst, R, ObjT, Args...>::create(ref_type, const_ref_type, f, type_system);
    class_.add_method(method_name, calltarget);
}

template <typename R, typename ObjT, typename... Args>
void bind_method(TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...) const)
{
    typedef R (AbstractDelegate::*DelgFuncPtr)(Args...) const;
    auto calltarget = GeneratorFactory<MemberKind::member_const, R, ObjT, Args...>::create(ref_type, const_ref_type, f);
    class_.add_method(method_name, calltarget);
}

template <typename R, typename... Args>
void bind_static_method(TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    auto calltarget = GeneratorFactory<MemberKind::static_method, R, StaticMethod, Args...>::create(static_method_type, static_method_type, f);
    class_.add_method(method_name, calltarget);
}

// Also useful for defining "extension methods".
template <typename R, typename... Args>
void bind_nonmember_op(TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    auto calltarget = GeneratorFactory<MemberKind::nonmember_op, R, StaticMethod, Args...>::create(static_method_type, static_method_type, f);
    class_.add_method(method_name, calltarget);
}

template <typename F>
void bind_field(TypeMirror& class_, std::string field_name, F f)
{
    auto setter = new FieldSetterTarget<T, F>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new FieldGetterTarget<T, F>(f);
    class_.add_method("get_" + field_name, getter);
    auto reffer = new FieldReferenceTarget<T, F>(f);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename F>
void bind_array_field(TypeMirror& class_, std::string field_name, F f)
{
    auto setter = new ArrayFieldSetterTarget<T, F>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new ArrayFieldGetterTarget<T, F>(f);
    class_.add_method("get_" + field_name, getter);
    auto reffer = new ArrayFieldReferenceTarget<T, F>(f);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename FieldAccessor>
void bind_custom_field(TypeMirror& class_, std::string field_name, FieldAccessor f)
{
    auto setter = new CustomFieldSetterTarget<T&, FieldAccessor>(f);
    class_.add_method("set_" + field_name, setter);
    auto getter = new CustomFieldGetterTarget<T const&, FieldAccessor>(f);
    class_.add_method("get_" + field_name, getter);
}

template <typename From, typename To, template <typename From, typename To> class Converter=ImplicitConv>
void add_conv()
{
    type_system->add_converter_variations(
        BetterTypeInfo::create_index<From>(),
        BetterTypeInfo::create_index<To>(),
            new Converter<From, To>);
}

template <typename To>
boost::intrusive_ptr<Expression<To>> try_conv(ExprPtr from) const
{
    return static_cast<Expression<To>*>(type_system->try_conv(from, BetterTypeInfo::create_index<To>()).get());
}

template <typename To>
bool has_conv(ExprPtr from) const
{
    return has_conv(from->get_type(), BetterTypeInfo::create_index<To>());
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
TypeMirror& register_class(std::string name, TypeMirror& namespace_)
{
    static TypeIndex type(BetterTypeInfo::create_index<T>());
    namespace_.add_method(name, new ClassExprTarget<T>());
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
TypeMirror& register_enum(std::string name, TypeMirror& namespace_)
{
    auto& result = register_class<T, true>(name, ns);
    result.bind_nonmember_op("==",    &EnumHelper<T>::equals);
    result.bind_nonmember_op("!=",    &EnumHelper<T>::not_equals);
    result.bind_nonmember_op("value", &EnumHelper<T>::value);
    result.bind_nonmember_op("asString", &EnumHelper<T>::asString);
    namespace_.add_method(name, new ClassExprTarget<T>());
    return result;
}

}
