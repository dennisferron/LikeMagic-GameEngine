#include "BreakpointManager.hpp"
#include "StepStateManager.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseHandler : public boost::static_visitor<GdbResponseType>
{
private:

    MainChannels channels;
    BreakpointManager& brkpt_mgr;
    StepStateManager& step_mgr;

public:

    GdbResponseHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_);
    void handle(GdbResponse const& response);
    template <typename T> GdbResponseType operator()(const T& t);
    GdbResponseType operator()(const GdbResponses::UninitializedVariant& t);

};

}}
