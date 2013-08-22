// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"

namespace LM {



// The difference between implicit conv and no change conv
// is implicit conversion wraps the expression in a trampoline and
// returns the wrapped value unchanged, whereas no change conv
// doesn't even do that much - there's no trampoline, it simply
// asserts that the expression itself is a different expression.

template <typename From=void, typename To=void>
class NoChangeConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return expr;
    }

    virtual std::string description() const { return "NoChangeConv"; }

    // A no-change conversion is virtually free.
    virtual float cost() const { return 0.01; }
};

}
