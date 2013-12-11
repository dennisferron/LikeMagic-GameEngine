#pragma once

#include "AbstractAdapter.hpp"
#include "UserCmd.hpp"
#include <string>

namespace IoDbg {

class UserCmdParser : public AbstractAdapter<std::string>
{
private:
    AbstractOutput<Rules::UserCmd>& sink;
    Rules::UserCmd Parse(std::string str) const;

public:
    UserCmdParser(AbstractOutput<Rules::UserCmd>& sink_);
    virtual void WriteData(std::string const& input);
};

}
