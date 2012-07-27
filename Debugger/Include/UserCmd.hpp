
#pragma once

#include <string>
#include "boost/optional.hpp"

namespace Iocaste { namespace Debugger {

struct UserCmd
{
    boost::optional<std::string> raw_string;

    struct SetOption
    {
        std::string name;
        boost::optional<std::string> modifier;
        std::string value;
    };
    boost::optional<SetOption> set_option;

    struct SetBreakpoint
    {
        std::string file_name;
        int line_number;
    };
    boost::optional<SetBreakpoint> set_breakpoint;

    UserCmd() {}

    UserCmd(std::string str) :
        raw_string(str)
        {}

    UserCmd(UserCmd::SetOption set_option_) :
        set_option(set_option_)
        {}

    UserCmd(UserCmd::SetBreakpoint set_breakpoint_) :
        set_breakpoint(set_breakpoint_)
        {}

    void Parse(std::string str);
    void Write(std::string& str) const;
};

}}
