#include "BreakpointManager.hpp"
#include "StepStateManager.hpp"
#include "WatchManager.hpp"
#include "GdbResponseParser.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdHandler : public boost::static_visitor<>
{
private:

    MainChannels channels;
    BreakpointManager& brkpt_mgr;
    StepStateManager& step_mgr;
    WatchManager& watch_mgr;
    GdbResponseParser& resp_parser;

public:

    UserCmdHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_,
                   WatchManager& watch_mgr_, GdbResponseParser& resp_parser_);
    void handle(UserCmd const& cmd);
    template <typename T> void operator()(const T& t) const;
    void operator()(const UserCmds::SetOption& t) const;
    void operator()(const UserCmds::SetBreakpoint& t) const;
    void operator()(const UserCmds::StepMode& t) const;
    void operator()(const UserCmds::Info& t) const;
    void operator()(const UserCmds::WhatIs& t) const;

};

}}
