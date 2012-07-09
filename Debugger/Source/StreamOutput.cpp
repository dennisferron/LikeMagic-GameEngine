#include "StreamOutput.hpp"

using namespace std;
using namespace Iocaste::Debugger;

StreamOutput::StreamOutput(ostream& stream_, bool add_newline_) :
    stream(stream_), add_newline(add_newline_)
{
}

void StreamOutput::WriteData(string const& data)
{
    stream << data;

    if (add_newline)
        stream << "\n";

    stream << flush;
}
