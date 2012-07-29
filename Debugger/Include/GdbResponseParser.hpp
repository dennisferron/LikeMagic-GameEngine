#pragma once

#include "AbstractAdapter.hpp"
#include "GdbResponse.hpp"
#include "StringWithPrompt.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseParser : public AbstractAdapter<StringWithPrompt>
{
private:
    AbstractOutput<GdbResponse>& sink;
    GdbResponse Parse(StringWithPrompt const& str) const;

public:
    GdbResponseParser(AbstractOutput<GdbResponse>& sink_);
    virtual void WriteData(StringWithPrompt const& input);
};

}}
