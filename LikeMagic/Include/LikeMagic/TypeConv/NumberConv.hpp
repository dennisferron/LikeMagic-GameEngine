// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"

namespace LM {

// A major difference between NumberConv and StaticCast conv is that the
// number converter casts by value, creating an all-new term; it does not need the expr after.
template <typename From, typename To>
class NumberConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        // Don't need to return a "reference" here because
        // the number converter creates a new To-value not a To-pointer
        // as the StaticCastConv did.
        ExprPtr result = Term<To>::create(
            static_cast<To>(
                *reinterpret_cast<From const*>(
                    expr->get_value_ptr().as_const)));
        return result;
    }

    virtual std::string description() const { return describe_converter<From, To>("NumberConv(new Term)"); }
    virtual float cost() const { return 10.0; }
};

}
