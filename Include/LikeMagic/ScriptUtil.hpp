// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <string>

namespace LikeMagic
{

// Supports the same script functions as a vector, but this
// differs from std::vector in that it doesn't manage its own memory.
template <typename T>
class NativeArray
{
private:
    T* array;
    size_t arr_size;

public:
    NativeArray(size_t size_)
        : array(new T[size_]), arr_size(size_)
    {
    }

    NativeArray(size_t size_, T* array_)
        : array(array_), arr_size(size_)
    {
    }

    T* begin_nc() { return array; }
    T const* begin_c() { return array; }
    size_t size() { return arr_size; }
    T& at_nc(size_t pos) { return array[pos]; }
    T const& at_c(size_t pos) { return array[pos]; }
    void at_put(size_t pos, T const& value) { array[pos] = value; }
};

class ScriptUtil
{
public:
    static std::string ptr_addr_to_str(void const* p);
    static void* get_null_ptr();
    static void* get_test_ptr(std::string hex_str);
    static bool get_true();
    static bool get_false();
    static double get_double(double value);
    static int get_int(int value);
    static float get_float(float value);
    static void* get_void_ptr(void* value);

    static std::string get_string(std::string const& value);

    static float get_random_float(float min, float max);
    static float* get_random_float_array(int width, int height, float min, float max);

    static void print_float_array(float const* array, int width, int height);

    static bool is_nan(float f);

    // Instance fields to test member field setting
    void* voidp_field;
    char* charp_field;
    unsigned char* ucharp_field;
    int* intp_field;
    unsigned int* uintp_field;

    static std::string get_script_path();
    static void set_script_path(std::string value);
};

}
