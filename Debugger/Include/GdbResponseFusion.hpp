#include "SharedTypesFusion.hpp"
#include "GdbResponse.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::Banner,
    (std::string, version)
    (std::string, msg)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::ProgramExited,
    (std::string, how)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::TestStr1,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::TestStr2,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::UninitializedVariant,
    (double, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::Empty,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::RawStr,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::ReadingSymbols,
    (std::string, message)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::BreakpointSet,
    (int, breakpoint_number)
    (SharedTypes::GdbAddress, address)
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::BreakpointHit,
    (int, breakpoint_number)
    (SharedTypes::GdbResponseFunction, function)
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::AddressInFunction,
    (SharedTypes::AddressIn, address_in)
    (SharedTypes::GdbResponseFunction, function)
)


BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::BacktraceLine,

    (int, backtrace_number)

    (boost::optional<
        SharedTypes::AddressIn
    >, address_in)

    (SharedTypes::GdbResponseFunction, function)

    (boost::optional<
        SharedTypes::FromModule
    >, module)

    (boost::optional<
        SharedTypes::AtFile
    >, file_name)

    (boost::optional<
        int
    >, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::CursorPos,
    (std::string, file_name)
    (int, line_number)
    (int, char_number)
    (std::string, unknown)
    (SharedTypes::GdbAddress, address)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::LocalsInfo,
    (GdbResponses::LocalsInfo::locals_type, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    GdbResponses::ValueHistory,
    (int, number)
    (std::string, equals)
    (SharedTypes::GdbValue, value)
)

