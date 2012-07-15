#include "UserCmd.hpp"
#include "AbstractAdapter.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdWriter : public AbstractAdapter<UserCmd>
{
private:
    AbstractOutput<std::string>& sink;
public:
    UserCmdWriter(AbstractOutput<std::string>& sink_);
    virtual void WriteData(UserCmd const& input);
};

}}
