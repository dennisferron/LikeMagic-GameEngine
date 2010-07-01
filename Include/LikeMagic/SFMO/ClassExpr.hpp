// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "Expression.hpp"

#include "../Utility/TypeDescr.hpp"
#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace SFMO {

// "LikeMagic classes" protos do not have a C++ object attached because they
// represent C++ classes, not instances, yet there has to be a proxy in order
// to call LikeMagic methods on it.  This is a catch-22:  you have to call
// a "new" method to make an instance in the first place!  This special expression
// type is the solution to that catch-22:  it is an expression that cannot
// be evaluated, but serves

template <typename T>
class ClassExpr : public Expression<T>
{
private:
    ClassExpr() {}

public:
    static boost::intrusive_ptr<Expression<T>> create() { return new ClassExpr(); }

    inline virtual T eval()
    {
        throw std::logic_error(description() + " represents a class from C++. " +
                " Only constructors and proxy methods can be called on C++ class protos." +
                " To call a member method, first call a constructor (using new or tmp) to make an instance of this class.");
    }

    virtual boost::intrusive_ptr<Expression<T>> clone() const { return new ClassExpr(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("C++ class " + TypeDescr<T>::text());
    }

    virtual void mark() const {}
};

}}
