// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/Mirrors/CallTarget.hpp"

using namespace LikeMagic::Mirrors;

CallTarget::~CallTarget()
{
}

// Some methods (like constructors) should not be inherited.
virtual bool CallTarget::is_inherited() const
{
    return true;
}

