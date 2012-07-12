#include "UserCmdParser.hpp"
using namespace Iocaste::Debugger;

UserCmdParser::UserCmdParser(AbstractOutput<UserCmd>& sink_)
    : sink(sink_)
{
}

void UserCmdParser::WriteData(std::string input)
{
    UserCmd cmd;
    cmd.raw_string = input;
    sink.WriteData(cmd);
}
