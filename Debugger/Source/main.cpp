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
#include "QueueInput.hpp"
#include "QueueOutput.hpp"
#include "LookForPrompt.hpp"
#include "Parser.hpp"
#include "StringEscaper.hpp"
#include "ActivityLog.hpp"

using namespace Iocaste::Debugger;

/*
struct ActivityLog
{
private:
    std::string label;
    std::string data;

    static std::string encode(std::string data)
    {
        std::stringstream r;
        for (int i=0; i<data.size(); ++i)
        {
            char c = data.at(i);
            switch (c)
            {
            case '\0':
                r << "\\0";
                break;
            case '\n':
                r << "\\n":
                break;
            case 26:
                r << "\\x" << std::hex(2) << c;
                break;
            default:
                r.put(c);
            }
        }
        return r;
    }

    static std::string decode(std::string data)
    {
        std::stringstream r;
        for (int i=0; i<data.size(); ++i)
        {

            if ()
        }
    }

public:

    std::string toLogStr()
    {
        return label + ": " + encode(data);
    }
};
*/

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
    //unescape(escape("teststr"));
    string str = "myTag:some\\nline";
    ActivityLogLine a;
    bool success = a.Parse(str);
    cerr << a.tag << endl;
    cerr << a.content << endl;
    return 0;

    std::vector<std::string> args;
    args.push_back("/usr/bin/gdb");

    for (int i=1; i<argc; ++i)
        args.push_back(argv[i]);

    bp::child c = start_child(args);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

    std::ofstream debug_log("/Users/dennisferron/debug.log", ofstream::out);

    debug_log << "testing..." << std::endl;

    CharInput from_gdb(is);
    StreamOutput to_gdb(os);

    LineInput from_user(std::cin);
    StreamOutput to_user(std::cout);

    ProducerConsumerQueue<string> gdb_chunks;
    LookForPrompt look_for_prompt(gdb_chunks, "(gdb) ");
    QueueInput<string> get_gdb_chunks(gdb_chunks);

    //Worker gdb_writer(from_user, to_gdb, "from cin to gdb cin", debug_log);
    Worker gdb_reader(from_gdb, look_for_prompt, "from gdb cout to find prompt", debug_log);
    //Worker gdb_to_screen(get_gdb_chunks, to_user, "from gdb chunks to cout", debug_log);


    std::string line;
    do
    {
        string gdb_out = get_gdb_chunks.ReadData();

//        if (0 == gdb_out.compare(0, 9, string("Breakpoint")))
//        {
//            debug_log << "Removing breakpoint confirmation just to see what happens" << endl;
//            gdb_out = "";
//        }

        if (0 == gdb_out.compare(1, 5, "/Users", 0))
        {
            /*
/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/Source/main.cpp:36:730:beg:0x100000d39
            */
            debug_log << "Replacing char in current pos" << endl << flush;
            cerr << "found /Users in " << gdb_out << endl;
            gdb_out.replace(74, 1, "1");
        }
        else
        {
            cerr << "Failed to match /Users in " << gdb_out << endl;
            debug_log << "Failed to match /Users in " << gdb_out << endl;
        }


//        if (gdb_out.at(0)==26)
//        {
//            debug_log << "Encountered eof char with " << gdb_out << endl;
//            gdb_out.erase(0, 2);
//            cout.put(26);
//            cout.put(26);
//            cout << flush;
//        }
        cout << gdb_out;
        cout << std::flush;

        line = from_user.ReadData();

        // We need to do this for input because we are getting the lines directly.
        // For output from GDB, the worker logs it already.
        debug_log << line << std::endl;

        SetPrompt set_prompt;
        if (Parse(line, set_prompt))
        {
            std::cerr << "New end marker: " << set_prompt.new_prompt << std::endl;
            look_for_prompt.set_end_marker(set_prompt.new_prompt);
        }

        SetBreakpoint breakpoint;
        if (Parse(line, breakpoint))
        {
            std::cerr << "Set breakpoint: " << breakpoint.file_name << ":" << breakpoint.line_number << std::endl;
//            stringstream ss;
//            ss << "break \"" << breakpoint.file_name << ":" << (breakpoint.line_number+10) << "\"";
//            // break "/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/Source/main.cpp:36"
//            to_gdb.WriteData(ss.str()+"\n");
//            continue;
        }

        to_gdb.WriteData(line + "\n");

    } while (line!="quit");

    bp::status s = c.wait();

    std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
}

