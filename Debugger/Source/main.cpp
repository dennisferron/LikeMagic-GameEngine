#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace bp = ::boost::process;

#include "Worker.hpp"
#include "CharInput.hpp"
#include "LineInput.hpp"
#include "StreamOutput.hpp"
#include "Queue.hpp"
#include "LookForPrompt.hpp"
#include "Parser.hpp"
#include "ActivityLog.hpp"
#include "Channel.hpp"

using namespace Iocaste::Debugger;

enum class MainLoopState
{
    ReadUser,
    WriteGdb,
    ReadGdb,
    WriteUser,
    Quit
};

void main_loop(Channel<UserCmd, GdbResponse> gdb, Channel<GdbResponse, UserCmd> user)
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
    std::ofstream log_file("/Users/dennisferron/debug.log", ofstream::out);
    StreamOutput debug_log(log_file, true);
    ActivityLog activity_log(debug_log);

    bp::child c = start_gdb(argc, argv);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

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

    /*

    FromUser to Worker to Log to CmdParser to Queue
    IssueCmd to CmdWriter to Log to ToGdb
    FromGdb  to Worker to LookForPrompt to Log to GdbParser to Queue to ProcessResponse
    IssueResponse to ResponseWriter to ToUser

    */

    bp::status s = c.wait();

    std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
}

