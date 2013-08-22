// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/StdBindings/StdBindings.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "LikeMagic/MarkableObjGraph.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

#include "IoObject.h"

#include "LikeMagic/TypeConv/NumberConv.hpp"
#include "LikeMagic/TypeConv/StringConv.hpp"
#include "LikeMagic/TypeConv/IteratorConv.hpp"

#include "LikeMagic/BindingMacros.hpp"

#include "boost/preprocessor/seq/for_each.hpp"

#include "LikeMagic/ScriptUtil.hpp"

#include <sstream>

#define add_num_conv(type_sys, type) \
add_conv<type, type const&, NumberConv>(); \
add_conv<type&, type, NumberConv>(); \
add_conv<type const&, type, NumberConv>(); \
add_conv<type, double, NumberConv>(); \
add_conv<type, double const&, NumberConv>(); \
add_conv<type&, double, NumberConv>(); \
add_conv<type&, double const&, NumberConv>(); \
add_conv<type const&, double, NumberConv>(); \
add_conv<type const&, double const&, NumberConv>();

#define add_all_num_conv_impl(r, data, elem) add_num_conv(data, elem);
#define add_all_num_conv(type_sys, SEQ) BOOST_PP_SEQ_FOR_EACH(add_all_num_conv_impl, type_sys, SEQ)

using namespace LM;
using namespace std;

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

