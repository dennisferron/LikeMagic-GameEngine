// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <iostream>
#include "boost/lexical_cast.hpp"

#pragma once

namespace LikeMagic { namespace Utility {

template <typename E>
struct EnumHelper
{
    static bool equals(E a, E b) { return a == b; }
    static bool not_equals(E a, E b) { return a != b; }
    static int value(E e) { return static_cast<int>(e); }
    static std::string asString(E e) { return boost::lexical_cast<std::string>(value(e)); }
};

}}
