#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
namespace bp = ::boost::process;

#include "Worker.hpp"

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

    //std::ofstream debug_log("debug.log", ios::out | ios::binary);
    std::ofstream debug_log("debug.log", ofstream::out);



    Worker worker1(std::cin, os, "from cin to child stdin", debug_log);
    Worker worker2(is, std::cout, "from child stdout to cout", debug_log);
    //Worker worker2(std::cin, std::cout, "from child stdout to cout", debug_log);

    while (!worker2.is_stopped())
    {
        pthread_yield();
        usleep(100);
    }

    worker1.stop_thread();

    c.wait();

    return 0;
}
