
#include "StepStateManager.hpp"

namespace Iocaste { namespace Debugger {

struct StepResponseVisitor
{

};

StepStateManager::StepStateManager(MainChannels const& channels_)
    : channels(channels_), at_script_breakpoint(false)
{
}

void StepStateManager::atScriptBreakpoint(bool value)
{
    at_script_breakpoint = value;
}

void StepStateManager::handle(UserCmds::Step const& cmd)
{
    doStep("StepMode_StopOnAnyMessage", cmd);
}

void StepStateManager::handle(UserCmds::Next const& cmd)
{
    doStep("StepMode_StepNext", cmd);
}

void StepStateManager::handle(UserCmds::Finish const& cmd)
{
    doStep("StepMode_StepOut", cmd);
}

void StepStateManager::handle(UserCmds::Cont const& cmd)
{
    doStep("StepMode_Run", cmd);
}

void StepStateManager::doStep(std::string step_mode, UserCmd cmd)
{
    if (!at_script_breakpoint)
    {
        channels.toGdb.WriteData(cmd);
    }
    else
    {
        channels.toGdb.WriteData(UserCmds::Return {step_mode});
        channels.toGdb.WriteData(UserCmds::Cont {"cont"});
    }
}

}}

