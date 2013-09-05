// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/ToExprConv.hpp"

using namespace LM;

ExprPtr ToExprConv::wrap_expr(ExprPtr expr) const
{
    return Term<ExprPtr>::create(expr);
}

std::string ToExprConv::description() const
{
    return "ToExprConv";
}
