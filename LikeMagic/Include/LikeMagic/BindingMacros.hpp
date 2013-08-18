// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

// Defines a collection of macros to aid in binding or protos.

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/binding_functions.hpp"

#include "boost/preprocessor/seq/for_each.hpp"
#include "boost/preprocessor/stringize.hpp"

#define LM_ENUM_PROTOS_IMPL(r, data, elem) data.add_proto(BOOST_PP_STRINGIZE(elem), elem);
#define LM_ENUM_PROTOS(vm_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_ENUM_PROTOS_IMPL, vm_name, SEQ)

#define LM_ADD_PROTO(vm_name, class_name, ...) vm_name.add_proto(#class_name, class_name(__VA_ARGS__));

// Does a to-script conversion on the proto, turning doubles into IoNumber and strings into IoSeq, etc.
#define LM_ADD_NATIVE_PROTO(vm_name, class_name, ...) vm_name.add_proto(#class_name, class_name(__VA_ARGS__), true);

#define LM_ADD_PROTOS_IMPL(r, data, elem) LM_ADD_PROTO(data, elem)
#define LM_ADD_PROTOS(vm_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_ADD_PROTOS_IMPL, vm_name, SEQ)

// Like LM_ADD_PROTO but doesn't add parens to make it a constructor call
#define LM_ADD_VALUE(vm_name, value_name, ...) vm_name.add_proto(#value_name, value_name);

#define LM_ADD_VALUES_IMPL(r, data, elem) LM_ADD_VALUE(data, elem)
#define LM_ADD_VALUES(vm_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_ADD_VALUES_IMPL, vm_name, SEQ)

// Add vector<class_name> to vm with name "vector_of_class_name"
#include <vector>
#define LM_ADD_VECTOR(vm_name, class_name) vm_name.add_proto("vector_of_" #class_name, std::vector<class_name>());

// Add vectors for several classes.
#define LM_ADD_VECTORS_IMPL(r, data, elem) LM_ADD_VECTOR(data, elem)
#define LM_ADD_VECTORS(vm_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_ADD_VECTORS_IMPL, vm_name, SEQ)

#define LM_CLASS(namespace, class_name) auto& class_name##_LM = register_class<class_name>(#class_name, namespace);
#define LM_CLASS_NO_COPY(namespace, class_name) auto& class_name##_LM = register_class<class_name, false>(#class_name, namespace);
#define LM_ENUM(namespace, class_name) auto& class_name##_LM = register_enum<class_name>(#class_name, namespace);

#define LM_FUNC_IMPL(r, data, elem) bind_method<data>(data##_LM, BOOST_PP_STRINGIZE(elem), &data::elem);
#define LM_FUNC(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_FUNC_IMPL, class_name, SEQ)

#define LM_STATIC_MEMBER_FUNC_IMPL(r, data, elem) bind_static_method(data##_LM, BOOST_PP_STRINGIZE(elem), &data::elem);
#define LM_STATIC_MEMBER_FUNC(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_STATIC_MEMBER_FUNC_IMPL, class_name, SEQ)

#define LM_EXTENSION_METHOD_IMPL(r, data, elem) bind_nonmember_op(data##_LM, BOOST_PP_STRINGIZE(elem), &elem);
#define LM_EXTENSION_METHOD(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_EXTENSION_METHOD_IMPL, class_name, SEQ)
#define LM_EXTENSION_METHOD_OVERLOAD(class_name, given_func_name, actual_func, ret_type, ...) bind_nonmember_op(class_name##_LM, given_func_name, static_cast<ret_type (*)(__VA_ARGS__)>(&actual_func));

#define LM_FUNC_OVERLOAD(class_name, given_func_name, actual_func, ret_type, ...) bind_method(class_name##_LM, given_func_name, static_cast<ret_type (class_name::*)(__VA_ARGS__)>(&class_name::actual_func));
#define LM_FUNC_OVERLOAD_CONST(class_name, given_func_name, actual_func, ret_type, ...) bind_method(class_name##_LM, given_func_name, static_cast<ret_type (class_name::*)(__VA_ARGS__) const>(&class_name::actual_func));
#define LM_OP_OVERLOAD(class_name, CONST, op, ret_type, ...) bind_method(class_name##_LM, #op, static_cast<ret_type (class_name::*)(__VA_ARGS__) CONST>(&class_name::operator op));

// For LM_FUNC_OVERLOAD_BOTH
template <typename T> struct LM_InsertConst { typedef T const type; };
template <typename T> struct LM_InsertConst<T*> { typedef T const* type; };
template <typename T> struct LM_InsertConst<T&> { typedef T const& type; };

#define LM_FUNC_OVERLOAD_BOTH(class_name, actual_func, ret_type, ...) LM_FUNC_OVERLOAD_CONST(class_name, #actual_func "_c", actual_func, LM_InsertConst<ret_type>::type, __VA_ARGS__) LM_FUNC_OVERLOAD(class_name, #actual_func "_nc", actual_func, ret_type, __VA_ARGS__)

#define LM_OP_IMPL(r, data, elem) bind_method(data##_LM, BOOST_PP_STRINGIZE(elem), &data::operator elem);
#define LM_OP(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_OP_IMPL, class_name, SEQ)

#define LM_CONSTR(class_name, constructor_name, ...) bind_constructor<class_name>(class_name##_LM, constructor_name, TypePack<__VA_ARGS__>());

// Your LikeMagic Class objects must be named with the class name followed by "_LM" (do not provide the _LM to the macro)
#define LM_BASE(class_name, base_name) add_base(class_name##_LM, base_name##_LM);

#define LM_FIELD_IMPL(r, data, elem) bind_field(data##_LM, BOOST_PP_STRINGIZE(elem), &data::elem);
#define LM_FIELD(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_FIELD_IMPL, class_name, SEQ)

#define LM_BLOCK_IMPL(r, data, elem) bind_field(data##_LM, "On" BOOST_PP_STRINGIZE(elem), &data::BOOST_PP_CAT(On,elem));
#define LM_BLOCK(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_BLOCK_IMPL, class_name, SEQ)

#define LM_ARRAY_FIELD_IMPL(r, data, elem) bind_array_field(data##_LM, BOOST_PP_STRINGIZE(elem), &data::elem);
#define LM_ARRAY_FIELD(class_name, SEQ) BOOST_PP_SEQ_FOR_EACH(LM_ARRAY_FIELD_IMPL, class_name, SEQ)

#define LM_STATIC_FUNC(class_name, func_name) bind_static_method(class_name##_LM, #func_name, class_name::func_name);
#define LM_STATIC_FUNC_NAME(class_name, given_func_name, actual_func) bind_static_method(class_name##_LM, given_func_name, class_name::actual_func);
#define LM_STATIC_FUNC_OVERLOAD(class_name, given_func_name, actual_func, ret_type, ...) bind_static_method(class_name##_LM, given_func_name, static_cast<ret_type (*)(__VA_ARGS__)>(&class_name::actual_func));
