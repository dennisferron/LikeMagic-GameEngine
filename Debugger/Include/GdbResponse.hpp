#pragma once

#include <string>
#include <vector>
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace Iocaste { namespace Debugger {

namespace GdbResponses
{

struct Banner
{
    std::string version;
    std::string msg;
};

struct Empty
{
    boost::optional<std::string> dummy;
};

struct ReadingLibs
{
    std::string periods;
};

struct BreakpointSet
{
    int breakpoint_number;
    unsigned long long address;
    std::string file_name;
    int line_number;
};

struct CursorPos
{
    std::string file_name;
    int line_number;
    int char_number;
    std::string unknown;
    unsigned long long address;
};

struct BreakpointHit
{
    int breakpoint_number;
    std::string function;
    std::string args;
    std::string file_name;
    int line_number;
};

struct LocalsInfo
{
    std::string msg;
};

}

typedef  boost::variant
<
    GdbResponses::Banner,
    GdbResponses::ReadingLibs,
    GdbResponses::BreakpointSet,
    GdbResponses::CursorPos,
    GdbResponses::BreakpointHit,
    GdbResponses::LocalsInfo,
    GdbResponses::Empty
> GdbResponseType;

struct GdbResponse
{
    std::vector<GdbResponseType> values;
    std::string prompt;
};

}}
