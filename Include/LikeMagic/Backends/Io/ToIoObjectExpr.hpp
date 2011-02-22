// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Expression.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Backends/Io/API_Io.hpp"
#include "LikeMagic/Backends/Io/ToIoTypeInfo.hpp"

#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace Backends { namespace Io {

using LikeMagic::SFMO::ExprPtr;
using LikeMagic::SFMO::Expression;
using LikeMagic::Utility::TypeIndex;

class AbstractToIoObjectExpr : public AbstractExpression
{
public:

    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m) = 0;

    virtual boost::intrusive_ptr<Expression<IoObject*>> clone() const
    {
        throw std::logic_error("clone not implemented yet");
    }

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

    virtual LikeMagic::Utility::TypeIndex get_type() const
    {
        return ToIoTypeInfo::create_index();
    }

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m)
    {
        return F::eval_in_context(self, locals, m, from_expr->eval());
    }

    virtual std::string description() const
    {
        return "ToIoObjectExpr";
        /*
        return
          "To-Io expression from C++ type "
        + BetterTypeInfo::create<T>().describe()
        + " to Io type "
        + get_type().describe();
        */
    }

    virtual void mark() const { from_expr->mark(); }

};


}}}
