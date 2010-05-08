
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

class AbstractTypeConverter
{
public:
    virtual ~AbstractTypeConverter() {}
    virtual std::string describe() const = 0;
    virtual ExprPtr wrap_expr(ExprPtr expr) const = 0;
};

// Handy helper function
template <typename From, typename To>
std::string describe_converter(std::string converter_name)
{
    return
            converter_name +
            " from " + BetterTypeInfo::create<From>().describe() +
            " to " + BetterTypeInfo::create<To>().describe();
}


}}
