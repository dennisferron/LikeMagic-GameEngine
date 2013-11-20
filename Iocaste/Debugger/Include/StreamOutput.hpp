#pragma once

#include "AbstractOutput.hpp"

#include <string>
#include <iostream>

namespace IoDbg {

class StreamOutput :
    public AbstractOutput<std::string>
{
private:
    std::ostream& stream;
    bool add_newline;

public:
    StreamOutput(std::ostream& stream_, bool add_newline_=false);
    virtual ~StreamOutput();
    virtual void WriteData(std::string const& data);
};

}

