// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include "boost/intrusive_ptr.hpp"

namespace LikeMagic { namespace Exprs {

class AbstractExpression;
typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;

}}

#include <string>

namespace LikeMagic { namespace TypeConv {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Exprs::ExprPtr;

class AbstractTypeConverter;
void intrusive_ptr_add_ref(AbstractTypeConverter const* p);
void intrusive_ptr_release(AbstractTypeConverter const* p);

class AbstractTypeConverter
{
private:
    friend void intrusive_ptr_add_ref(AbstractTypeConverter const* p);
    friend void intrusive_ptr_release(AbstractTypeConverter const* p);
    mutable int ref_count;

public:
    AbstractTypeConverter();
    virtual ~AbstractTypeConverter();
    virtual std::string description() const = 0;
    virtual ExprPtr wrap_expr(ExprPtr expr) const = 0;

    // Since the conversions are cached once figured out, there would be little benefit
    // to trying to optimize by using an integer cost, and using a float allows us
    // more flexibility in defining fractional costs for special cases.
    virtual float cost() const;
};

// Handy helper function
template <typename From, typename To>
std::string describe_converter(std::string converter_name)
{
    return
            converter_name +
            " from " + BetterTypeInfo::create_index<From>().description() +
            " to " + BetterTypeInfo::create_index<To>().description();
}

typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

}}
