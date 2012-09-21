
#include "WatchManager.hpp"

namespace Iocaste { namespace Debugger {

WatchManager::WatchManager(MainChannels const& channels_)
    : channels(channels_), at_script_breakpoint(false)
{
}

void WatchManager::atScriptBreakpoint(bool value)
{
    at_script_breakpoint = value;
}

void WatchManager::setScriptContext(ScriptContext context_)
{
    context = context_;
}


void WatchManager::handle(UserCmds::Info const& cmd)
{
    /*
    if (at_script_breakpoint && cmd.value == "locals")
    {

    }
    else if (at_script_breakpoint && cmd.value == "args")
    {

    }
    else
    */
    {
        channels.toGdb.WriteData(cmd);
    }
}


}}

