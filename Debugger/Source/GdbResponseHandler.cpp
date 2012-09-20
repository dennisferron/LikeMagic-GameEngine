#include "GdbResponseHandler.hpp"

using namespace Iocaste::Debugger;


GdbResponseHandler::GdbResponseHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_, StepStateManager& step_mgr_, WatchManager& watch_mgr_)
    : channels(channels_), brkpt_mgr(brkpt_mgr_), step_mgr(step_mgr_), watch_mgr(watch_mgr_) {}

template <typename T>
bool hasResponseType(std::vector<GdbResponseType> items)
{
    for (auto line_item : items)
        if (boost::get<T>(&line_item))
            return true;

    return false;
}

void GdbResponseHandler::handle(GdbResponse const& response)
{
    if (hasResponseType<GdbResponses::BreakpointHit>(response.values))
    {
        bool at_script_breakpoint = brkpt_mgr.handle(response);
        channels.info.WriteData(std::string("at_script_breakpoint = ") + (at_script_breakpoint? "true" : "false"));
        step_mgr.atScriptBreakpoint(at_script_breakpoint);
        watch_mgr.atScriptBreakpoint(at_script_breakpoint);
    }
    else
    {
        std::vector<GdbResponseType> output;
        for (auto line_item : response.values)
            output.push_back(boost::apply_visitor(*this, line_item));

        GdbResponse munged;
        munged.prompt = response.prompt;
        munged.values = output;
        channels.toUser.WriteData(munged);
    }
}

template <typename T>
GdbResponseType GdbResponseHandler::operator()(const T& t)
{
    return t;
}

GdbResponseType GdbResponseHandler::operator()(const GdbResponses::UninitializedVariant& t)
{
    raiseError(ParseException("GdbResponseHandler was passed uninitialized variant in GdbResponse object."));
    return GdbResponses::Empty();
}

/*
    Power goal - mix Io stack frames and C++ stack frames in backtrace lines.
    This will require detecting backtraces at the GdbResponse level rather
    than at the GdbResponseType item level.
    GdbResponseType GdbResponseHandler::operator()(std::vector<GdbResponseType>& output, const BacktraceLine& t) const
    {
        cerr << "backtrace line is"
        << " #" << t.backtrace_number
        << " at addr:" << t.address
        << " in func:" << t.function
        << " with args:" << t.args
        << " from module:" << t.module
        << " in file:" << t.file_name
        << " at line:" << t.line_number
        << endl;
    }
*/
