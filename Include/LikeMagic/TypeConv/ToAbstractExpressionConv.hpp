// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "ConvertibleTo.hpp"
#include "../SFMO/Term.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

// This type converter allows bound functions to get ahold of the out expression object,
// rather than what is inside the expression object.  It allows you to write functions that
// work with any expression.

class ToAbstractExpressionConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Term<ExprPtr, true>::create(expr);
    }

    virtual std::string describe() const { return "ToAbstractExpressionConv"; }
};

}}
