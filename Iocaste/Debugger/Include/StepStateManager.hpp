#pragma once

#include "MainChannels.hpp"

#include <vector>

namespace Iocaste { namespace Debugger {

struct StepResponseVisitor;

class StepStateManager
{
private:

    MainChannels channels;
    bool at_script_breakpoint;

    friend struct StepResponseVisitor;

    void doStep(std::string step_mode, UserCmd cmd);

public:

    StepStateManager(MainChannels const& channels_);
    void atScriptBreakpoint(bool value);
    void handle(UserCmds::StepMode const& cmd);
};

}}

