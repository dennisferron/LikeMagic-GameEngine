// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic { namespace Utility {

// Detects if type is legal to use as qualifier for member function pointer.
template<typename T>
class ICanHasMemberFunc
{
private:
    typedef char Yes;
    typedef struct { char a[2]; } No;
    template<typename U> static Yes test(void (U::*f)());
    template<typename U> static No test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(Yes) };
};

}}
