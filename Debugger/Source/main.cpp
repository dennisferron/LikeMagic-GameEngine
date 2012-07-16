#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>

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

/*
void main_loop(AbstractInput<UserCmd> fromUser, AbstractOutput<> toUser, Channel<GdbResponse, UserCmd> user)
{
    // Relay gdb's welcome message before processing user commands.  Codeblocks seems to require this.
    user.to.WriteData(gdb.from.ReadData());

    MainLoopState state = MainLoopState.ReadUser;
    UserCmd cmd;
    GdbResponse response;

    while (true)
    {
        switch (state)
        {
            case MainLoopState.ReadUser:
                cmd = user.from.ReadData();
                state = processCmd(cmd, gdb, user);
                break;

            case MainLoopState.WriteGdb:
                gdb.to.WriteData(cmd)
                state = MainLoopState.ReadGdb;
                break;

            case MainLoopState.ReadGdb:
                response = gdb.from.ReadData();
                state = processResponse(response, gdb, user);
                break;

            case MainLoopState.WriteUser:
                user.to.WriteData(response);
                state = MainLoopState.ReadUser;
                break;

            case MainLoopState.Quit:
                return;
        }
    }
}
*/

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



int main(int argc, char* argv[])
{
    //InputChain().to<Input<float>>(0.1f, cin).to<TestWorker>("first").to<TestQueue>().to<TestWorker>("second").to<Adapter>().to<Output>().force();
    //InputChain().to<LineInput>(cin).to<Worker>("test").to<LookForPrompt>("(gdb) ").to<Queue<string>>().force();
    //return 0;

    std::ofstream log_file("/Users/dennisferron/debug.log", ofstream::out);
    StreamOutput debug_log(log_file, true);
    ActivityLog log(debug_log);

    bp::child c = start_gdb(argc, argv);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

    auto fromUser = InputChain().to<LineInput>(cin).to<Worker>("fromUser").to<LogChannel>(log, "fromUser").to<UserCmdParser>().to<Queue<UserCmd>>().complete();
    auto toGdb = InputChain().to<UserCmdWriter>().to<LogChannel>(log, "toGdb").to<StreamOutput>(os).complete();
    auto fromGdb = InputChain().to<CharInput>(is).to<Worker>("fromGdb").to<LookForPrompt>("(gdb) ").to<LogChannel>(log, "fromGdb").to<GdbResponseParser>().to<Queue<GdbResponse>>().complete();
    auto toUser = InputChain().to<GdbResponseWriter>().to<LogChannel>(log, "toUser").to<StreamOutput>(cout).complete();

    /*
    CharInput raw_gdb_chars(is);
    StreamOutput to_gdb(os);

    AbstractOutput<string>& log_to_gdb = activity_log.Wrap("toGdb", to_gdb);

    Queue<string> gdb_response_queue;

    AbstractOutput<string>& log_gdb = activity_log.Wrap("fromGdb", gdb_response_queue);

    LookForPrompt look_for_prompt(log_gdb, "(gdb) ");
    Worker gdb_reader(raw_gdb_chars, look_for_prompt, "from gdb look for prompt", debug_log);

    LineInput raw_from_user(std::cin);
    StreamOutput raw_to_user(std::cout);

    AbstractOutput<string>& log_to_user = activity_log.Wrap("toUser", raw_to_user);

    Queue<UserCmd> user_cmd_queue;

    UserCmdParser cmd_parser(user_cmd_queue);

    AbstractOutput<string>& log_from_user = activity_log.Wrap("fromUser", cmd_parser);

    Worker user_reader(raw_from_user, log_from_user);

    bp::status s = c.wait();

    std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    */

    return 0;
}

