// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"

namespace LM {



// For most implicit conv cases, just return obj.  One special case below.
template <typename From, typename To>
struct ImplicitConvImpl
{
    inline static To do_conv(From obj) { return obj; }
};

// When converting value to const reference, need to reference
// ***the_original_temporary***; which means we CAN'T accept it
// by value (because that creates a ***second*** temporary that
// would disappear when do_conv exits).  So, we must actually
// accept it as a const reference as well as return it as such.
// (And if this is called not for a value From type, but when
// From is in fact already a reference, it does no harm
// to accept that reference as a const & instead - we're
// turning it into a const To reference anyway.)
template <typename From, typename To>
struct ImplicitConvImpl<From, To const&>
{
    inline static To const& do_conv(From const& obj) { return obj; }
};


template <typename From, typename To>
class ImplicitConv : public ConvertibleTo<To>
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        Expression<From>* from_expr = static_cast<Expression<From>*>(expr.get());
        ExprPtr result = Trampoline<From, To, ImplicitConvImpl<From, To>>::create(
            from_expr
        );
        return result;
    }

    virtual std::string description() const { return describe_converter<From, To>("ImplicitConv"); }
};


}
