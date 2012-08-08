
#ifndef NO_LOAD_GDB

#define BOOST_FILESYSTEM_VERSION 2
#include "boost/process.hpp"
namespace bp = ::boost::process;

#endif

#include "boost/assert.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
using namespace std;

#include "InputChain.hpp"
#include "InputChainComponents.hpp"
#include "TestPlan.hpp"
using namespace Iocaste::Debugger;

struct MainChannels
{
    AbstractInput<UserCmd>& fromUser;
    AbstractOutput<GdbResponse>& toUser;
    AbstractInput<GdbResponse>& fromGdb;
    AbstractOutput<UserCmd>& toGdb;
    AbstractOutput<std::string>& info;
    AbstractInput<boost::exception_ptr>& errors;
    AbstractOutput<std::string>& end_markers;

    MainChannels(AbstractInput<UserCmd>& fromUser_, AbstractOutput<GdbResponse>& toUser_, AbstractInput<GdbResponse>& fromGdb_,
                 AbstractOutput<UserCmd>& toGdb_, AbstractOutput<std::string>& info_, AbstractInput<boost::exception_ptr>& errors_,
                 AbstractOutput<std::string>& end_markers_)
        : fromUser(fromUser_), toUser(toUser_), fromGdb(fromGdb_), toGdb(toGdb_), info(info_), errors(errors_), end_markers(end_markers_) {}
};

void checkErrors(MainChannels channels)
{
    try
    {
        if (channels.errors.HasData())
        {
            auto e = channels.errors.ReadData();
            boost::rethrow_exception(e);
        }
    }
    catch (TestException const& e)
    {
        cerr << endl << "Test failed " << e.what() << endl;
    }
    catch (Exception const& e)
    {
        cerr << endl << e.what() << endl;
    }
//    catch (std::exception const& e)
//    {
//        cerr << e.what() << endl;
//    }
    catch (...)
    {
        cerr << "unknown err" << endl;
    }
}


/*

Execution diagram

    main loop           user cmd handler

    +---+          +-------+              +-------+
    |   |          |       v              |       |
    |   |          |  GDB will handle?    |       v
    |   v          |  Yes  No------->handle   write GDB
    |   user cmd?  |   v             cmd  ^     read GDB
    |   No Yes->read   write         |    +-------+
    |   |       user   GDB           v
    |   v              v         fake response
    |   gdb resp?<-----+<--------write to user
    +-<--No  Yes
    ^         |
    |         v
    |     gdb response
    |     write to user
    |         |
    +<--------+

It is not as crazy as it looks.

There are just a few basic ideas at work in the diagram:

UserCmd handler

    Whenever a UserCmd is received, the user command handler
    either writes it to gdb or handles it internally.

    In the process of handling a command itself, the handler may write
    other commands to gdb and read those responses.

    After handling a command internally, the command
    handler always writes some (faked) response.

Main Loop

    The main loop is agnostic as to whether the next
    input should be from the user first or gdb first.

        This prevents the debugger from becoming unresponsive
        while waiting on the wrong input source.
*/

struct GdbBreakpoint
{
    int number;
};

struct IoBreakpoint
{
    int number;
};

struct UserBreakpoint
{
    int number;
};

struct OurBreakpoint
{
    int number;
};

class BreakpointMap
{
private:
    typedef boost::variant<UserBreakpoint, OurBreakpoint> breakpoint_user;
    typedef boost::variant<GdbBreakpoint, IoBreakpoint> breakpoint_provider;
    typedef std::pair<breakpoint_user, breakpoint_provider> row_t;
    std::vector<row_t> tbl;

    template <typename Result>
    Result next_user_breakpoint()
    {
        int max = 0;

        try
        {
            for (row_t row : tbl)
                if (Result* m = boost::get<Result>(&row.first))
                    if (m->number > max)
                        max = m->number;
        }
        catch (exception const& e)
        {
            cerr << "Error getting max_user_breakpoint " << t.number << " exception was " << e.what() << endl;
            throw;
        }

        return {max+1};
    }

public:

    template <typename Result, typename Source>
    Result get_user_breakpoint(Source t)
    {
        try
        {
            for (row_t row : tbl)
                if (Result* m = boost::get<Result>(&row.first))
                    if (m->number == t.number)
                        return *m;
        }
        catch (exception const& e)
        {
            cerr << "Error in get_user_breakpoint " << t.number << " exception was " << e.what() << endl;
            throw;
        }

        Result r = next_user_breakpoint();
        tbl.push_back( { r, t } );
        return r;
    }