void LM::add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_std = register_namespace("std", global_ns);

    typedef std::map<s32, IoObject*> map_of_s32_IoObject;
    LM_CLASS(ns_std, map_of_s32_IoObject)
    LM_CONSTR(map_of_s32_IoObject, "new")

    LM_EXTENSION_METHOD(map_of_s32_IoObject, (at)(atPut)(removeAt))

    // Add the abstract type system itself as a class.
    LM_CLASS_NO_COPY(global_ns, TypeSystem)
    LM_FUNC(TypeSystem, (global_namespace))

    LM_CLASS_NO_COPY(global_ns, CallTarget)

    LM_CLASS_NO_COPY(global_ns, TypeMirror)
    LM_FUNC(TypeMirror, (get_class_name)(get_class_type)(get_instance_size))

    LM_CLASS(global_ns, TypeIndex)
    LM_FUNC(TypeIndex, (description))

    LM_CLASS(global_ns, MarkableObjGraph)
    LM_FUNC(MarkableObjGraph, (number_of_parents)(number_of_children))

    LM_CLASS(global_ns, string)
    LM_CLASS(global_ns, wstring)

    // Register number types as copyable but do not auto-deref
    register_class<short, true, false>("short", global_ns);
    register_class<unsigned short, true, false>("ushort", global_ns);
    register_class<int, true, false>("int", global_ns);
    register_class<unsigned int, true, false>("uint", global_ns);
    register_class<long, true, false>("long", global_ns);
    register_class<unsigned long, true, false>("ulong", global_ns);
    register_class<double, true, false>("double", global_ns);
    register_class<float, true, false>("float", global_ns);

    // Do auto-deref bool though
    register_class<bool, true, true>("bool", global_ns);

    register_class<unsigned char, true, false>("uchar", global_ns);

    LM_CLASS(global_ns, wchar_t)

    LM_CLASS(global_ns, Delegate)

    add_all_num_conv(type_sys, (signed char)(short)(int)(long)(unsigned char)(unsigned short)(unsigned int)(unsigned long)(float)(double))

    // Allow string conversions
    add_conv<  std::string&,    std::wstring,   StringConv>();
    add_conv<  std::string&,    wchar_t const*, StringConv>();
    add_conv<  std::string&,    char const*,    StringConv>();

    add_conv<  std::wstring,    std::string,    StringConv>();
    add_conv<  std::wstring&,   std::string,    StringConv>();
    add_conv<  wchar_t const*,  std::string,    StringConv>();

    // When IoNil is encountered, it is marshaled as a NullExpr<void*> object,
    // which is an expression   of type of void* that always returns NULL.
    // Some fancy magic happens in try_conv to intercept the void* NULL value
    // and replace it with a NullExpr of the appropriate pointer type for the function argument.
    add_conv<void*&, void*>();

    // Allow char*& terms to be converted to char* values.
    add_conv<  char const*&,    char const*,    ImplicitConv>();
    add_conv<  unsigned char const*&,    unsigned char const*,    ImplicitConv>();
    add_conv<  char*&, char*,    ImplicitConv>();
    add_conv<  unsigned char*&,    unsigned char*,    ImplicitConv>();
    add_conv<  void const*&,    void const*,    ImplicitConv>();
    add_conv<  void*, void* const&, NumberConv>();

    // enable std::vector conversions to pointers for primitives
    //register_collection<unsigned short>("ushort");
    register_class<std::vector<int>>("vector_of_int", ns_std);
    register_class<std::vector<unsigned int>>("vector_of_uint", ns_std);
    register_class<std::vector<short>>("vector_of_short", ns_std);
    register_class<std::vector<unsigned short>>("vector_of_ushort", ns_std);

    typedef vector<string> vector_of_string;
    LM_CLASS(ns_std, vector_of_string)
    LM_FUNC(vector_of_string, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_string, at, string&, vector_of_string::size_type)

    typedef vector<float> vector_of_float;
    LM_CLASS(ns_std, vector_of_float)
    LM_CONSTR(vector_of_float, "new",)

    // Although default parameters won't work for functions with LikeMagic,
    // it is possible to specify constructors that leave some parameters at their defaults.
    LM_CONSTR(vector_of_float, "new", size_t)

    LM_FUNC(vector_of_float, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_float, at, float&, vector_of_float::size_type)
    LM_FUNC_OVERLOAD(vector_of_float, "begin_nc", begin, vector_of_float::iterator)
    LM_FUNC_OVERLOAD_CONST(vector_of_float, "begin_c", begin, vector_of_float::const_iterator)
    LM_FUNC_OVERLOAD(vector_of_float, "push_back", push_back, void, vector_of_float::value_type const&)
    LM_EXTENSION_METHOD_OVERLOAD(vector_of_float, "at_put", at_put, void, vector_of_float&, size_t, float const&)

    // These three lines allow converting a vector iterator to a pointer into the array.
    typedef vector_of_float::iterator vector_of_float_iterator;
    LM_CLASS(ns_std, vector_of_float_iterator)
    add_conv<vector_of_float_iterator, float*, IteratorConv>();

    typedef NativeArray<float> NativeArray_of_float;
    LM_CLASS(global_ns, NativeArray_of_float)
    LM_CONSTR(NativeArray_of_float, "new", size_t)
    LM_CONSTR(NativeArray_of_float, "new", size_t, float*)
    LM_FUNC(NativeArray_of_float, (begin_c)(begin_nc)(at_c)(at_nc)(at_put)(size))


    typedef vector<double> vector_of_double;
    LM_CLASS(ns_std, vector_of_double)
    LM_CONSTR(vector_of_double, "new",)

    // Although default parameters won't work for functions with LikeMagic,
    // it is possible to specify constructors that leave some parameters at their defaults.
    LM_CONSTR(vector_of_double, "new", size_t)

    LM_FUNC(vector_of_double, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_double, at, double&, vector_of_double::size_type)
    LM_FUNC_OVERLOAD(vector_of_double, "begin_nc", begin, vector_of_double::iterator)
    LM_FUNC_OVERLOAD_CONST(vector_of_double, "begin_c", begin, vector_of_double::const_iterator)
    LM_FUNC_OVERLOAD(vector_of_double, "push_back", push_back, void, vector_of_double::value_type const&)
    LM_EXTENSION_METHOD_OVERLOAD(vector_of_double, "at_put", at_put, void, vector_of_double&, size_t, double const&)

    // These three lines allow converting a vector iterator to a pointer into the array.
    typedef vector_of_double::iterator vector_of_double_iterator;
    LM_CLASS(ns_std, vector_of_double_iterator)
    add_conv<vector_of_double_iterator, double*, IteratorConv>();

    typedef NativeArray<double> NativeArray_of_double;
    LM_CLASS(global_ns, NativeArray_of_double)
    LM_CONSTR(NativeArray_of_double, "new", size_t)
    LM_CONSTR(NativeArray_of_double, "new", size_t, double*)
    LM_FUNC(NativeArray_of_double, (begin_c)(begin_nc)(at_c)(at_nc)(at_put)(size))

    LM_CLASS(global_ns, ScriptUtil)
    LM_CONSTR(ScriptUtil, "new",)
    LM_FIELD(ScriptUtil, (voidp_field)(charp_field)(ucharp_field)(intp_field)(uintp_field))
    LM_STATIC_MEMBER_FUNC(ScriptUtil, (ptr_addr_to_str)(get_null_ptr)(get_test_ptr)(get_true)(get_false)(get_void_ptr)
    (get_int)(get_double)(get_string)(get_float)(get_random_float)(get_random_float_array)(print_float_array)(is_nan)
    (get_script_path)(set_script_path))
}


