// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "LikeMagic/Exprs/TypeConvAdapter.hpp"

namespace LM {

template <typename From, typename To>
class StaticCastConv : public AbstractTypeConverter
{
private:
    struct Impl : public ConvImpl
    {
        virtual ValuePtr do_conv(ValuePtr value)
        {
            return
                static_cast<To*>(
                    reinterpret_cast<From*>(
                        GetValuePtr<From>::value(value)));
        }
    } impl;

public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return LM::TypeConvAdapter<From, To>::create(expr, impl);
    }

    virtual std::string description() const { return describe_converter<From, To>("StaticCastConv"); }
};

}
