#pragma once

#include "AbstractInput.hpp"
#include "AbstractAdapter.hpp"
#include "StringWithPrompt.hpp"

#include <iostream>

namespace Iocaste {
    namespace Debugger {

class RecombinePrompt :
    public AbstractAdapter<StringWithPrompt>
{
private:
    std::string buffer;
    std::string end_marker_str;
    AbstractOutput<std::string>& output;

public:
    RecombinePrompt(AbstractOutput<std::string>& output_);
    virtual void WriteData(StringWithPrompt const& data);
};

    }
}
