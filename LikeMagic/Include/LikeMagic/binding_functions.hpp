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

#include "LikeMagic/TypeConv/StaticCastConv.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/StaticCastConv.hpp"

#include "LikeMagic/Utility/EnumHelper.hpp"
#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"

namespace LM {

std::string create_constructor_name(std::string prefix, std::string method_name);

template <typename From, typename To,
    template <typename From, typename To>
        class Converter = LM::StaticCastConv>
void add_conv()
{
    type_system->add_converter_variations(
        LM::TypId<From>::get(),
        LM::TypId<To>::get(),
            new Converter<From, To>);
}

template <typename T, typename... Args>
void bind_constructor(LM::TypeMirror& class_, std::string method_name, LM::TypePack<Args...>)
{
    static_assert(!boost::is_abstract<T>::value, "Cannot declare LikeMagic constructor on abstract class. To construct objects of this type, register a derived, concrete class and register its constructor.");

    auto target_new = new LM::ConstructorCallTarget<T, Args...>(false);
    class_.add_method(create_constructor_name("new", method_name), target_new);

    auto target_tmp = new LM::ConstructorCallTarget<T, Args...>(true);
    class_.add_method(create_constructor_name("tmp", method_name), target_tmp);
}

template <typename T>
T* operator_remove_const(T const * ptr)
{
    return const_cast<T*>(ptr);
}

// Also useful for defining "extension methods".
template <typename R, typename FirstArg, typename... Args>
void bind_nonmember_op(LM::TypeMirror& class_, std::string method_name, R (*f)(FirstArg, Args...))
{
    class_.add_method(method_name,
        new LM::ExtensionMethodCallTarget<R, FirstArg, Args...>(f));
}
/*
template <typename T>
void bind_built_in_operations(LM::TypeMirror& class_)
{
    // In C++, any type can be deleted.
    auto deleter = new LM::DestructorCallTarget<T>();
    class_.add_method("delete", deleter);

    // const cast
    bind_nonmember_op(class_, "remove_const", &operator_remove_const<T>);
}
*/
/*
template <typename T>
void add_delegate_conv()
{
    // Allow the type to be reinterpreted as Delegate to work with DelegateCallGenerator.
    add_conv<T&, LM::Delegate&, LM::NoChangeConv>();
}
*/

template <typename T, typename Base, template <typename From, typename To>
    class Converter=LM::StaticCastConv>
void add_base(LM::TypeMirror& class_, LM::TypeMirror const& base_class)
{
    class_.add_base(&base_class);
    add_conv<T*, Base*, Converter>();
}


template <typename ObjT, typename R, typename... Args>
void bind_method(LM::TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...))
{
    typedef LM::DelegateCallTarget<false, R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           class_.get_class_type()));
}

template <typename ObjT, typename R, typename... Args>
void bind_method(LM::TypeMirror& class_, std::string method_name, R (ObjT::*f)(Args...) const)
{
    typedef LM::DelegateCallTarget<true, R, Args...> Target;
    class_.add_method(
        method_name,
        new Target(
           reinterpret_cast<typename Target::F>(f),
           class_.get_class_type()));
}


#ifdef LM_BINDING_FUNCTIONS_CPP
#define LM_DEF_BIND_METHOD_IMPL(RTYPE, ARGTYPE) \
void bind_method_impl(TypeMirror& class_, std::string method_name, RTYPE (Delegate::*f)(ARGTYPE)) { \
    class_.add_method(method_name, create_target(f, class_.get_class_type())); } \
void bind_method_impl(TypeMirror& class_, std::string method_name, RTYPE (Delegate::*f)(ARGTYPE) const) { \
    class_.add_method(method_name, create_target(f, class_.get_class_type())); }
#else
#define LM_DEF_BIND_METHOD_IMPL(RTYPE, ARGTYPE) \
void bind_method_impl(TypeMirror& class_, std::string method_name, RTYPE (Delegate::*f)(ARGTYPE)); \
void bind_method_impl(TypeMirror& class_, std::string method_name, RTYPE (Delegate::*f)(ARGTYPE) const);
#endif

#define LM_DECL_BIND_METHOD(RTYPE, ARGTYPE) \
LM_DEF_BIND_METHOD_IMPL(RTYPE, ARGTYPE) \
template <typename ObjT> void bind_method( \
    LM::TypeMirror& class_, std::string method_name, RTYPE (ObjT::*f)(ARGTYPE)) { \
    bind_method_impl(class_, method_name, reinterpret_cast<RTYPE(Delegate::*)(ARGTYPE)>(f)); } \
