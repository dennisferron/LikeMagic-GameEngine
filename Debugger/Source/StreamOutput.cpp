#include "StreamOutput.hpp"

using namespace std;
using namespace Iocaste::Debugger;

StreamOutput::StreamOutput(ostream& stream_) :
    stream(stream_)
{
}

void StreamOutput::WriteData(string const& data)
{
    stream << data << flush;
}
