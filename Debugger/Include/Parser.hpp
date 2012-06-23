
#pragma once

#include <string>

namespace Iocaste {
    namespace Debugger {

struct SetPrompt
{
    std::string new_prompt;
};

struct SetBreakpoint
{
    std::string file_name;
    int line_number;
};

bool Parse(std::string str, SetPrompt& prompt);
bool Parse(std::string str, SetBreakpoint& breakpoint);

    }
}
