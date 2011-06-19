// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "Expression.hpp"

#include "../Utility/TypeDescr.hpp"
#include <iostream>

namespace LikeMagic { namespace SFMO {

template <typename T>
class ConstructedTerm :
    public Expression<T&>
{
private:
    T value;

    template <typename... Args>
    ConstructedTerm(Args... args) : value(args...)
    {
    }

public:
    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args... args) { return new ConstructedTerm(args...); }

    inline virtual T& eval() { return value; }
    virtual boost::intrusive_ptr<Expression<T&>> clone() const { return new Term<T>(value); }
    virtual std::set<AbstractObjectSet*> get_objsets() { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const { return true; }

    virtual std::string description() const
    {
        return std::string("ConstructedObject<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }
};

}}
