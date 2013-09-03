// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Term.hpp"

namespace LM {



// This type converter allows bound functions to get ahold of the outer expression object,
// rather than what is inside the expression object.  It allows you to write functions that
// work with any expression.

class ToExprConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Term<ExprPtr>::create(expr);
    }

    virtual std::string description() const { return "ToExprConv"; }
};

}
