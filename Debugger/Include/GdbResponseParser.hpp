#pragma once

#include "AbstractOutput.hpp"
#include "GdbResponse.hpp"
#include <string>

namespace Iocaste { namespace Debugger {

class GdbResponseParser : public AbstractOutput<std::string>
{
private:
    AbstractOutput<GdbResponse>& sink;

public:
    GdbResponseParser(AbstractOutput<GdbResponse>& sink_);
    virtual void WriteData(std::string input);
};

}}
