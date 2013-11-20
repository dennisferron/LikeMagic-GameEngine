
#include "SharedTypesFusion.hpp"
#include "UserCmd.hpp"

BOOST_FUSION_ADAPT_STRUCT(
    Rules::RawString,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Return,
    (boost::optional<std::string>, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::WhatIs,
    (std::string, cmd)
    (boost::optional<std::string>, expr)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::SetOptionWithModifier,
    (std::string, name)
    (std::string, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::SetOptionNoModifier,
    (std::string, name)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::SetOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::ShowOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::SetBreakpoint,
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::SetBreakpointOnFunction,
    (std::string, function_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Source,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Directory,
    (std::string, file_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::TTY,
    (std::string, device_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Run,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Info,
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Backtrace,
    (boost::optional<int>, num_frames)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Quit,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::StepMode,
    (std::string, cmd)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::PrintWorkingDirectory,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::Empty,
    (boost::optional<std::string>, dummy)
)

BOOST_FUSION_ADAPT_STRUCT(
    Rules::PrintFunction,
    (std::string, function_name)
    (std::vector<Rules::GdbValue>, args)
)

