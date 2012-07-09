#pragma once

#include "AbstractOutput.hpp"

#include <string>
#include <iostream>

namespace Iocaste {
    namespace Debugger {

class StreamOutput :
    public AbstractOutput<std::string>
{
private:
    std::ostream& stream;
    bool add_newline;

public:
    StreamOutput(std::ostream& stream_, bool add_newline_=false);
    virtual void WriteData(std::string const& data);
};

    }
}

