
#pragma once

#include <string>

namespace Iocaste { namespace Debugger {

struct UserCmd
{
    std::string raw_string;
};

struct UserSetOption : public UserCmd
{
    std::string name;
    std::string value;
};

}}
