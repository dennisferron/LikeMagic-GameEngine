// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractObjectSet.hpp"
#include "Expression.hpp"
#include <type_traits>

namespace LikeMagic { namespace SFMO {

template <typename T>
class LazyExpr : public Expression<T>
{
private:
    boost::intrusive_ptr<Expression<T>> wrapped_expr;

    LazyExpr(boost::intrusive_ptr<Expression<T>> expr_) : wrapped_expr(expr_) { }

public:

    static boost::intrusive_ptr<Expression<T>> create(boost::intrusive_ptr<Expression<T>> expr)
        { return new LazyExpr(expr); }

    virtual std::set<AbstractObjectSet*> get_objsets() const
    {
        return wrapped_expr->get_objsets();
    }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return true; }

    inline virtual T eval()
    {
        return wrapped_expr->eval();
    }

    virtual boost::intrusive_ptr<Expression<T>> clone() const { return new LazyExpr<T>(wrapped_expr); }

    virtual std::string description() const
    {
        return "lazy(" + wrapped_expr->description() + ")";
    }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() { wrapped_expr->mark(); }
};

template <>
class LazyExpr<void> : public Expression<void>
{
private:
    boost::intrusive_ptr<Expression<void>> wrapped_expr;

    LazyExpr(boost::intrusive_ptr<Expression<void>> expr_) : wrapped_expr(expr_) { }

public:

    static boost::intrusive_ptr<Expression<void>> create(boost::intrusive_ptr<Expression<void>> expr)
        { return new LazyExpr(expr); }

    virtual std::set<AbstractObjectSet*> get_objsets() const
    {
        return wrapped_expr->get_objsets();
    }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return true; }

    inline virtual void eval()
    {
        wrapped_expr->eval();
    }

    virtual boost::intrusive_ptr<Expression<void>> clone() const { return new LazyExpr<void>(wrapped_expr); }

    virtual std::string description() const
    {
        return "lazy(" + wrapped_expr->description() + ")";
    }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() { wrapped_expr->mark(); }

};

}}
