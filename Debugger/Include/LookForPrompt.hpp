#pragma once

#include "AbstractInput.hpp"
#include "AbstractAdapter.hpp"

#include <string>
#include <iostream>

namespace Iocaste {
    namespace Debugger {

class LookForPrompt :
    public AbstractAdapter<std::string>
{
private:
    std::string buffer;
    std::string end_marker_str;
    AbstractOutput<std::string>& output;
    AbstractInput<std::string>& end_marker_queue;

public:
    LookForPrompt(AbstractOutput<std::string>& output_, AbstractInput<std::string>& end_marker_queue_);
    virtual void WriteData(std::string const& data);
};

    }
}
