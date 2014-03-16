#include "BreakpointManager.hpp"
#include "StepStateManager.hpp"
#include "WatchManager.hpp"

namespace IoDbg {

class UserCmdHandler : public boost::static_visitor<>
{
private:

    MainChannels channels;
    BreakpointManager& brkpt_mgr;
    StepStateManager& step_mgr;
    WatchManager& watch_mgr;

public:

    UserCmdHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_,
                   WatchManager& watch_mgr_);
    void handle(UserCmd const& cmd);
    template <typename T> void operator()(const T& t) const;
    void operator()(const Rules::SetOption& t) const;
    void operator()(const Rules::SetBreakpoint& t) const;
    void operator()(const Rules::StepMode& t) const;
    void operator()(const Rules::Info& t) const;
    void operator()(const Rules::WhatIs& t) const;

};

}
