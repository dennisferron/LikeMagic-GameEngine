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
#include "LikeMagic/BindingMacros.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#include "LikeMagic/StdBindings/ScriptUtil.hpp"

#include <sstream>

#include "LikeMagic/StdBindings/StdBindings.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#include "LikeMagic/StdBindings/ScriptUtil.hpp"

#include <sstream>

#define add_num_conv(type) \
add_conv<type, type const&, NumberConv>(); \
add_conv<type&, type, NumberConv>(); \
add_conv<type const&, type, NumberConv>(); \
/* \
add_conv<double, type, NumberConv>(); \
add_conv<double, type const&, NumberConv>(); \
add_conv<double&, type, NumberConv>(); \
add_conv<double&, type const&, NumberConv>(); \
add_conv<double const&, type, NumberConv>(); \
add_conv<double const&, type const&, NumberConv>(); */ \
add_conv<type, double, NumberConv>(); \
add_conv<type, double const&, NumberConv>(); \
add_conv<type&, double, NumberConv>(); \
add_conv<type&, double const&, NumberConv>(); \
add_conv<type const&, double, NumberConv>(); \
add_conv<type const&, double const&, NumberConv>();

#define add_all_num_conv_impl(r, data, elem) add_num_conv(elem);
#define add_all_num_conv(SEQ) BOOST_PP_SEQ_FOR_EACH(add_all_num_conv_impl,, SEQ)

using namespace LM;
using namespace std;


// Vector helper.  Assignment in Io cannot (?) be overloaded; it creates new
// slots rather than copying values.  This allows us to assign values to vector elements.
template <typename T>
void at_put(vector<T>& target, size_t pos, T const& value)
{
    target.at(pos) = value;
}

std::string wchar_to_string(wchar_t const* char_ptr)
{
    std::string result;

    while (*char_ptr++)
        result += (char)*char_ptr;

    return result;
}

std::wstring string_to_wstring(std::string const& src)
{
    std::wstring result;

    for (char ch : src)
        result += (wchar_t)ch;

    return result;
}

void add_string_convs();

STD_BINDINGS_API void LM::add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_std = register_namespace("std", global_ns);

    // Add the abstract type system itself as a class.
    LM_CLASS(global_ns, TypeSystem)
    LM_FUNC(TypeSystem, (global_namespace))

    LM_STATIC_FUNC_NAME(global_ns, "wchar_to_string", wchar_to_string)
    LM_STATIC_FUNC_NAME(global_ns, "string_to_wstring", string_to_wstring)

    LM_CLASS(global_ns, CallTarget)

    LM_CLASS(global_ns, TypeMirror)
    LM_FUNC(TypeMirror, (get_class_name)(get_class_type)(get_instance_size))

    LM_CLASS(global_ns, TypeIndex)
    LM_FUNC(TypeIndex, (description))

    LM_CLASS(global_ns, MarkableObjGraph)
    LM_FUNC(MarkableObjGraph, (number_of_parents)(number_of_children))

    LM_CLASS(global_ns, void)

    LM_CLASS(global_ns, string)
    LM_FUNC(string, (c_str))

    LM_CLASS(global_ns, wstring)
    LM_FUNC(wstring, (c_str))

    LM_CLASS(global_ns, short)
    typedef unsigned short ushort;
    LM_CLASS(global_ns, ushort)
    LM_CLASS(global_ns, int)
    typedef unsigned int uint;
    LM_CLASS(global_ns, uint)
    LM_CLASS(global_ns, long)
    typedef unsigned long ulong;
    LM_CLASS(global_ns, ulong)
    LM_CLASS(global_ns, double)
    LM_CLASS(global_ns, float)
    LM_CLASS(global_ns, bool)
    typedef unsigned char uchar;
    LM_CLASS(global_ns, uchar)
    LM_CLASS(global_ns, char)

    LM_CLASS(global_ns, Delegate)

    LM_CLASS(global_ns, wchar_t)
    LM_EXTENSION_METHOD(wchar_t, (wchar_to_string))

    add_conv<float, double, NumberConv>();
    add_conv<short, double, NumberConv>();
    add_conv<int, double, NumberConv>();
    add_conv<long, double, NumberConv>();
    add_conv<unsigned short, double, NumberConv>();
    add_conv<unsigned int, double, NumberConv>();
    add_conv<unsigned long, double, NumberConv>();

    add_conv<short, int, NumberConv>();
    add_conv<short, long, NumberConv>();
    //add_conv<int, long, NumberConv>();
    add_conv<unsigned short, int, NumberConv>();
    add_conv<unsigned short, long, NumberConv>();
    //add_conv<unsigned int, long, NumberConv>();

    // enable std::vector conversions to pointers for primitives
    typedef std::vector<int> vector_of_int;
    LM_CLASS(ns_std, vector_of_int)
    typedef std::vector<unsigned int> vector_of_uint;
    LM_CLASS(ns_std, vector_of_uint)
    typedef std::vector<short> vector_of_short;
    LM_CLASS(ns_std, vector_of_short)
    typedef std::vector<unsigned short> vector_of_ushort;
    LM_CLASS(ns_std, vector_of_ushort)

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
    //add_conv<vector_of_float_iterator, float*, IteratorConv>();

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
    //add_conv<vector_of_double_iterator, double*, IteratorConv>();

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
    )
}


