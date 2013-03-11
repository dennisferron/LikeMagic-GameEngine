// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <cxxabi.h>

#include <string>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

namespace LikeMagic { namespace Utility {

std::string demangle_name(std::string type_name)
{
    int status;
    char* buf = abi::__cxa_demangle(type_name.c_str(), 0, 0, &status);
    std::string result(buf);
    free(buf);
    return result;
}

}}