    template <typename Result, typename Source>
    Result get_provider_breakpoint(Source t)
    {
        try
        {
            for (row_t row : tbl)
                if (Result* m = boost::get<Result>(&row.second))
                    if (m->number == t.number)
                        return *m;
        }
        catch (exception const& e)
        {
            cerr << "Error in get_provider_breakpoint " << t.number << " exception was " << e.what() << endl;
            throw;
        }

        // If we don't find a provider breakpoint, that's an error.
        raiseError(LogicError("No provider breakpoint for this user breakpoint number."));
    }

};

class UserCmdHandler
{
private:
    MainChannels channels;
    BreakpointMap& brkpts;
    std::string last_prompt;
    boost::optional<OurBreakpoint> io_debugger_breakpoint;

    struct Visitor;
    friend struct Visitor;
    struct Visitor : boost::static_visitor<>
    {
        UserCmdHandler& handler;

        Visitor(UserCmdHandler& handler_) : handler(handler_) {}

        template <typename T>
        void operator()(const T& t) const
        {
            handler.toGdb(t);
        }

        void operator()(const UserCmds::SetOption& t) const
        {
            if (t.name == "prompt")
                handler.channels.end_markers.WriteData(handler.last_prompt = t.value);

            handler.toGdb(t);
        }

        void operator()(const UserCmds::SetBreakpoint& t) const
        {
            if (boost::algorithm::ends_with(t.file_name, ".io"))
                handler.handleIoBreakpoint(t);
            else
                handler.handleGdbBreakpoint(t);
        }
    };

    void toGdb(UserCmd const& cmd) const
    {
        channels.toGdb.WriteData(cmd);
    }

    void toUser(GdbResponse const& response) const
    {
        channels.toUser.WriteData(response);
    }

    OurBreakpoint setIoDebuggerBreakHere() const
    {
        UserCmds::SetBreakpointOnFunction real_bkpt = { "io_debugger_break_here" };
        UserCmd cmd;
        cmd = real_bkpt;
        channels.toGdb.WriteData( cmd );

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* bs = boost::get<GdbResponses::BreakpointSet>(&resp.values.at(0)))
        {
            GdbBreakpoint gb = { bs->breakpoint_number };
            return brkpts.get_user_breakpoint<OurBreakpoint>(gb);
        }
        else
        {
            // Todo: this is not necessarily a logic error in this program per se,
            // need an exception type for "did not get expected response".
            raiseError(LogicError("Did not get expected gdb response type from gdb when setting breakpoint on io_debugger_break_here() function."));

            // never get here
            return {-1};
        }
    }

    IoBreakpoint setIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        if (!io_debugger_breakpoint)
            io_debugger_breakpoint = setIoDebuggerBreakHere();

        UserCmds::PrintFunction print;
        print.function_name = "io_debugger_set_breakpoint";
        print.args.push_back(stbk.file_name);
        print.args.push_back(stbk.line_number);
        channels.toGdb.WriteData(print);

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* vh = boost::get<GdbResponses::ValueHistory>(&resp.values.at(0)))
        {
            if (auto* breakpt_num = boost::get<int>(&vh->value))
            {
                return {*breakpt_num};
            }
            else
            {
                raiseError(LogicError("Did not get expected function return type from gdb when calling io_debugger_set_breakpoint."));
            }
        }
        else
        {
            // Todo: this is not necessarily a logic error in this program per se,
            // need an exception type for "did not get expected response".
            raiseError(LogicError("Did not get expected gdb response type from gdb when calling io_debugger_set_breakpoint."));
        }

        // Never get here
        return {-1};
    }

    void handleIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        IoBreakpoint ib = setIoBreakpoint(stbk);
        UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

        GdbResponses::BreakpointSet bs;

        bs.breakpoint_number = ub.number;
        bs.address = std::string("0x00000000");
        bs.file_name = stbk.file_name;
        bs.line_number = stbk.line_number;

        GdbResponse resp;
        resp.prompt = last_prompt;
        resp.values.push_back(bs);
        toUser(resp);
    }

    void handleGdbBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        IoBreakpoint ib = setIoBreakpoint(stbk);
        UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

        GdbResponses::BreakpointSet bs;

        bs.breakpoint_number = ub.number;
        bs.address = std::string("0x00000000");
        bs.file_name = stbk.file_name;
        bs.line_number = stbk.line_number;

        GdbResponse resp;
        resp.prompt = last_prompt;
        resp.values.push_back(bs);
        cerr << "Before toUser" << endl;
        toUser(resp);
        cerr << "Wrote io breakpoint resp to user." << endl;
    }

public:

    UserCmdHandler(MainChannels const& channels_, BreakpointMap& brkpts_)
        : channels(channels_), brkpts(brkpts_) {}

    void handle(UserCmd const& cmd)
    {
        boost::apply_visitor(Visitor(*this), cmd);
    }

};

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



