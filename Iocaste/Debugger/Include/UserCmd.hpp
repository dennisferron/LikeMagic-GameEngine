
#pragma once

#include "SharedTypes.hpp"

namespace IoDbg {

// To add a new UserCmd:
//  - Define its struct here
//  - Add it to the UserCmd variant typedef here
//  - Bind the struct in UserCmdFusion.hpp
//  - Add a parse rule for it in UserCmdParser.cpp
//  - Add its parse rule to the parse start rule
//  - Add a debug printer for it in UserCmdWriter.cpp
//  - Add a write rule for it
//  - Add it to the writer's start rule

namespace Rules
{
    struct RawString
    {
        std::string value;
    };

    struct PrintFunction
    {
        std::string function_name;
        std::vector<Rules::GdbValue> args;
    };

    struct SetOptionWithModifier
    {
        std::string name;
        std::string modifier;
        std::string value;
    };

    struct SetOptionNoModifier
    {
        std::string name;
        std::string value;
    };

    struct SetOption
    {
        std::string name;
        boost::optional<std::string> modifier;
        std::string value;

        SetOption() {}

        SetOption(SetOptionWithModifier that) :
            name(that.name), modifier(that.modifier),
                value(that.value) {}

        SetOption(SetOptionNoModifier that) :
            name(that.name),
                value(that.value) {}
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


    struct StepMode
    {
        std::string cmd;
    };

    struct Quit
    {
        boost::optional<std::string> dummy;
    };

    struct Return
    {
        // (need something called GdbExpression perhaps)
        boost::optional<std::string> value;
    };

    struct PrintWorkingDirectory
    {
        boost::optional<std::string> dummy;
    };

    struct WhatIs
    {
        std::string cmd;
        boost::optional<std::string> expr;
    };
/*
    struct Empty
    {
        boost::optional<std::string> dummy;
    };
*/

typedef  boost::variant
<
    Rules::RawString,
    Rules::PrintFunction,
    Rules::SetOption,
    Rules::ShowOption,
    Rules::SetBreakpoint,
    Rules::SetBreakpointOnFunction,
    Rules::Source,
    Rules::Directory,
    Rules::TTY,
    Rules::Run,
    Rules::Info,
    Rules::Backtrace,
    Rules::StepMode,
    Rules::Quit,
    Rules::Return,
    Rules::PrintWorkingDirectory,
    Rules::WhatIs,
    Rules::Empty
> UserCmd;

}}
