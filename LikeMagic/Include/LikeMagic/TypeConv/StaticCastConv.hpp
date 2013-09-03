// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Adapter.hpp"

namespace LM {

template <typename From, typename To>
class StaticCastConv : public ConvertibleTo<To>
{
private:
    struct Impl : public ConvImpl
    {
        virtual void const* do_conv(void const* value)
        {
            return
                static_cast<To*>(
                    reinterpret_cast<From*>(
                        const_cast<void*>(value)));
        }
    } impl;

public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return LM::Adapter<From, To>::create(expr, impl);
    }

    virtual std::string description() const { return describe_converter<From, To>("StaticCastConv"); }
};

}
