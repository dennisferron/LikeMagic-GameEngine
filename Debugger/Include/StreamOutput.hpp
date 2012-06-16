#pragma

#include "AbstractInput.hpp"

#include <string>
#include <iostream>

namespace Iocaste {
    namespace Debugger {

class StreamOutput :
    public AbstractOutput<std::string>
{
private:
    std::ostream& stream;

public:
    StreamOutput(std::ostream& stream_);
    virtual void WriteData(std::string data);
};

    }
}

