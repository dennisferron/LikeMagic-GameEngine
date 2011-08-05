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

class ScriptUtil
{
public:
    static std::string ptr_addr_to_str(void* p);
    static void* get_null_ptr();
    static void* get_test_ptr(std::string hex_str);
    static bool get_true();
    static bool get_false();
    static double get_double(double value);
    static int get_int(int value);

    // Instance fields to test member field setting
    void* voidp_field;
    char* charp_field;
    unsigned char* ucharp_field;
    int* intp_field;
    unsigned int* uintp_field;
};

}
