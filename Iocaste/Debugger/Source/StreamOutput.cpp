#include "StreamOutput.hpp"

using namespace std;
using namespace IoDbg;

StreamOutput::StreamOutput(ostream& stream_, bool add_newline_) :
    stream(stream_), add_newline(add_newline_)
{
}

StreamOutput::~StreamOutput() {}

void StreamOutput::WriteData(string const& data)
{
    stream << data;

    if (add_newline)
        stream << "\n";

    stream << flush;
}
