
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

    There is an asymmetry between the handling of user cmds
    versus gdb responses.  A user command always goes
    to the separate handler, but a gdb response gets forwarded
    directly to the user.

        There is no concern for gdb responses from the
        user cmd handler reaching to the main loop because
        the user cmd handler should have eaten those itself.

        HOWEVER, we will need a "gdb response handler"
        in the future to munge the breakpoint numbering
        when the user gets breakpoint information, because
        the actual number of gdb breakpoints is less
        by the amount of "virtual" Io breakpoints.
*/


class UserCmdHandler : public boost::static_visitor<>
{
private:
    MainChannels channels;

    void toGdb(UserCmd const& cmd) const
    {
        channels.toGdb.WriteData(cmd);
    }

    void toUser(GdbResponse const& response)
    {

    }


public:

    UserCmdHandler(MainChannels& channels_) : channels(channels_) {}

    template <typename T>
    void operator()(const T& t) const
    {
        toGdb(t);
    }

    void operator()(const UserCmds::SetOption& t) const
    {
        if (t.name == "prompt")
        {
            channels.end_markers.WriteData(t.value);
        }
        toGdb(t);
    }

    void operator()(const UserCmds::SetBreakpoint& t) const
    {
        if (boost::algorithm::ends_with(t.file_name, ".io"))
            toUser(setIoBreakpoint(t));
        else
            toGdb(t);
    }
};

void mainLoop(MainChannels channels)
{
    UserCmd cmd;
    GdbResponse response;

    while (true)
    {
        checkErrors(channels);

        if (channels.fromUser.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadUser");

            cmd = channels.fromUser.ReadData();

            UserCmdHandler cmd_handler(channels);
            boost::apply_visitor(cmd_handler, cmd);

            /*
            if (cmd.raw_string && *(cmd.raw_string) == "quit")
            {
                cerr << "Received quit command" << endl;
                return;
            }
            if (cmd.set_option && cmd.set_option->name == "prompt")
            {
                channels.end_markers.WriteData(cmd.set_option->value);
            }
            */
        }

        checkErrors(channels);

        if (channels.fromGdb.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadGdb");
            response = channels.fromGdb.ReadData();
            channels.toUser.WriteData(response);
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

    std::ifstream replay_file(replayFileName);
    std::ofstream log_file(logFileName, ofstream::out);
    auto log_replay = InputChain().to<LineInput>(replay_file).to<Worker>("log_replay", error_queue).to<ActivityLog>(plan1).to<StreamOutput>(log_file, true).complete();
    auto& log = log_replay.at<ActivityLog>(0);

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

