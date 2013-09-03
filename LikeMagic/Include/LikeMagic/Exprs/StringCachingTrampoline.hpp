// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Expr.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"

#include <iostream>

namespace LM {

// When converting strings to char* or references, the conversion is unsafe in Exprs expressions if a new string has to be generated
// unless this temporary string is stored away somewhere for the pointer to have
// something durable to refer to while the Exprs expression exists.
// This class should probably not be used for other kind of casts.
template <typename From, typename To, typename Converter>
class StringCachingAdapter : public Expression<To>
{
private:
    typedef typename boost::remove_const<typename boost::remove_reference<To>::type>::type CacheType;

    ExprPtr from_expr;
    CacheType cached_String;
    std::string test_String;

    StringCachingAdapter(ExprPtr expr) : from_expr(expr) {}

public:

    static ExprPtr create(ExprPtr expr)
    {
        return new StringCachingAdapter(expr);
    }

    inline virtual To eval()
    {
        cached_String = Converter::do_conv(try_conv<From>(from_expr)->eval());
        // Here we may be returning a reference to the cached value instead of by-value.
        return cached_String;
    }

    virtual std::string description() const
    {
        return "converts " + from_expr->description() + " from " + LM::TypeDescr<From>::text() + " to " + Expr::description();
    }

    virtual void mark() const
    {
        from_expr->mark();
    }
};

}
