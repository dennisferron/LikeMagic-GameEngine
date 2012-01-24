
#include "Interpreter/Bindings.hpp"
#include "Interpreter/Protos.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Backends::Io;

using namespace Interpreter;

#include <sstream>
#include <stdexcept>

#include "boost/algorithm/string/trim.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

using namespace std;


#include "IoState.h"

void IoAddonsInit(IoObject *context);

//#define IOBINDINGS

#ifdef IO_CHECK_ALLOC
#define IO_SHOW_STATS 1
#endif

#include "Iocaste/Exception.hpp"

#ifdef IO_SHOW_STATS
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double System_UserTime(void)
{
	struct rusage u;
	int r = getrusage(0, &u);
	return r == -1 ? -1 : u.ru_utime.tv_sec + (((double)u.ru_utime.tv_usec)/1000000);
}

#endif

#include <iostream>
using namespace std;

// Predicate for trimming characters up to a directory marker.
struct IsNotDir { bool operator()(char c) { return c != '/' && c != '\\'; } };

void do_cli(IoVM& vm)
{
    cout << std::endl;
    cout << "LikeMagic Io binding library." << std::endl;
    cout << "To run file from system commandline: LikeMagic <filename.io>" << std::endl;
    cout << "To run file from the Io> prompt: doFile(\"<filename.io>\")" << std::endl;
    cout << "" << std::endl;
    cout << "Type 'exit' to quit." << std::endl;
    vm.run_cli();
}

void do_file(IoVM& vm, string file_name)
{
    std::string scriptPath(file_name);
    boost::algorithm::trim_right_if(scriptPath, IsNotDir());
    vm.add_proto("scriptPath", scriptPath, NamespacePath::global(), true);

    std::stringstream code;
    code << "doFile(\"" << file_name << "\")";
    vm.do_string(code.str());
}


int main(int argc, const char *argv[])
{
 #ifdef USE_DMALLOC
    // Starting LikeMagic in codeblocks debug mode doesn't propagate the dmalloc environment settings.  I don't know why.
    dmalloc_debug_setup("check-blank,log=~/dmalloc.log");
#endif
    try
    {
        RuntimeTypeSystem type_sys;
        add_bindings(type_sys);

        IoVM vm(type_sys);

        for (int i=1; i<argc; ++i)
        {
            cout << flush;
            if (string(argv[i]) == "--runCLI")
                do_cli(vm);
            else
                do_file(vm, argv[i]);
        }

        cout << "Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
        return 0;
    }
    catch (Iocaste::ScriptException const& ex)
    {
        cout << "main.cpp caught unhandled script exception: " << ex.what() << endl;
    }
    catch (std::logic_error e)
    {
        cout << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
    }
    catch (std::exception e)
    {
        cout << "Exited with exception " << e.what() << std::endl;
    }
    catch (...)
    {
        cout << "main.cpp caught unhandled unknown exception" << endl;
    }

    cout << "Exiting with error" << endl;
    return -1;
}
