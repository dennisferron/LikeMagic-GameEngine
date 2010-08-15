// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Expression.hpp"

namespace LikeMagic { namespace SFMO {

// Adapts an expression of one type so that it can be used as another type.
template <typename From, typename To, typename Converter>
class Trampoline : public Expression<To>
{
private:
    boost::intrusive_ptr<Expression<From>> from_expr;

    Trampoline(boost::intrusive_ptr<Expression<From>> expr) : from_expr(expr)
    {
    }

public:
    static boost::intrusive_ptr<Expression<To>> create(ExprPtr expr)
    {
        boost::intrusive_ptr<Expression<To>> result = new Trampoline(reinterpret_cast<Expression<From>*>(expr.get()));
        return result;
    }

    inline virtual To eval()
    {
        return Converter::do_conv(from_expr->eval());
    }

    virtual boost::intrusive_ptr<Expression<To>> clone() const { return new Trampoline(from_expr); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return from_expr->get_objsets(); }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return from_expr->is_lazy(); }

    virtual std::string description() const
    {
        return "(" + from_expr->description() + " from " + LikeMagic::Utility::TypeDescr<From>::text() + " to " + LikeMagic::Utility::TypeDescr<To>::text() + ")";
    }

    virtual void mark() const
    {
        from_expr->mark();
    }

};

}}