void mainLoop(MainChannels channels)
{
    BreakpointMap brkpts;
    UserCmdHandler cmd_handler(channels, brkpts);
    GdbResponseHandler resp_handler(channels, brkpts);

    while (true)
    {
        checkErrors(channels);

        if (channels.fromUser.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadUser");
            UserCmd cmd = channels.fromUser.ReadData();
            cmd_handler.handle(cmd);
        }

        checkErrors(channels);

        if (channels.fromGdb.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadGdb");
            GdbResponse response = channels.fromGdb.ReadData();
            resp_handler.handle(response);
        }
    }
}

#ifndef NO_LOAD_GDB

bp::child start_gdb(int argc, char* argv[])
{
    std::vector<std::string> args;
    args.push_back("/usr/bin/gdb");

    for (int i=1; i<argc; ++i)
        args.push_back(argv[i]);

    std::string exec = args[0];

    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();
    ctx.stdin_behavior = bp::capture_stream();

    return bp::launch(exec, args, ctx);
}

#endif

int main(int argc, char* argv[])
{
    char const* logFileName =
#if defined(_WIN32)
    ".\\debug.log"
#else
    "./debug.log"
#endif
        ;

    char const* replayFileName =
#if defined(_WIN32)
    ".\\gdb-sample.log"
#else
    "./gdb-sample.log"
#endif
        ;

    Queue<boost::exception_ptr> error_queue;
    Queue<std::string> end_marker_queue;

    TestPlan plan1;

    plan1.setAction("info", TestActionType::ignore);
    plan1.setAction("fromUser", TestActionType::write);
    plan1.setAction("toGdb", TestActionType::expectExact);
    plan1.setAction("fromGdb", TestActionType::write);
    plan1.setAction("toUser", TestActionType::expectExact);

    // ignore exceptions from code under test to prevent generating additional "did not get expected label" exceptions.
    plan1.setAction("exception", TestActionType::ignore);

    std::ifstream replay_file(replayFileName);
    std::ofstream log_file(logFileName, ofstream::out);
    auto log_replay = InputChain().to<LineInput>(replay_file).to<Worker>("log_replay", error_queue).to<ActivityLog>(plan1).to<StreamOutput>(log_file, true).complete();
    auto& log = log_replay.at<ActivityLog>(0);

    auto exception_log = InputChain().to<LogChannel>(log, "exception").to<StreamOutput>(cerr).complete();
    setExceptionLog(&exception_log.at<LogChannel>(0));

#ifdef NO_LOAD_GDB
    auto& os = cout;
    auto& is = cin;
#else
    bp::child c = start_gdb(argc, argv);
    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();
#endif

    auto fromUser = InputChain().to<LineInput>(cin).to<Worker>("fromUser", error_queue).to<LogChannel>(log, "fromUser").to<UserCmdParser>().to<Queue<UserCmd>>().complete();

    // LineInput eats newlines so fromUser -> toGdb stream output must re-add newline (pass true to stream output).
    auto toGdb = InputChain().to<UserCmdWriter>().to<LogChannel>(log, "toGdb").to<StreamOutput>(os, true).complete();

    string prompt = "(gdb) ";
    //string prompt = ">>>>>>cb_gdb:";
    auto fromGdb = InputChain().to<CharInput>(is).to<Worker>("fromGdb", error_queue).to<LookForPrompt>(end_marker_queue).to<LogChannelWithPrompt>(log, "fromGdb").to<GdbResponseParser>().to<Queue<GdbResponse>>().complete();

    // CharInput does not eat newlines, and look-for-prompt looks for a prompt string not a newline, so newlines are NOT eaten
    // therefore fromGdb -> toUser does not need to re-add a newline.
    auto toUser = InputChain().to<GdbResponseWriter>().to<LogChannelWithPrompt>(log, "toUser").to<RecombinePrompt>().to<StreamOutput>(cout, false).complete();

    auto info = InputChain().to<LogChannel>(log, "info").to<StreamOutput>(cerr, true).complete();

    info.head().WriteData("Built input chains.");

    mainLoop(MainChannels(fromUser.tail(), toUser.head(), fromGdb.tail(), toGdb.head(), info.head(), error_queue, end_marker_queue));

    // This doesn't do much good if they are blocked waiting on stream input.
    fromUser.at<Worker>(0).stop_thread_soon();
    fromGdb.at<Worker>(0).stop_thread_soon();
    log_replay.at<Worker>(0).stop_thread_soon();

    //bp::status s = c.wait();
    //std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
}

