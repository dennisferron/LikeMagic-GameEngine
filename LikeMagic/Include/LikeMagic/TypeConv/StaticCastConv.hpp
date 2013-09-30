// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "boost/type_traits/is_pointer.hpp"

namespace LM {

template <typename From, typename To>
class StaticCastConv : public AbstractTypeConverter
{
private:
    static_assert(boost::is_pointer<From>::value, "Conversion must take place by pointers.");
    static_assert(boost::is_pointer<To>::value, "Conversion must take place by pointers.");

public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        // Although we calculate the to-value immediately,
        // we return a "reference" to ensure the original
        // storage location does not get collected.
        return create_reference(
            static_cast<To>(
                reinterpret_cast<From>(
                    GetValuePtr<From>::value(
                         expr->get_value_ptr()))),
            TypId<To>::get(), expr);
    }

    virtual std::string description() const { return describe_converter<From, To>("StaticCastConv"); }

    virtual float cost() const { return 1.0f; }
};

}
