/*
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "SharedTypes.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace IoDbg;

BOOST_FUSION_ADAPT_STRUCT(
    Rules::GdbStruct,
    (std::string, contents)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::AddressIn,
    (Rules::GdbAddress, address)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::FromModule,
    (std::string, module_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::AtFile,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::GdbAddress,
    (std::string, hex_value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::ValueAsString,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::ValueElided,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::NoLocals,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::ValueAsFunctionPtr,
    (std::string, text)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::GdbValue,
    (Rules::GdbValue_value_type, value)
    (boost::optional<
        Rules::ValueAsString
    >, value_as_string)
    (boost::optional<
        Rules::ValueAsFunctionPtr
    >, value_as_function_ptr)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::GdbResponseFunctionArg,
    (std::string, name)
    (std::string, equals)
    (GdbValue, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::GdbResponseFunction,
    (std::string, name)
    (std::vector<Rules::GdbResponseFunctionArg>, args)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::TypeCast,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::VariableEquals,
    (std::string, name)
    (std::string, equals)
    (boost::optional<Rules::TypeCast>, type_cast)
    (GdbValue, value)
)

*/
