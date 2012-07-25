#include "UserCmdWriter.hpp"
using namespace Iocaste::Debugger;

UserCmdWriter::UserCmdWriter(AbstractOutput<std::string>& sink_)
    : sink(sink_) {}

void UserCmdWriter::WriteData(UserCmd const& input)
{
    if (input.raw_string)
        sink.WriteData(*input.raw_string);
    else if (input.set_option)
    {
        cerr << "Got " << input.set_option->name << " " << input.set_option->value << endl;
    }
    else
        throw GeneratorException("No fields set on UserCmd");
}
