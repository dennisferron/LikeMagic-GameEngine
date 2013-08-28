// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Expression.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"

#include <iostream>

namespace LM {



// Adapts an expression of one type so that it can be used as another type.
// Numeric casts to references are unsafe in Exprs expressions unless the intermediate result is stored away somewhere
// for the reference to have something durable to refer to.
// I think this is because C++ reuses the same static or temporary memory location for all the type casts.
// This class should probably not be used for other kind of casts.
template <typename From, typename To, typename Converter>
class NumberCachingTrampoline : public Expression<To>
{
private:
    typedef typename boost::remove_const<typename boost::remove_reference<To>::type>::type CacheType;

    ExprPtr from_expr;
    CacheType cached_number;

    NumberCachingTrampoline(ExprPtr expr) : from_expr(expr) {}

public:

    static ExprPtr create(ExprPtr expr)
    {
        return new NumberCachingTrampoline(expr);
    }

    inline virtual To eval()
    {
        cached_number = Converter::do_conv(try_conv<From>(from_expr)->eval());

        // Here we may be returning a reference to the cached value instead of by-value.
        return cached_number;
    }

    virtual std::string description() const
    {
        return "converts " + from_expr->description() + " from " + LM::TypeDescr<From>::text() + " to " + LM::TypeDescr<To>::text();
    }

    virtual void mark() const
    {
        from_expr->mark();
    }

};

}
