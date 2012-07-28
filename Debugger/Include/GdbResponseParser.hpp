#pragma once

#include "AbstractAdapter.hpp"
#include "GdbResponse.hpp"
#include <string>

namespace Iocaste { namespace Debugger {

class GdbResponseParser : public AbstractAdapter<std::string>
{
private:
    AbstractOutput<GdbResponse>& sink;
    GdbResponse Parse(std::string str) const;

public:
    GdbResponseParser(AbstractOutput<GdbResponse>& sink_);
    virtual void WriteData(std::string const& input);
};

}}
