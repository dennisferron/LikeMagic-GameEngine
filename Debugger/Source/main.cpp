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
using namespace Iocaste::Debugger;

struct MainChannels
{
    AbstractInput<UserCmd>& fromUser;
    AbstractOutput<GdbResponse>& toUser;
    AbstractInput<GdbResponse>& fromGdb;
    AbstractOutput<UserCmd>& toGdb;

    MainChannels(AbstractInput<UserCmd>& fromUser_, AbstractOutput<GdbResponse>& toUser_, AbstractInput<GdbResponse>& fromGdb_, AbstractOutput<UserCmd>& toGdb_)
        : fromUser(fromUser_), toUser(toUser_), fromGdb(fromGdb_), toGdb(toGdb_) {}
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
    // Relay gdb's welcome message before processing user commands.  Codeblocks seems to require this.
    BOOST_ASSERT_MSG(channels.fromGdb.HasData(), "Expected to receive banner message from GDB.");
    channels.toUser.WriteData(channels.fromGdb.ReadData());

    MainLoopState state = MainLoopState::ReadUser;
    UserCmd cmd;
    GdbResponse response;

    while (true)
    {
        switch (state)
        {
            case MainLoopState::ReadUser:
                cmd = channels.fromUser.ReadData();
                state = processUserCmd(cmd, channels);
                break;

            case MainLoopState::WriteGdb:
                channels.toGdb.WriteData(cmd);
                state = MainLoopState::ReadGdb;
                break;

            case MainLoopState::ReadGdb:
                response = channels.fromGdb.ReadData();
                state = processResponse(response, channels);
                break;

            case MainLoopState::WriteUser:
                channels.toUser.WriteData(response);
                state = MainLoopState::ReadUser;
                break;

            case MainLoopState::Quit:
                return;
        }
    }
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

    std::ofstream log_file(logFileName, ofstream::out);
    StreamOutput debug_log(log_file, true);
    ActivityLog log(debug_log);

    bp::child c = start_gdb(argc, argv);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

    auto fromUser = InputChain().to<LineInput>(cin).to<Worker>("fromUser").to<LogChannel>(log, "fromUser").to<UserCmdParser>().to<Queue<UserCmd>>().complete();
    auto toGdb = InputChain().to<UserCmdWriter>().to<LogChannel>(log, "toGdb").to<StreamOutput>(os).complete();
    auto fromGdb = InputChain().to<CharInput>(is).to<Worker>("fromGdb").to<LogChannel>(log, "rawGDB").to<LookForPrompt>("(gdb) ").to<LogChannel>(log, "fromGdb").to<GdbResponseParser>().to<Queue<GdbResponse>>().complete();
    auto toUser = InputChain().to<GdbResponseWriter>().to<LogChannel>(log, "toUser").to<StreamOutput>(cout, false).complete();

    //auto test = InputChain().to<LogChannel>(log, "testing").to<StreamOutput>(cout, true).complete();
    //auto test = InputChain().to<StreamOutput>(cout, true).complete();
    //auto test = InputChain().to<TestAdapter<3>>().to<TestAdapter<3>>().to<TestAdapter<3>>().to<StreamOutput>(cout, true).complete();
    //test.head().WriteData("Hello!!");

    mainLoop(MainChannels(fromUser.tail(), toUser.head(), fromGdb.tail(), toGdb.head()));

    bp::status s = c.wait();

    std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
}

