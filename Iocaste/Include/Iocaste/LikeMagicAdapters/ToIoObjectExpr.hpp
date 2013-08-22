// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expression.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "Iocaste/LikeMagicAdapters/ToIoTypeInfo.hpp"

#include <iostream>
#include <stdexcept>

namespace Iocaste { namespace LMAdapters {

using LM::ExprPtr;
using LM::Expression;
using LM::TypeIndex;

class AbstractToIoObjectExpr : public AbstractExpression
{
public:

    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m) = 0;

    virtual TypeIndex get_class_type() const { return this->get_type(); }

    // It's already a script object, so don't need to try to convert it a second time.
    virtual bool disable_to_script_conv() const { return true; }

    virtual bool is_null() const { return false; }
};

template <typename T, typename F>
class ToIoObjectExpr : public AbstractToIoObjectExpr
{
private:
    boost::intrusive_ptr<Expression<T>> from_expr;

private:
    ToIoObjectExpr(boost::intrusive_ptr<Expression<T>> from_expr_) : from_expr(from_expr_) {}

public:

    static ExprPtr create(ExprPtr from_expr)
    {
        AbstractExpression* from_ptr = from_expr.get();
        Expression<T>* from_exact = static_cast<Expression<T>*>(from_ptr);
        ToIoObjectExpr* result = new ToIoObjectExpr<T, F>(from_exact);
        return result;
    }

    virtual LM::TypeIndex get_type() const
    {
        return ToIoTypeInfo::create_index();
    }

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m)
    {
        return F::eval_in_context(self, locals, m, from_expr->eval());
    }

    virtual std::string description() const
    {
        return "ToIoObjectExpr from " + from_expr->description();
    }

    virtual void mark() const { from_expr->mark(); }

};


}}
