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

#include "boost/type_traits/is_pointer.hpp"

namespace LM {

template <typename From, typename To>
class StaticCastConv : public AbstractTypeConverter
{
private:
    static_assert(boost::is_pointer<From>::value, "Conversion must take place by pointers.");
    static_assert(boost::is_pointer<To>::value, "Conversion must take place by pointers.");

    struct Impl : public ConvImpl
    {
        virtual ValuePtr do_conv(ValuePtr value) const
        {
            return
                static_cast<To>(
                    reinterpret_cast<From>(
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
