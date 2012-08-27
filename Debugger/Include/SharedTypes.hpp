#pragma once

#include <string>
#include <vector>
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace Iocaste { namespace Debugger { namespace SharedTypes {

struct GdbAddress
{
    std::string hex_value;
};

struct GdbValue
{
    typedef boost::variant<
        int, std::string, GdbAddress
    > value_type;
    value_type value;
    boost::optional<std::string> value_as_string;
};

struct GdbResponseFunctionArg
{
    std::string name;
    GdbValue value;
};

struct GdbResponseFunction
{
    std::string name;
    std::vector<GdbResponseFunctionArg> args;
};

struct TypeCast
{
    std::string value;
};

struct VariableEquals
{
    std::string name;
    boost::optional<TypeCast> type_cast;
    GdbValue value;
};

}}}
