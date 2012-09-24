#pragma once

#include "AbstractAdapter.hpp"
#include "GdbResponse.hpp"
#include "StringWithPrompt.hpp"

namespace Iocaste { namespace Debugger {

class GdbContextSensitiveParser : public AbstractAdapter<StringWithPrompt>
{
private:
    AbstractOutput<GdbResponseType>& sink;
    std::vector<GdbResponseType> Parse(std::string const& str) const;

public:
    GdbContextSensitiveParser(AbstractOutput<GdbResponse>& sink_);
    virtual void WriteData(StringWithPrompt const& input);
    void expect(std::vector<GdbResponseType> responses);
};

}}
>
