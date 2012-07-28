#pragma once

#include <string>
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
    boost::optional<std::string> dummy;
};

}

typedef  boost::variant
<
    GdbResponses::Banner,
    GdbResponses::ReadingLibs,
    GdbResponses::Empty
> GdbResponse;

}}
