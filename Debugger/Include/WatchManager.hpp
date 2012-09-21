#pragma once

#include "MainChannels.hpp"
#include "SharedTypes.hpp"

#include <vector>

namespace Iocaste { namespace Debugger {

struct ScriptContext
{
    SharedTypes::GdbAddress self;
    SharedTypes::GdbAddress locals;
    SharedTypes::GdbAddress m;
};

class WatchManager
{
private:

    MainChannels channels;
    bool at_script_breakpoint;
    ScriptContext context;

public:

    WatchManager(MainChannels const& channels_);
    void setScriptContext(ScriptContext context);
    void atScriptBreakpoint(bool value);
    void handle(UserCmds::Info const& cmd);
};

}}

