#include "UserCmd.hpp"
#include "AbstractOutput.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdWriter : public AbstractOutput<UserCmd>
{
private:
    AbstractOutput<std::string> sink;
public:
    UserCmdWriter(AbstractOutput<std::string> const& sink_);
    virtual void WriteData(UserCmd const& input);
};

}}
