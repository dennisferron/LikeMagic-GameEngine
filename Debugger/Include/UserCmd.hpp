
#pragma once

#include "SharedTypes.hpp"

namespace Iocaste { namespace Debugger {

// To add a new UserCmd:
//  - Define its struct here
//  - Add it to the UserCmd variant typedef here
//  - Bind the struct in UserCmdFusion.hpp
//  - Add a parse rule for it in UserCmdParser.cpp
//  - Add its parse rule to the parse start rule
//  - Add a debug printer for it in UserCmdWriter.cpp
//  - Add a write rule for it
//  - Add it to the writer's start rule

namespace UserCmds
{
    struct RawString
    {
        std::string value;
    };

    struct PrintFunction
    {
        std::string function_name;
        std::vector<SharedTypes::GdbValue> args;
    };

    struct SetOption
    {
        std::string name;
        boost::optional<std::string> modifier;
        std::string value;

        SetOption() {}

        // This enables initializing SetOption without a modifier in the qi rule.
        typedef std::pair<std::string, std::string> Pair;
        SetOption(Pair p)
            : name(p.first), value(p.second) {}
    };


    struct ShowOption
    {
        std::string name;
        boost::optional<std::string> modifier;
    };


    struct SetBreakpoint
    {
        std::string file_name;
        int line_number;
    };

    struct SetBreakpointOnFunction
    {
        std::string function_name;
    };

    struct Source
    {
        std::string file_name;
    };


    struct Directory
    {
        std::string file_name;
    };


    struct TTY
    {
        std::string device_name;
    };


    struct Run
    {
        boost::optional<std::string> dummy;
    };


    struct Info
    {
        std::string value;
    };


    struct Backtrace
    {
        boost::optional<int> num_frames;
    };


    struct Next
    {
        boost::optional<std::string> dummy;
    };


    struct Step
    {
        boost::optional<std::string> dummy;
    };


    struct Finish
    {
        boost::optional<std::string> dummy;
    };

    struct Quit
    {
        boost::optional<std::string> dummy;
    };

    struct Empty
    {
        boost::optional<std::string> dummy;
    };
}

typedef  boost::variant
<
    UserCmds::RawString,
    UserCmds::PrintFunction,
    UserCmds::SetOption,
    UserCmds::ShowOption,
    UserCmds::SetBreakpoint,
    UserCmds::SetBreakpointOnFunction,
    UserCmds::Source,
    UserCmds::Directory,
    UserCmds::TTY,
    UserCmds::Run,
    UserCmds::Info,
    UserCmds::Backtrace,
    UserCmds::Next,
    UserCmds::Step,
    UserCmds::Finish,
    UserCmds::Quit,
    UserCmds::Empty
> UserCmd;

}}
