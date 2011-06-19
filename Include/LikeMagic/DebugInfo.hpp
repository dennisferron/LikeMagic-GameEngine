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

class DebugInfo
{
private:
    std::string name;

public:
    std::string get_debug_name() const { return name; }
    void set_debug_name(std::string debug_name) { name = debug_name; }
};

}
