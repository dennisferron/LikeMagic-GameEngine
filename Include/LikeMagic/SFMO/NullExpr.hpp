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
#include <stdexcept>

namespace LikeMagic { namespace SFMO {

// Designates that an argument was a script nil object.  Nil can be converted to any pointer type.
struct NilExprTag {};

// When IoNil is encountered, it is marshaled as a NullExpr object.
// The type can be converted to any other pointer in TypeConvGraph.
template <typename T>
class NullExpr : public Expression<T>
{
    static_assert(boost::is_pointer<T>::value, "Cannot create NullExpr for type that is not a pointer!");
private:
    NullExpr() {}

public:
    static boost::intrusive_ptr<Expression<T>> create() { return new NullExpr(); }

    inline virtual T eval() { return NULL; }
    virtual boost::intrusive_ptr<Expression<T>> clone() const { return new NullExpr(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("NULL");
    }

    virtual void mark() const {}
};

}}
