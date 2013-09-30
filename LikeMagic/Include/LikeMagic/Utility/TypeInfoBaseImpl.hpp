// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "boost/functional/hash.hpp"
#include <string>

namespace LM {

class TypeInfoBaseImpl : public AbstractTypeInfo
{
public:

    virtual ~TypeInfoBaseImpl() {}

    virtual bool operator <(const AbstractTypeInfo& that) const
    {
        if (this->get_system() < that.get_system())
            return true;
        else if (that.get_system() < this->get_system())
            return false;
        else
            return this->less(that);
    }

    virtual bool operator ==(const AbstractTypeInfo& that) const
    {
        if (this->get_system() != that.get_system())
            return false;
        else
            return this->equals(that);
    }

    virtual bool get_is_const() const { return false; }

    virtual TypeInfoPtr class_type() const { return TypeInfoPtr(this); }
    virtual TypeInfoPtr as_const() const { return TypeInfoPtr(this); }
    virtual TypeInfoPtr as_nonconst() const { return TypeInfoPtr(this); }
    virtual TypeInfoPtr as_ptr() const { return TypeInfoPtr(this); }
    virtual TypeInfoPtr as_value() const { return TypeInfoPtr(this); }

    virtual std::size_t hash_value() const
    {
        size_t result = 0;
        boost::hash_combine(result, get_system());
        boost::hash_combine(result, calc_hash());
        return result;
    }
};

}
