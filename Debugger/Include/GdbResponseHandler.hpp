#include "MainChannels.hpp"
#include "BreakpointMap.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseHandler
{
private:
    MainChannels channels;
    BreakpointMap& brkpts;

    void toUser(GdbResponse const& response)
    {
        channels.toUser.WriteData(response);
    }

    struct Visitor : public boost::static_visitor<>
    {
        BreakpointMap& brkpts;
        std::vector<GdbResponseType> output;

        Visitor(BreakpointMap& brkpts_) : brkpts(brkpts_) {}

        template <typename T>
        void operator()(const T& t)
        {
            output.push_back(t);
        }

        void operator()(const GdbResponses::UninitializedVariant& t)
        {
            cerr << "got uninitialized variant" << endl;
            raiseError(ParseException("GdbResponseHandler was passed uninitialized variant in GdbResponse object."));
        }

        void operator()(const GdbResponses::BreakpointSet& t)
        {
            cerr << "breakpoint set is " << t.breakpoint_number << " " << t.address << " " << t.file_name << " " << t.line_number << endl;

            GdbResponses::BreakpointSet bs(t);
            GdbBreakpoint gb = {t.breakpoint_number};
            bs.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
            output.push_back(bs);
        }

    /*
        Power goal - mix Io stack frames and C++ stack frames in backtrace lines.
        This will require detecting backtraces at the GdbResponse level rather
        than at the GdbResponseType item level.
        void operator()(std::vector<GdbResponseType>& output, const BacktraceLine& t) const
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
    };

public:

    GdbResponseHandler(MainChannels const& channels_, BreakpointMap& brkpts_)
        : channels(channels_), brkpts(brkpts_) {}


    void handle(GdbResponse const& response)
    {
        Visitor v(brkpts);
        for (auto line_item : response.values)
            boost::apply_visitor(v, line_item);

        GdbResponse munged;
        munged.prompt = response.prompt;
        munged.values = v.output;
        channels.toUser.WriteData(munged);
    }
};

}}
