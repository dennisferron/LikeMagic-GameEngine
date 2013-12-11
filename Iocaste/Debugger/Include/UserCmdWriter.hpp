#include "UserCmd.hpp"
#include "AbstractAdapter.hpp"

namespace IoDbg {

class UserCmdWriter : public AbstractAdapter<Rules::UserCmd>
{
private:
    AbstractOutput<std::string>& sink;
    std::string Write(Rules::UserCmd const& cmd) const;

public:
    UserCmdWriter(AbstractOutput<std::string>& sink_);
    virtual void WriteData(Rules::UserCmd const& input);
};

}
