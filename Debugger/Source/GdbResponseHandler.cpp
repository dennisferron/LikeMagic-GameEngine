#include "GdbResponseHandler.hpp"

using namespace Iocaste::Debugger;


GdbResponseHandler::GdbResponseHandler(MainChannels const& channels_, BreakpointManager& brkpt_mgr_)
    : channels(channels_), brkpt_mgr(brkpt_mgr_) {}

void GdbResponseHandler::handle(GdbResponse const& response)
{
    std::vector<GdbResponseType> output;
    for (auto line_item : response.values)
        output.push_back(boost::apply_visitor(*this, line_item));

    GdbResponse munged;
    munged.prompt = response.prompt;
    munged.values = output;
    channels.toUser.WriteData(munged);
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

GdbResponseType GdbResponseHandler::operator()(const GdbResponses::BreakpointSet& t)
{
    return brkpt_mgr.gdbBreakpointSet(t);
}

GdbResponseType GdbResponseHandler::operator()(const GdbResponses::BreakpointHit& t)
{
    return brkpt_mgr.gdbBreakpointHit(t);
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