template <typename ObjT> void bind_method( \
    LM::TypeMirror& class_, std::string method_name, RTYPE (ObjT::*f)(ARGTYPE) const) { \
        bind_method_impl(class_, method_name, reinterpret_cast<RTYPE(Delegate::*)(ARGTYPE) const>(f)); }

LM_DECL_BIND_METHOD(void,)
LM_DECL_BIND_METHOD(int,)
LM_DECL_BIND_METHOD(unsigned int,)
LM_DECL_BIND_METHOD(float,)
LM_DECL_BIND_METHOD(double,)

LM_DECL_BIND_METHOD(void, int)
LM_DECL_BIND_METHOD(void, unsigned int)
LM_DECL_BIND_METHOD(void, float)
LM_DECL_BIND_METHOD(void, double)




template <typename R, typename... Args>
void bind_static_method(LM::TypeMirror& class_, std::string method_name, R (*f)(Args...))
{
    typedef LM::StaticMethodCallTarget_R<R, Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename... Args>
void bind_static_method(LM::TypeMirror& class_, std::string method_name, void (*f)(Args...))
{
    typedef LM::StaticMethodCallTarget_void<Args...> Target;
    class_.add_method(method_name, new Target(f));
}

template <typename T, typename R>
void bind_field(LM::TypeMirror& class_, std::string field_name, R(T::*f))
{
    typedef LM::FieldSetterTarget<R> SetterTarget;
    auto setter = new SetterTarget(reinterpret_cast<typename SetterTarget::F>(f), class_.get_const_ptr_type());
    class_.add_method("set_" + field_name, setter);

    typedef LM::FieldGetterTarget<R> GetterTarget;
    auto getter = new GetterTarget(reinterpret_cast<typename GetterTarget::F>(f), class_.get_ptr_type());
    class_.add_method("get_" + field_name, getter);

    typedef LM::FieldReferenceTarget<R> RefferTarget;
    auto reffer = new RefferTarget(reinterpret_cast<typename RefferTarget::F>(f), class_.get_ptr_type());
    class_.add_method("ref_" + field_name, reffer);
}

template <typename T, typename R, size_t N>
void bind_array_field(LM::TypeMirror& class_, std::string field_name, R(T::*f)[N])
{
    typedef LM::ArrayFieldSetterTarget<R> SetterTarget;
    auto setter = new SetterTarget(reinterpret_cast<typename SetterTarget::F>(f), class_.get_const_ptr_type(), N);
    class_.add_method("set_" + field_name, setter);

    typedef LM::ArrayFieldGetterTarget<R> GetterTarget;
    auto getter = new GetterTarget(reinterpret_cast<typename GetterTarget::F>(f), class_.get_ptr_type(), N);
    class_.add_method("get_" + field_name, getter);

    typedef LM::ArrayFieldReferenceTarget<R> RefferTarget;
    auto reffer = new RefferTarget(reinterpret_cast<typename RefferTarget::F>(f), class_.get_ptr_type(), N);
    class_.add_method("ref_" + field_name, reffer);
}

template <typename T>
LM::TypeMirror& register_class(std::string name, TypeMirror& namespace_)
{
    const TypeIndex class_type(LM::TypId<T>::get());

    if (type_system->get_class(class_type))
        return *(type_system->get_class(class_type));
    else
    {
        auto result = new LM::TypeMirror(name, sizeof(T), class_type);
        type_system->add_class(class_type, result, namespace_);

        // TODO: Merge implementation of this with implementation of TermDeleter.
        //auto deleter = new LM::DestructorCallTarget<T>();
        //result->add_method("delete", deleter);

        return *result;
    }
}

template <typename T>
LM::TypeMirror& register_enum(std::string name, TypeMirror& namespace_)
{
    auto& result = register_class<T>(name, namespace_);
    bind_nonmember_op(result, "==",    &LM::EnumHelper<T>::equals);
    bind_nonmember_op(result, "!=",    &LM::EnumHelper<T>::not_equals);
    bind_nonmember_op(result, "value", &LM::EnumHelper<T>::value);
    bind_nonmember_op(result, "asString", &LM::EnumHelper<T>::asString);
    return result;
}

LM::TypeMirror& register_namespace(std::string name, TypeMirror& parent_namespace_);

}
