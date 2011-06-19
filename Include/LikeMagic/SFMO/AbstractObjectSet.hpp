// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <typeinfo>

namespace LikeMagic { namespace SFMO {

class AbstractObjectSet
{
public:
    virtual ~AbstractObjectSet() {}
    virtual void reset() = 0;
    virtual bool at_end() const = 0;
    virtual void advance() = 0;
    virtual std::string obj_type_descr() = 0;
};

}}
