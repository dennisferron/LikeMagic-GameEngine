#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "SharedTypes.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbAddress,
    (std::string, hex_value)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbValue,
    (SharedTypes::GdbValue::value_type, value)
    (boost::optional<std::string>, value_as_string)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbResponseFunctionArg,
    (std::string, name)
    (SharedTypes::GdbValue, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbResponseFunction,
    (std::string, name)
    (std::vector<SharedTypes::GdbResponseFunctionArg>, args)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::TypeCast,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::VariableEquals,
    (std::string, name)
    (boost::optional<SharedTypes::TypeCast>, type_cast)
    (SharedTypes::GdbValue, value)
)
