// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

template <int... N>
struct Test
{
    int x;
};

int main()
{
    Test<0> t1;
    Test<1,2,3> t2;
    return t2.x;
}

#include "LikeMagic/Mirrors/CallTarget.hpp"

using namespace LikeMagic::Mirrors;

CallTarget::~CallTarget()
{
}

// Some methods (like constructors) should not be inherited.
bool CallTarget::is_inherited() const
{
    return true;
}
