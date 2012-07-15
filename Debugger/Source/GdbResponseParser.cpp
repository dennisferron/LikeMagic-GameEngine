#include "GdbResponseParser.hpp"
using namespace Iocaste::Debugger;

GdbResponseParser::GdbResponseParser(AbstractOutput<GdbResponse>& sink_)
    : sink(sink_)
{
}

void GdbResponseParser::WriteData(std::string const& input)
{
    GdbResponse response;
    response.raw_string = input;
    sink.WriteData(response);
}
