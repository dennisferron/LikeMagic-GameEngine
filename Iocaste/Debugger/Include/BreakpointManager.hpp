#pragma once

#include "MainChannels.hpp"
#include "BreakpointMap.hpp"
#include "WatchManager.hpp"

#include "GdbResponse.hpp"

#include <vector>

namespace IoDbg {

struct BreakpointResponseVisitor;

class BreakpointManager
{
private:

    MainChannels channels;
    WatchManager& watch_mgr;
    BreakpointMap brkpts;
    boost::optional<OurBreakpoint> io_debugger_breakpoint;
    boost::optional<OurBreakpoint> io_init_breakpoint;
    std::vector<IoBreakpoint> deferred_breakpoints;
    std::string gdb_prompt;

    friend struct BreakpointResponseVisitor;

    void toGdb(UserCmd const& cmd) const;
    void toUser(GdbResponse const& response) const;
    OurBreakpoint setIoDebuggerBreakpoint(std::string function_name);
    void loadDeferredBreakpoint(Rules::GdbAddress io_state, IoBreakpoint ib);
    IoBreakpoint setIoBreakpoint(Rules::SetBreakpoint const& stbk);
    void userSetIoBreakpoint(Rules::SetBreakpoint const& stbk);
    Rules::BreakpointSet setGdbBreakpoint(Rules::SetBreakpoint const& stbk);
    void userSetGdbBreakpoint(Rules::SetBreakpoint const& stbk);
    void ioDebuggerInit(const Rules::BreakpointHit& bh);
    GdbActionable ioDebuggerIoBreakpoint(const Rules::BreakpointHit& bh);

    typedef std::vector<std::pair<std::string, Rules::GdbValue>> FunctionArgs;
    FunctionArgs getArgs();
    FunctionArgs getArgs(Rules::GdbResponseFunction func);
    Rules::GdbValue getArg(FunctionArgs args, std::string arg_name);
    int getInt(FunctionArgs args, std::string arg_name);
    std::string getValueAsString(FunctionArgs args, std::string arg_name);
    Rules::GdbAddress getPointer(FunctionArgs args, std::string arg_name);
    GdbActionable gdbBreakpointHit(const Rules::BreakpointHit& t, bool& is_our_breakpoint);
    GdbActionable gdbBreakpointSet(const Rules::BreakpointSet& t);
    GdbActionable gdbBreakpointPending(const Rules::BreakpointPending& t);
    GdbActionable gdbCursorPos(const Rules::CursorPos& t, bool is_our_breakpoint);
    bool isIoBreakpoint(std::string file_name) const;

public:

    BreakpointManager(MainChannels const& channels_, WatchManager& watch_mgr_);
    void userSetBreakpoint(const Rules::SetBreakpoint& t);
    void setPrompt(std::string new_prompt);
    bool handle(GdbResponse const& response);
};

}

