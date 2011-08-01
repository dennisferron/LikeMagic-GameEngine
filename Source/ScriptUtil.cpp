// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/ScriptUtil.hpp"

#include <sstream>

using namespace std;
using namespace LikeMagic;

string ScriptUtil::ptr_addr_to_str(void* p)
{
    stringstream ss;
    ss << p;
    return ss.str();
}

void* ScriptUtil::get_null_ptr()
{
    return NULL;
}

void* ScriptUtil::get_test_ptr(string hex_str)
{
    void* result = 0;
    std::stringstream ss;
    ss << std::hex << hex_str;
    ss >> result;
    return result;
}
