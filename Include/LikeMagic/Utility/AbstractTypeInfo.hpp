// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <typeinfo>
#include <stdexcept>

namespace LikeMagic { namespace Utility {

class AbstractTypeInfo
{
protected:

    virtual std::type_info const* comparator_typeid() const = 0;
    virtual bool less(const AbstractTypeInfo& that) const = 0;

public:

    bool operator <(const AbstractTypeInfo& that) const
    {
        if (this->comparator_typeid() < that.comparator_typeid())
            return true;
        else if (that.comparator_typeid() < this->comparator_typeid())
            return false;
        else
            return this->less(that);
    }

    bool operator ==(const AbstractTypeInfo& that) const
    {
        return !(*this<that) && !(that<*this);
    }

    virtual std::string describe() const = 0;
};

}}
