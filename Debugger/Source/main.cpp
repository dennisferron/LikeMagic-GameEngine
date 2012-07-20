#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>
#include <boost/assert.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
using namespace std;
namespace bp = ::boost::process;


enum class MainLoopState
{
    ReadUser,
    WriteGdb,
    ReadGdb,
    WriteUser,
    Quit
};

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

    MainChannels(AbstractInput<UserCmd>& fromUser_, AbstractOutput<GdbResponse>& toUser_, AbstractInput<GdbResponse>& fromGdb_, AbstractOutput<UserCmd>& toGdb_, AbstractOutput<std::string>& info_)
        : fromUser(fromUser_), toUser(toUser_), fromGdb(fromGdb_), toGdb(toGdb_), info(info_) {}
};

MainLoopState processUserCmd(UserCmd& cmd, MainChannels channels)
{
    return MainLoopState::WriteGdb;
}

MainLoopState processResponse(GdbResponse& response, MainChannels channels)
{
    return MainLoopState::WriteUser;
}

void mainLoop(MainChannels channels)
{
    //Thread::usleep(100000L);

    // Relay gdb's welcome message before processing user commands.  Codeblocks seems to require this.
    //if(channels.fromGdb.HasData())
    //{
    //    auto banner = channels.fromGdb.ReadData();
    //    channels.toUser.WriteData(banner);
    //}
    //else
    //    channels.info.WriteData("Failed to receive gdb's welcome banner, or it did not end with a '(gdb)' prompt.");

    MainLoopState state = MainLoopState::ReadUser;
    UserCmd cmd;
    GdbResponse response;

    while (true)
    {
        if (channels.fromUser.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadUser");
            cmd = channels.fromUser.ReadData();
            channels.toGdb.WriteData(cmd);
            if (cmd.raw_string == "quit")
                return;
        }

        if (channels.fromGdb.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadGdb");
            response = channels.fromGdb.ReadData();
            channels.toUser.WriteData(response);
        }
    }

/*
    while (true)
    {
        switch (state)
        {
            case MainLoopState::ReadUser:
                channels.info.WriteData("MainLoopState::ReadUser");
                cmd = channels.fromUser.ReadData();
                state = processUserCmd(cmd, channels);
                break;

            case MainLoopState::WriteGdb:
                channels.info.WriteData("MainLoopState::WriteGdb");
                channels.toGdb.WriteData(cmd);

                if (cmd.raw_string == "quit")
                    state = MainLoopState::Quit;
                else
                    state = MainLoopState::ReadGdb;
                break;

            case MainLoopState::ReadGdb:
                channels.info.WriteData("MainLoopState::ReadGdb");
                response = channels.fromGdb.ReadData();
                state = processResponse(response, channels);
                break;

            case MainLoopState::WriteUser:
                channels.info.WriteData("MainLoopState::WriteUser");
                channels.toUser.WriteData(response);
                state = MainLoopState::ReadUser;
                break;

            case MainLoopState::Quit:
                channels.info.WriteData("MainLoopState::Quit");
                return;
        }
    }
    */
}


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

template <int I>
struct TestAdapter : public AbstractAdapter<string>
{
    AbstractOutput<string>& sink;

    TestAdapter(TestAdapter const&)=delete;

    TestAdapter(AbstractOutput<string>& sink_) : sink(sink_)
    {
        cout << "TestAdapter " << this << " created" << endl;
    }

    TestAdapter(AbstractOutput<string>& sink_, int i) : sink(sink_)
    {
        cout << "TestAdapter " << this << " created" << endl;
    }

    ~TestAdapter()
    {
        cout << "~TestAdapter " << this << " destructed" << endl;
    }

    void WriteData(string const& str)
    {
        cout << "Got: " << str << endl;
        sink.WriteData(str+"x");
    }
};

int main(int argc, char* argv[])
{
    //InputChain().to<Input<float>>(0.1f, cin).to<TestWorker>("first").to<TestQueue>().to<TestWorker>("second").to<Adapter>().to<Output>().force();
    //InputChain().to<LineInput>(cin).to<Worker>("test").to<LookForPrompt>("(gdb) ").to<Queue<string>>().force();
    //return 0;

    char const* logFileName =
#ifdef __APPLE__
    "/Users/dennisferron/debug.log"
#else
    "/home/dennis/debug.log"
#endif
        ;

    char const* replayFileName =
#ifdef __APPLE__
    "/Users/dennisferron/gdb-sample.log"
#else
    "/home/dennis/gdb-sample.log"
#endif
        ;

    TestPlan plan1;
    plan1.setAction("info", TestActionType::ignore);
    plan1.setAction("fromUser", TestActionType::write);
    plan1.setAction("toGdb", TestActionType::expectExact);
    plan1.setAction("fromGdb", TestActionType::write);
    plan1.setAction("toUser", TestActionType::expectExact);

    std::ifstream replay_file(replayFileName);
    std::ofstream log_file(logFileName, ofstream::out);
    auto log_replay = InputChain().to<LineInput>(replay_file).to<Worker>().to<ActivityLog>(plan1).to<StreamOutput>(log_file, true).complete();
    auto& log = log_replay.get<ActivityLog, 0>();

    bp::child c = start_gdb(argc, argv);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

/*
    Testing protocol by activity log line label:
        ignore info
        write fromUser
        expect toGdb
        write fromGdb
        expect toUser
*/

    auto fromUser = InputChain().to<LineInput>(cin).to<Worker>("fromUser").to<LogChannel>(log, "fromUser").to<UserCmdParser>().to<Queue<UserCmd>>().complete();

    // LineInput eats newlines so fromUser -> toGdb stream output must re-add newline (pass true to stream output).
    auto toGdb = InputChain().to<UserCmdWriter>().to<LogChannel>(log, "toGdb").to<StreamOutput>(os, true).complete();

    //string prompt = "(gdb) ";
    string prompt = ">>>>>>cb_gdb:";
    auto fromGdb = InputChain().to<CharInput>(is).to<Worker>("fromGdb").to<LookForPrompt>(prompt).to<LogChannel>(log, "fromGdb").to<GdbResponseParser>().to<Queue<GdbResponse>>().complete();

    // CharInput does not eat newlines, and look-for-prompt looks for a prompt string not a newline, so newlines are NOT eaten
    // therefore fromGdb -> toUser does not need to re-add a newline.
    auto toUser = InputChain().to<GdbResponseWriter>().to<LogChannel>(log, "toUser").to<StreamOutput>(cout, false).complete();

    auto info = InputChain().to<LogChannel>(log, "info").to<StreamOutput>(cerr, true).complete();

    //auto test = InputChain().to<LogChannel>(log, "testing").to<StreamOutput>(cout, true).complete();
    //auto test = InputChain().to<StreamOutput>(cout, true).complete();
    //auto test = InputChain().to<TestAdapter<3>>().to<TestAdapter<3>>().to<TestAdapter<3>>().to<StreamOutput>(cout, true).complete();
    //test.head().WriteData("Hello!!");

    info.head().WriteData("Built input chains.");

    mainLoop(MainChannels(fromUser.tail(), toUser.head(), fromGdb.tail(), toGdb.head(), info.head()));

    //bp::status s = c.wait();

    //std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
}

