
#pragma once

#include <string>
#include "boost/optional.hpp"

namespace Iocaste { namespace Debugger {

// To add a new UserCmd, the following steps must be taken:
//
//  - define the new struct inside struct UserCmd in UserCmd.hpp
//  - define a boost::optional member of that struct type to UserCmd
//  - overload UserCmd's constructor to set that member
//  - add a binding for the new struct type in UserCmdFusion.hpp
//  - add a member to the UserCmd binding in the same header file
//  - declare & define a rule to parse it in UserCmdParser.cpp
//  - add " | your_new_rule" to the start rule in UserCmdParser.cpp
//  - declare & define a rule to parse it in UserCmdWriter.cpp
//  - add " << -your_new_rule" to the start rule in UserCmdWriter.cpp
//  - add a debug print message "got 'x' rule" << members in UserCmdWriter.cpp
//
//  Furthermore,
//      - The order of the boost::fusion binding must match the order of the
//        more-specific rule alternatives in the start rules.
//
//  If you get "error cannot initialize 'UserCmd' with 'your_new_cmd&'":
//      - Check your UserCmd constructor overload
//
//  If you get "error cannot initialize 'your_new_cmd' with 'UserCmd&'"
//   or "error no type named 'const_iterator' in 'your_new_cmd':
//      - You're missing a boost fusion definition
//
//  If you get other compile errors
//      - Check your rules' attributes
//
//  If you did all this and it (at runtime) fails to parse, did you:
//      - Forget to add " | your_rule" to the parser start rule?
//      - Have a subrule that's eating chars belonging to the next subrule?

struct UserCmd
{
    boost::optional<std::string> raw_string;

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
    boost::optional<SetOption> set_option;

    struct ShowOption
    {
        std::string name;
        boost::optional<std::string> modifier;
    };
    boost::optional<ShowOption> show_option;

    struct SetBreakpoint
    {
        std::string file_name;
        int line_number;
    };
    boost::optional<SetBreakpoint> set_breakpoint;

    struct Source
    {
        std::string file_name;
    };
    boost::optional<Source> source;

    struct Directory
    {
        std::string file_name;
    };
    boost::optional<Directory> directory;

    struct TTY
    {
        std::string device_name;
    };
    boost::optional<TTY> tty;

    struct Run
    {
        boost::optional<std::string> dummy;
    };
    boost::optional<Run> run;

    UserCmd() {}

    UserCmd(std::string str) :
        raw_string(str)
        {}

    UserCmd(UserCmd::SetOption set_option_) :
        set_option(set_option_)
        {}

    UserCmd(UserCmd::ShowOption show_option_) :
        show_option(show_option_)
        {}

    UserCmd(UserCmd::SetBreakpoint set_breakpoint_) :
        set_breakpoint(set_breakpoint_)
        {}

    UserCmd(UserCmd::Source source_) :
        source(source_)
        {}

    UserCmd(UserCmd::Directory directory_) :
        directory(directory_)
        {}

    UserCmd(UserCmd::TTY tty_) :
        tty(tty_)
        {}

    UserCmd(UserCmd::Run run_) :
        run(run_)
        {}

    void Parse(std::string str);
    void Write(std::string& str) const;
};

}}
