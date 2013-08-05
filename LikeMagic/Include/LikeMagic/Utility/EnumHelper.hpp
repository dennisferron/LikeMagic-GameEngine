// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <iostream>

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

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
