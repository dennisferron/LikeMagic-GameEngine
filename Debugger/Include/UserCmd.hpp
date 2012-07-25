
#pragma once

#include <string>
#include "boost/optional.hpp"

namespace Iocaste { namespace Debugger {

struct UserSetOption
{
    std::string name;
    boost::optional<std::string> modifier;
    std::string value;
};

struct UserCmd
{
    boost::optional<std::string> raw_string;
    boost::optional<UserSetOption> set_option;

    UserCmd() {}

    UserCmd(std::string str) :
        raw_string(str)
        {}

    UserCmd(UserSetOption set_option_) :
        set_option(set_option_)
        {}

    void Parse(std::string str);
};

}}
