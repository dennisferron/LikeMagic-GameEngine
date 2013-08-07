// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/StdBindings/StdBindings.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

#include "IoObject.h"

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/NamespacePath.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"
#include "LikeMagic/TypeConv/IteratorConv.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

#include "boost/preprocessor/seq/for_each.hpp"

#include "LikeMagic/ScriptUtil.hpp"

#include <sstream>

#define add_num_conv(type_sys, type) \
type_system->add_conv<type, type const&, NumberConv>(); \
type_system->add_conv<type&, type, NumberConv>(); \
type_system->add_conv<type const&, type, NumberConv>(); \
type_system->add_conv<type, double, NumberConv>(); \
type_system->add_conv<type, double const&, NumberConv>(); \
type_system->add_conv<type&, double, NumberConv>(); \
type_system->add_conv<type&, double const&, NumberConv>(); \
type_system->add_conv<type const&, double, NumberConv>(); \
type_system->add_conv<type const&, double const&, NumberConv>();

#define add_all_num_conv_impl(r, data, elem) add_num_conv(data, elem);
#define add_all_num_conv(type_sys, SEQ) BOOST_PP_SEQ_FOR_EACH(add_all_num_conv_impl, type_sys, SEQ)

using namespace LikeMagic;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::Utility;

using namespace std;

using namespace LikeMagic;

typedef int s32;

// Extension methods

IoObject* at(std::map<s32, IoObject*> const& self, s32 key)
{
    auto result = self.find(key);
    if (result == self.end())
        return NULL;
    else
        return result->second;
}

IoObject* atPut(std::map<s32, IoObject*>& self, s32 key, IoObject* value)
{
    return self[key] = value;
}

void removeAt(std::map<s32, IoObject*>& self, s32 key)
{
    self.erase(key);
}


// Vector helper.  Assignment in Io cannot (?) be overloaded; it creates new
// slots rather than copying values.  This allows us to assign values to vector elements.
template <typename T>
void at_put(vector<T>& target, size_t pos, T const& value)
{
    target.at(pos) = value;
}

