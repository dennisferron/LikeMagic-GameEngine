
#include "StepStateManager.hpp"

namespace IoDbg {

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

void StepStateManager::handle(Rules::StepMode const& cmd)
{
    if (cmd.cmd == "step")
        doStep("StepMode_StopOnAnyMessage", cmd);
    else if (cmd.cmd == "next")
        doStep("StepMode_StepNext", cmd);
    else if (cmd.cmd == "finish")
        doStep("StepMode_StepOut", cmd);
    else
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
        channels.toGdb.WriteData(Rules::Return {step_mode});
        channels.toGdb.WriteData(Rules::StepMode {"cont"});
    }
}

}

