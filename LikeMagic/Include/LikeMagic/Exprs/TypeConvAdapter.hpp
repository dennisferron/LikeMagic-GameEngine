// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/TypeSystem.hpp"

namespace LM {

// Adapts an expression of one type so that it can be used as another type.
template <typename From, typename To>
class TypeConvAdapter : public Expr
{
private:
    ExprPtr from_expr;
    ConvImpl const& conv;

    TypeConvAdapter(ExprPtr expr, ConvImpl const& conv_) : from_expr(expr), conv(conv_)
    {
    }

public:
    static ExprPtr create(ExprPtr expr, ConvImpl const& conv)
    {
        return new TypeConvAdapter(expr, conv);
    }

    virtual ValuePtr get_ptr_value()
    {
        return conv.do_conv(from_expr->get_value_ptr());
    }

    virtual std::string description() const
    {
        return "(" + from_expr->description() + " from " + LM::TypeDescr<From>::text() + " to " + Expr::description() + ")";
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
