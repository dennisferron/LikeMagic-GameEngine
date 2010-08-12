// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Expression.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"

#include <iostream>

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

// Adapts an expression of one type so that it can be used as another type.
// Numeric casts to references are unsafe in SFMO expressions unless the intermediate result is stored away somewhere
// for the reference to have something durable to refer to.
// I think this is because C++ reuses the same static or temporary memory location for all the type casts.
// This class should probably not be used for other kind of casts.
template <typename From, typename To, typename Converter>
class NumberCachingTrampoline : public Expression<To>
{
private:
    typedef typename boost::remove_const<typename boost::remove_reference<To>::type>::type CacheType;

    boost::intrusive_ptr<Expression<From>> from_expr;
    CacheType cached_number;

    NumberCachingTrampoline(boost::intrusive_ptr<Expression<From>> expr) : from_expr(expr) {}

public:

    static boost::intrusive_ptr<Expression<To>> create(ExprPtr expr)
    {
        return new NumberCachingTrampoline(reinterpret_cast<Expression<From>*>(expr.get()));
    }

    inline virtual To eval()
    {
        cached_number = Converter::do_conv(from_expr->eval());

        // Here we may be returning a reference to the cached value instead of by-value.
        return cached_number;
    }

    virtual boost::intrusive_ptr<Expression<To>> clone() const { return new NumberCachingTrampoline(from_expr); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return from_expr->get_objsets(); }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return from_expr->is_lazy(); }

    virtual std::string description() const
    {
        return "converts " + from_expr->description() + " from " + LikeMagic::Utility::TypeDescr<From>::text() + " to " + LikeMagic::Utility::TypeDescr<To>::text();
    }

    virtual void mark() const
    {
        from_expr->mark();
    }

};

}}
