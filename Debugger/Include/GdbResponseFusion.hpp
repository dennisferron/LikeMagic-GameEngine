#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "GdbResponse.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;


BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::Banner,
    (std::string, version)
    (std::string, msg)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::Empty,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::ReadingLibs,
    (std::string, periods)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::BreakpointSet,
    (int, breakpoint_number)
    (unsigned long long, address)
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::CursorPos,
    (std::string, file_name)
    (int, line_number)
    (int, char_number)
    (std::string, unknown)
    (unsigned long long, address)
)
