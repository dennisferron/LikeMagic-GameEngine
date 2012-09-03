#include "BreakpointManager.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdHandler : public boost::static_visitor<>
{
private:

    MainChannels channels;
    BreakpointManager& brkpt_mgr;

public:

    UserCmdHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr);
    void handle(UserCmd const& cmd);
    template <typename T> void operator()(const T& t) const;
    void operator()(const UserCmds::SetOption& t) const;
    void operator()(const UserCmds::SetBreakpoint& t) const;
};

}}
