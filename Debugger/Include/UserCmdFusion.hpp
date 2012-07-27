
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "UserCmd.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::SetOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::SetOption::Pair,
    (string, first)
    (string, second)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::ShowOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::SetBreakpoint,
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::Source,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::Directory,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::TTY,
    (std::string, device_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::Run,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd,
    (boost::optional<std::string>, raw_string)
    (boost::optional<UserCmd::SetOption>, set_option)
    (boost::optional<UserCmd::ShowOption>, show_option)
    (boost::optional<UserCmd::SetBreakpoint>, set_breakpoint)
    (boost::optional<UserCmd::Source>, source)
    (boost::optional<UserCmd::Directory>, directory)
    (boost::optional<UserCmd::TTY>, tty)
    (boost::optional<UserCmd::Run>, run)
)

