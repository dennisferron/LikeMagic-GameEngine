#include "BreakpointManager.hpp"
#include "StepStateManager.hpp"
#include "WatchManager.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseHandler
{
private:

    MainChannels channels;
    BreakpointManager& brkpt_mgr;
    StepStateManager& step_mgr;
    WatchManager& watch_mgr;

public:

    GdbResponseHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_, WatchManager& watch_mgr_);
    void handle(GdbResponse const& response);

};

}}
