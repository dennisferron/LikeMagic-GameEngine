#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
namespace bp = ::boost::process;

#include "Worker.hpp"
#include "CharInput.hpp"
#include "LineInput.hpp"
#include "StreamOutput.hpp"
#include "QueueInput.hpp"
#include "QueueOutput.hpp"
#include "LookForPrompt.hpp"

using namespace Iocaste::Debugger;

bp::child start_child(std::vector<string> args)
{
    std::string exec = args[0];

    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();
    ctx.stdin_behavior = bp::capture_stream();

    return bp::launch(exec, args, ctx);
}

int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    args.push_back("/usr/bin/gdb");

    for (int i=1; i<argc; ++i)
        args.push_back(argv[i]);

    bp::child c = start_child(args);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

    std::ofstream debug_log("debug.log", ofstream::out);

    CharInput from_gdb(is);
    StreamOutput to_gdb(os);

    LineInput from_user(std::cin);
    StreamOutput to_user(std::cout);

    ProducerConsumerQueue<string> gdb_chunks;
    LookForPrompt look_for_prompt(gdb_chunks, "(gdb) ");
    QueueInput<string> get_gdb_chunks(gdb_chunks);

    Worker gdb_writer(from_user, to_gdb, "from cin to gdb cin", debug_log);
    Worker gdb_reader(from_gdb, look_for_prompt, "from gdb cout to find prompt", debug_log);
    Worker gdb_to_screen(get_gdb_chunks, to_user, "from gdb chunks to cout", debug_log);

    while (!gdb_reader.is_stopped())
    {
        pthread_yield();
        usleep(100);
    }

    gdb_writer.stop_thread();

    c.wait();

    return 0;
}

