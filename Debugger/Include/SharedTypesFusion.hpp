#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "SharedTypes.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::AddressIn,
    (SharedTypes::GdbAddress, address)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::FromModule,
    (std::string, module_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::AtFile,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbAddress,
    (std::string, hex_value)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::ValueAsString,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::NoLocals,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbValue,
    (SharedTypes::GdbValue::value_type, value)
    (boost::optional<
        SharedTypes::ValueAsString
    >, value_as_string)
)

BOOST_FUSION_ADAPT_STRUCT(
    SharedTypes::GdbResponseFunctionArg,
    (std::string, name)
    (std::string, equals)
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
    (std::string, equals)
    (boost::optional<SharedTypes::TypeCast>, type_cast)
    (SharedTypes::GdbValue, value)
)
