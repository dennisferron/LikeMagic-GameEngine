// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LM {

// By-value case is same as a StaticCastConv.
template <typename From, typename To>
class NumberConv
{
    static_assert(sizeof(From) && sizeof(To) && false, "Only use converter by pointer types.");
};

// A major difference between NumberConv and StaticCast conv is that the
// number converter casts by value, creating an all-new term; it does not need the expr after.

template <typename From, typename To>
class NumberConv<From*, To*> : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
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
