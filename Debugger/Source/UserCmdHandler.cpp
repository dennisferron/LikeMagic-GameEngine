#include "UserCmdHandler.hpp"
#include "boost/thread.hpp"

using namespace Iocaste::Debugger;

UserCmdHandler::UserCmdHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_)
    : channels(channels_), brkpt_mgr(brkpt_mgr_) {}

void UserCmdHandler::handle(UserCmd const& cmd)
{
    boost::apply_visitor(*this, cmd);
}

template <typename T>
void UserCmdHandler::operator()(const T& t) const
{
    channels.toGdb.WriteData(t);
}

void UserCmdHandler::operator()(const UserCmds::SetOption& t) const
{
    if (t.name == "prompt")
    {
        // Sometimes there's a race condition between the user sending he prompt change
        // and GDB still spitting out other messages with the old prompt.
        // This is a simple hack to get around that problem:
        boost::this_thread::sleep(
            boost::posix_time::milliseconds(5000)
        );

        channels.end_markers.WriteData(t.value);

        // Needed so that the breakpoint manager can synthesize gdb response objects.
        brkpt_mgr.setPrompt(t.value);
    }

    channels.toGdb.WriteData(t);
}

void UserCmdHandler::operator()(const UserCmds::SetBreakpoint& t) const
{
    brkpt_mgr.userSetBreakpoint(t);
}
