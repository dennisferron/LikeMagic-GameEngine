
#pragma once

#include <string>

namespace Iocaste {
    namespace Debugger {

struct SetPrompt
{
    std::string new_prompt;
};

bool Parse(std::string str, SetPrompt& prompt);

    }
}
