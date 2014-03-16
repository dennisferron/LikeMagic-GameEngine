#pragma once

#include "GdbResponse.hpp"

#include "AbstractAdapter.hpp"
#include "StringWithPrompt.hpp"

namespace IoDbg {

class GdbResponseParser : public AbstractAdapter<StringWithPrompt>
{
private:
    AbstractOutput<Rules::GdbResponse>& sink;
    bool use_alt_parser;
    std::vector<Rules::GdbResponseType> Parse(std::string const& str) const;

public:
    GdbResponseParser(AbstractOutput<Rules::GdbResponse>& sink_);
    virtual ~GdbResponseParser();
    virtual void WriteData(StringWithPrompt const& input);
    void expectAltInput();
};

}
