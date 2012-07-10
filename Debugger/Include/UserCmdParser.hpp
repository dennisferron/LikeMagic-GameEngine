#pragma once

#include "AbstractOutput.hpp"
#include "UserCmd.hpp"
#include <string>

namespace Iocaste { namespace Debugger {

class UserCmdParser : public AbstractOutput<std::string>
{
private:
    AbstractOutput<UserCmd>& sink;

public:
    UserCmdParser(AbstractOutput<UserCmd>& sink_);
    virtual void WriteData(std::string input);
};

}}
