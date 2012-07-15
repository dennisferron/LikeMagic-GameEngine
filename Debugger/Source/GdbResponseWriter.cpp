#include "GdbResponseWriter.hpp"
using namespace Iocaste::Debugger;

GdbResponseWriter::GdbResponseWriter(AbstractOutput<std::string>& sink_)
    : sink(sink_) {}

void GdbResponseWriter::WriteData(GdbResponse const& input)
{
    // TODO:  Actually write out the input...
    sink.WriteData(input.raw_string);
}
