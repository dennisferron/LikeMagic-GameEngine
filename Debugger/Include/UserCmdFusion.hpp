
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "UserCmd.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::RawString,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::SetOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::SetOption::Pair,
    (string, first)
    (string, second)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::ShowOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::SetBreakpoint,
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Source,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Directory,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::TTY,
    (std::string, device_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Run,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Info,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Backtrace,
    (boost::optional<int>, num_frames)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Next,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Step,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Finish,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Quit,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmds::Empty,
    (boost::optional<std::string>, dummy)
)
