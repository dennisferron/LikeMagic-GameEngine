// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/StaticCastConv.hpp"

namespace LM {

// By-value case is same as a StaticCastConv.
template <typename From, typename To>
class NumberConv : public StaticCastConv
{
public:
    virtual std::string description() const { return describe_converter<From, To>("NumberConv(static cast)"); }
    virtual float cost() const { return 10.0; }
};

// When the _destination_ type is a reference, we must create an lvalue to refer
// to (by creating a Term) EVEN IF To-type is a const reference.  Otherwise, if
// some part of this chain refers to a temporary, it might not still be around
// between when the expression is built and when it is used.

template <typename From, typename To>
class NumberConv<From, To&> : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Term<To>::create(
            static_cast<To>(
                EvalAs<From>::value(obj)));
    }

    virtual std::string description() const { return describe_converter<From, To&>("NumberConv(new Term)"); }
    virtual float cost() const { return 10.0; }
};

}
