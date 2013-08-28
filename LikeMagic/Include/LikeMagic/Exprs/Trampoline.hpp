// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Exprs/Expression.hpp"
#include "LikeMagic/TypeSystem.hpp"

namespace LM {

// Adapts an expression of one type so that it can be used as another type.
template <typename From, typename To, typename Converter>
class Trampoline : public Expression<To>
{
private:
    ExprPtr from_expr;

    Trampoline(ExprPtr expr) : from_expr(expr)
    {
    }

public:
    static ExprPtr create(ExprPtr expr)
    {
        ExprPtr result = new Trampoline(expr);
        return result;
    }

    inline virtual To eval()
    {
        return Converter::do_conv(LM::try_conv<From>(from_expr)->eval());
    }

    virtual std::string description() const
    {
        return "(" + from_expr->description() + " from " + LM::TypeDescr<From>::text() + " to " + AbstractExpression::description() + ")";
    }

    virtual void mark() const
    {
        from_expr->mark();
    }

    virtual bool is_terminal() const
    {
        return false;
    }
};

}
