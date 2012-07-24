
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
    const typeinfo& tag;
    union data {
        std::string raw_string;
        UserSetOption set_option;
    };

    UserCmd(std::string str) :
        tag(typeid(std::string)),
        data.raw_string(str)
        {}

    UserCmd(UserSetOption set_option_) :
        tag(typeid(UserSetOption)),
        data.set_option(set_option_)
        {}
};

}}
