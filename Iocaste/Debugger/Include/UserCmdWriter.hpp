#include "UserCmd.hpp"
#include "AbstractAdapter.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdWriter : public AbstractAdapter<UserCmd>
{
private:
    AbstractOutput<std::string>& sink;
    std::string Write(UserCmd const& cmd) const;

public:
    UserCmdWriter(AbstractOutput<std::string>& sink_);
    virtual void WriteData(UserCmd const& input);
};

}}
