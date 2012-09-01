#pragma once

#include <string>
#include <vector>
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace Iocaste { namespace Debugger { namespace SharedTypes {

struct FromModule
{
    std::string module_name;
};

struct AtFile
{
    std::string file_name;
};

struct GdbAddress
{
    std::string hex_value;
};

struct AddressIn
{
    GdbAddress address;
};

struct ValueAsString
{
    std::string text;
};

struct NoLocals
{
    std::string text;
};

struct GdbValue
{
    typedef boost::variant<
        int, std::string, GdbAddress
    > value_type;
    value_type value;
    boost::optional<
        ValueAsString
    > value_as_string;
};

struct GdbResponseFunctionArg
{
    std::string name;
    std::string equals;
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
    std::string equals;
    boost::optional<TypeCast> type_cast;
    GdbValue value;
};

}}}
