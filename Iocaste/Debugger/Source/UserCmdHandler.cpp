#include "UserCmdHandler.hpp"

#include <string>
using namespace std;

using namespace IoDbg;

UserCmdHandler::UserCmdHandler(MainChannels const& channels_,
    BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_,
        WatchManager& watch_mgr_)
        : channels(channels_), brkpt_mgr(brkpt_mgr_), step_mgr(step_mgr_),
            watch_mgr(watch_mgr_) {}

void UserCmdHandler::handle(UserCmd const& cmd)
{
    boost::apply_visitor(*this, cmd);
}

template <typename T>
void UserCmdHandler::operator()(const T& t) const
{
    channels.toGdb.WriteData(t);
}

void UserCmdHandler::operator()(const Rules::SetOption& t) const
{
    if (t.name == "prompt")
    {
        channels.end_markers.WriteData(t.value);

        // Needed so that the breakpoint manager can synthesize gdb response objects.
        brkpt_mgr.setPrompt(t.value);
    }

    channels.toGdb.WriteData(t);
}

void UserCmdHandler::operator()(const Rules::SetBreakpoint& t) const
{
    brkpt_mgr.userSetBreakpoint(t);
}

void UserCmdHandler::operator()(const Rules::StepMode& t) const
{
    step_mgr.handle(t);
}

void UserCmdHandler::operator()(const Rules::Info& t) const
{
    watch_mgr.handle(t);
}

void UserCmdHandler::operator()(const Rules::WhatIs& t) const
{
    watch_mgr.handle(t);
}
