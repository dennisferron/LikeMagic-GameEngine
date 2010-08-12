// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include "boost/intrusive_ptr.hpp"

namespace LikeMagic { namespace SFMO {

class AbstractExpression;
typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;

}}

#include <string>

namespace LikeMagic { namespace TypeConv {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::SFMO::ExprPtr;

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
    virtual ~AbstractTypeConverter() {}
    virtual std::string describe() const = 0;
    virtual ExprPtr wrap_expr(ExprPtr expr) const = 0;
};

// Handy helper function
template <typename From, typename To>
std::string describe_converter(std::string converter_name)
{
    return
            "type_conv " + converter_name +
            " from " + BetterTypeInfo::create<From>()->describe() +
            " to " + BetterTypeInfo::create<To>()->describe();
}

typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

}}
