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

    TypeIndex result_type;
    std::string conv_name;

public:

    StaticCastConv(TypeIndex result_type_, std::string conv_name_) : result_type(result_type_), conv_name(conv_name_) {}

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
            result_type,  // The result type might not be identical to the typeof T*
            expr // Reference to original expr to ensure target obj not collected.
        );
    }

    virtual std::string description() const { return describe_converter<From, To>("StaticCastConv(" + conv_name + " " + result_type.description() + ")"); }

    virtual float cost() const { return 1.0f; }
};

}
