#include "UserCmdWriter.hpp"
using namespace Iocaste::Debugger;

UserCmdWriter::UserCmdWriter(AbstractOutput<std::string sink_)
    : sink(sink_) {}

void UserCmdWriter::WriteData(UserCmd const& input)
{
    // TODO:  Actually write out the input...
    sink.WriteData(input.raw_string);
}
