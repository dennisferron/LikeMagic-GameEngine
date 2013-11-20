#pragma once

#include <string>

namespace IoDbg {

struct ActivityLogLine
{
    std::string label;
    std::string content;

    void Parse(std::string str);
    void Write(std::string& generated) const;
};

}
