#pragma once

#include "MainChannels.hpp"
#include "BreakpointMap.hpp"

#include <vector>

namespace Iocaste { namespace Debugger {

struct BreakpointResponseVisitor;

class BreakpointManager
{
private:

    MainChannels channels;
    BreakpointMap brkpts;
    boost::optional<OurBreakpoint> io_debugger_breakpoint;
    boost::optional<OurBreakpoint> io_init_breakpoint;
    std::vector<IoBreakpoint> deferred_breakpoints;
    std::string gdb_prompt;

    friend struct BreakpointResponseVisitor;

    void toGdb(UserCmd const& cmd) const;
    void toUser(GdbResponse const& response) const;
    OurBreakpoint setIoDebuggerBreakpoint(std::string function_name);
    void loadDeferredBreakpoint(SharedTypes::GdbAddress io_state, IoBreakpoint ib);
    IoBreakpoint setIoBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void userSetIoBreakpoint(UserCmds::SetBreakpoint const& stbk);
    GdbResponses::BreakpointSet setGdbBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void userSetGdbBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void ioDebuggerInit(const GdbResponses::BreakpointHit& bh);
    GdbResponseType ioDebuggerIoBreakpoint(const GdbResponses::BreakpointHit& bh);

    typedef std::vector<std::pair<std::string, SharedTypes::GdbValue>> FunctionArgs;
    FunctionArgs getArgs();
    FunctionArgs getArgs(SharedTypes::GdbResponseFunction func);
    SharedTypes::GdbValue getArg(FunctionArgs args, std::string arg_name);
    int getInt(FunctionArgs args, std::string arg_name);
    std::string getValueAsString(FunctionArgs args, std::string arg_name);
    SharedTypes::GdbAddress getPointer(FunctionArgs args, std::string arg_name);
    GdbResponseType gdbBreakpointHit(const GdbResponses::BreakpointHit& t, bool& is_our_breakpoint);
    GdbResponseType gdbBreakpointSet(const GdbResponses::BreakpointSet& t);
    GdbResponseType gdbBreakpointPending(const GdbResponses::BreakpointPending& t);
    GdbResponseType gdbCursorPos(const GdbResponses::CursorPos& t, bool is_our_breakpoint);
    bool isIoBreakpoint(std::string file_name) const;

public:

    BreakpointManager(MainChannels const& channels_);
    void userSetBreakpoint(const UserCmds::SetBreakpoint& t);
    void setPrompt(std::string new_prompt);
    bool handle(GdbResponse const& response);
};

}}

