// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "Iocaste/LikeMagicAdapters/ToIoTypeInfo.hpp"

#include <iostream>
#include <stdexcept>

namespace Iocaste { namespace LMAdapters {

using LM::ExprPtr;
using LM::Expr;
using LM::TypeIndex;

class AbstractToIoObjectExpr : public IMarkable
{
protected:
    TypeIndex io_type;

public:
    AbstractToIoObjectExpr(ValuePtr ptr, TypeIndex type) : io_type(type) {}
    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m) = 0;
    virtual TypeIndex get_type() const { return io_type; }
};

template <typename T, typename F>
class ToIoObjectExpr : public AbstractToIoObjectExpr
{
private:
    ExprPtr from_expr;
    F io_func;

    ToIoObjectExpr(ExprPtr from_expr_, F io_func_)
        : AbstractToIoObjectExpr(nullptr, ToIoTypeInfo::create_index()),
            from_expr(from_expr_), io_func(io_func_) {}

public:

    static ExprPtr create(ExprPtr from_expr, F io_func)
    {
        AbstractToIoObjectExpr* result = new ToIoObjectExpr<T, F>(from_expr, io_func);
        return create_expr(result, result->get_type());
    }

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m)
    {
        ExprPtr ward;
        return io_func(self, locals, m, EvalAs<T>::value(from_expr, ward));
    }

    virtual std::string description() const
    {
        return "ToIoObjectExpr from " + from_expr->description();
    }

    virtual void mark() const { from_expr->mark(); }
};

}}
