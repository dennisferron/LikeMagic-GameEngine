#pragma once

#include "MainChannels.hpp"
#include "BreakpointMap.hpp"

#include <vector>

namespace Iocaste { namespace Debugger {

class BreakpointManager
{
private:

    MainChannels channels;
    BreakpointMap brkpts;
    boost::optional<OurBreakpoint> io_debugger_breakpoint;
    boost::optional<OurBreakpoint> io_init_breakpoint;
    std::vector<IoBreakpoint> deferred_breakpoints;
    std::string gdb_prompt;

    void toGdb(UserCmd const& cmd) const;
    void toUser(GdbResponse const& response) const;
    OurBreakpoint setIoDebuggerBreakpoint(std::string function_name);
    void loadDeferredBreakpoint(SharedTypes::GdbAddress io_state, IoBreakpoint ib);
    IoBreakpoint setIoBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void userSetIoBreakpoint(UserCmds::SetBreakpoint const& stbk);
    GdbResponses::BreakpointSet setGdbBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void userSetGdbBreakpoint(UserCmds::SetBreakpoint const& stbk);
    void ioDebuggerInit();
    GdbResponseType ioDebuggerIoBreakpoint();

    typedef std::vector<std::pair<std::string, SharedTypes::GdbValue>> FunctionArgs;
    FunctionArgs getArgs();
    SharedTypes::GdbValue getArg(FunctionArgs args, std::string arg_name);
    int getInt(FunctionArgs args, std::string arg_name);
    std::string getValueAsString(FunctionArgs args, std::string arg_name);
    SharedTypes::GdbAddress getPointer(FunctionArgs args, std::string arg_name);

public:

    BreakpointManager(MainChannels const& channels_);
    void userSetBreakpoint(const UserCmds::SetBreakpoint& t);
    GdbResponseType gdbBreakpointHit(const GdbResponses::BreakpointHit& t);
    GdbResponseType gdbBreakpointSet(const GdbResponses::BreakpointSet& t);
    void setPrompt(std::string new_prompt);
};

}}

