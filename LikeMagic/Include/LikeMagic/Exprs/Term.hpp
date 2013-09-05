// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expr.hpp"

namespace LM {

// By-Value case
template <typename R>
struct Term
{
    static ExprPtr create(R func_result)
    {
        Expr* result = new Expr(new R(func_result));
        result->set_auto_delete_ptr(true);
        return result;
    }
};

// Reference case
template <typename R>
struct Term<R&>
{
    static ExprPtr create(R& func_result)
    {
        return new Expr(&func_result);
    }
};

// Pointer case
template <typename R>
struct Term<R*>
{
    static ExprPtr create(R* func_result)
    {
        return new Expr(func_result);
    }
};

// Reference to pointer case
template <typename R>
struct Term<R*&>
{
    static ExprPtr create(R*& func_result)
    {
        return new Expr(&func_result);
    }
};

}