void LikeMagic::StdBindings::add_bindings(TypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_std = Namespace::global->subspace("std");

    typedef std::map<s32, IoObject*> map_of_s32_IoObject;
    LM_CLASS(ns_std, map_of_s32_IoObject)
    LM_CONSTR(map_of_s32_IoObject,,)
    LM_EXTENSION_METHOD(map_of_s32_IoObject, (at)(atPut)(removeAt))

    Namespace global_ns = Namespace::global(type_sys);

    // Add the abstract type system itself as a class.
    LM_CLASS_NO_COPY(global_ns, TypeSystem)
    LM_FUNC(TypeSystem, (set_leak_memory)(leak_memory)(add_type_system_observer))

    LM_CLASS_NO_COPY(global_ns, AbstractCppObjProxy)

    LM_CLASS_NO_COPY(global_ns, CallTarget)

    LM_CLASS_NO_COPY(global_ns, TypeMirror)
    LM_FUNC(TypeMirror, (get_class_name)(get_type)(create_class_proxy)(get_namespace)(get_method_names)(get_size))

    LM_CLASS(global_ns, TypeIndex)
    LM_FUNC(TypeIndex, (describe))

    LM_CLASS(global_ns, NamespacePath)
    LM_FUNC(NamespacePath, (is_root)(get_name)(get_parent)(to_string))

    LM_CLASS(global_ns, Namespace)
    LM_FUNC(Namespace, (subspace))
    Namespace_LM.bind_static_method("global", Namespace::global);

    LM_CLASS(global_ns, DebugInfo)
    LM_FUNC(DebugInfo, (set_debug_name)(get_debug_name))

    LM_CLASS(global_ns, MarkableObjGraph)
    LM_BASE(MarkableObjGraph, DebugInfo)
    LM_FUNC(MarkableObjGraph, (number_of_parents)(number_of_children))

    LM_CLASS(global_ns, string)
    LM_CLASS(global_ns, wstring)

    // Register number types as copyable but do not auto-deref
    type_system->register_class<short, true, false>("short");
    type_system->register_class<unsigned short, true, false>("ushort");
    type_system->register_class<int, true, false>("int");
    type_system->register_class<unsigned int, true, false>("uint");
    type_system->register_class<long, true, false>("long");
    type_system->register_class<unsigned long, true, false>("ulong");
    type_system->register_class<double, true, false>("double");
    type_system->register_class<float, true, false>("float");

    // Do auto-deref bool though
    type_system->register_class<bool, true, true>("bool");

    type_system->register_class<unsigned char, true, false>("uchar");

    LM_CLASS(global_ns, wchar_t)
    LM_CLASS(global_ns, AbstractDelegate)

    add_all_num_conv(type_sys, (signed char)(short)(int)(long)(unsigned char)(unsigned short)(unsigned int)(unsigned long)(float)(double))

    // Allow string conversions
    type_system->add_conv<  std::string&,    std::wstring,   StringConv>();
    type_system->add_conv<  std::string&,    wchar_t const*, StringConv>();
    type_system->add_conv<  std::string&,    char const*,    StringConv>();

    type_system->add_conv<  std::wstring,    std::string,    StringConv>();
    type_system->add_conv<  std::wstring&,   std::string,    StringConv>();
    type_system->add_conv<  wchar_t const*,  std::string,    StringConv>();

    // When IoNil is encountered, it is marshaled as a NullExpr<void*> object,
    // which is an expression   of type of void* that always returns NULL.
    // Some fancy magic happens in try_conv to intercept the void* NULL value
    // and replace it with a NullExpr of the appropriate pointer type for the function argument.
    type_system->add_conv<void*&, void*>();

    // Allow char*& terms to be converted to char* values.
    type_system->add_conv<  char const*&,    char const*,    ImplicitConv>();
    type_system->add_conv<  unsigned char const*&,    unsigned char const*,    ImplicitConv>();
    type_system->add_conv<  char*&, char*,    ImplicitConv>();
    type_system->add_conv<  unsigned char*&,    unsigned char*,    ImplicitConv>();
    type_system->add_conv<  void const*&,    void const*,    ImplicitConv>();
    type_system->add_conv<  void*, void* const&, NumberConv>();

    // enable std::vector conversions to pointers for primitives
    //register_collection<unsigned short>("ushort");
    type_system->register_class<std::vector<int>>("vector_of_int");
    type_system->register_class<std::vector<unsigned int>>("vector_of_uint");
    type_system->register_class<std::vector<short>>("vector_of_short");
    type_system->register_class<std::vector<unsigned short>>("vector_of_ushort");

    typedef vector<string> vector_of_string;
    LM_CLASS(global_ns, vector_of_string)
    LM_FUNC(vector_of_string, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_string, at, string&, vector_of_string::size_type)

    typedef vector<float> vector_of_float;
    LM_CLASS(global_ns, vector_of_float)
    LM_CONSTR(vector_of_float,,)

    // Although default parameters won't work for functions with LikeMagic,
    // it is possible to specify constructors that leave some parameters at their defaults.
    LM_CONSTR(vector_of_float,, size_t)

    LM_FUNC(vector_of_float, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_float, at, float&, vector_of_float::size_type)
    LM_FUNC_OVERLOAD(vector_of_float, "begin_nc", begin, vector_of_float::iterator)
    LM_FUNC_OVERLOAD_CONST(vector_of_float, "begin_c", begin, vector_of_float::const_iterator)
    LM_FUNC_OVERLOAD(vector_of_float, "push_back", push_back, void, vector_of_float::value_type const&)
    LM_EXTENSION_METHOD_OVERLOAD(vector_of_float, "at_put", at_put, void, vector_of_float&, size_t, float const&)

    // These three lines allow converting a vector iterator to a pointer into the array.
    typedef vector_of_float::iterator vector_of_float_iterator;
    LM_CLASS(global_ns, vector_of_float_iterator)
    type_system->add_conv<vector_of_float_iterator, float*, IteratorConv>();

    typedef NativeArray<float> NativeArray_of_float;
    LM_CLASS(global_ns, NativeArray_of_float)
    LM_CONSTR(NativeArray_of_float,, size_t)
    LM_CONSTR(NativeArray_of_float,, size_t, float*)
    LM_FUNC(NativeArray_of_float, (begin_c)(begin_nc)(at_c)(at_nc)(at_put)(size))


    typedef vector<double> vector_of_double;
    LM_CLASS(global_ns, vector_of_double)
    LM_CONSTR(vector_of_double,,)

    // Although default parameters won't work for functions with LikeMagic,
    // it is possible to specify constructors that leave some parameters at their defaults.
    LM_CONSTR(vector_of_double,, size_t)

    LM_FUNC(vector_of_double, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_double, at, double&, vector_of_double::size_type)
    LM_FUNC_OVERLOAD(vector_of_double, "begin_nc", begin, vector_of_double::iterator)
    LM_FUNC_OVERLOAD_CONST(vector_of_double, "begin_c", begin, vector_of_double::const_iterator)
    LM_FUNC_OVERLOAD(vector_of_double, "push_back", push_back, void, vector_of_double::value_type const&)
    LM_EXTENSION_METHOD_OVERLOAD(vector_of_double, "at_put", at_put, void, vector_of_double&, size_t, double const&)

    // These three lines allow converting a vector iterator to a pointer into the array.
    typedef vector_of_double::iterator vector_of_double_iterator;
    LM_CLASS(global_ns, vector_of_double_iterator)
    type_system->add_conv<vector_of_double_iterator, double*, IteratorConv>();

    typedef NativeArray<double> NativeArray_of_double;
    LM_CLASS(global_ns, NativeArray_of_double)
    LM_CONSTR(NativeArray_of_double,, size_t)
    LM_CONSTR(NativeArray_of_double,, size_t, double*)
    LM_FUNC(NativeArray_of_double, (begin_c)(begin_nc)(at_c)(at_nc)(at_put)(size))

    LM_CLASS(global_ns, ScriptUtil)
    LM_CONSTR(ScriptUtil,,)
    LM_FIELD(ScriptUtil, (voidp_field)(charp_field)(ucharp_field)(intp_field)(uintp_field))
    LM_STATIC_MEMBER_FUNC(ScriptUtil, (ptr_addr_to_str)(get_null_ptr)(get_test_ptr)(get_true)(get_false)(get_void_ptr)
    (get_int)(get_double)(get_string)(get_float)(get_random_float)(get_random_float_array)(print_float_array)(is_nan)
    (get_script_path)(set_script_path))
}


