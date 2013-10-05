
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

using namespace LM;
using namespace Iocaste::LMAdapters;

#include "Iocaste/Run.hpp"

#include <sstream>
#include <stdexcept>

#include "boost/algorithm/string/trim.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
//#include "LikeMagic/StdBindings/ScriptUtil.hpp"
#include "boost/program_options.hpp"

#include "Iocaste/Exception.hpp"
#include "boost/exception/info.hpp"
#include "boost/exception/get_error_info.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

using namespace std;


namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

}

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
struct IsNotDirChar { bool operator()(char c) { return c != '/' && c != '\\'; } };

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
    boost::algorithm::trim_right_if(scriptPath, IsNotDirChar());
    //vm.add_proto("scriptPath", scriptPath, NamespacePath::global(), true);
    vm.set_script_path(scriptPath);
    std::stringstream code;
    code << "doFile(\"" << file_name << "\")";
    vm.do_string(code.str());
}

IOCASTE_API int Iocaste_run(int argc, const char *argv[], void (*add_bindings)())
{
    namespace po = boost::program_options;

#ifdef USE_DMALLOC
    // Starting LikeMagic in codeblocks debug mode doesn't propagate the dmalloc environment settings.  I don't know why.
    dmalloc_debug_setup("check-blank,log=~/dmalloc.log");
#endif

    // If the IoVM object is declared inside the try catch as a stack variable,
    // it gets destructed when there's an exception and then is unavailable for e.g.
    // printing the error message or the stack.  Should maybe create with new and/or
    // use an intrusive_ptr to track references to the IoVM object.
    IoVM* vm=NULL;
    po::options_description desc("Options");

    try
    {
        std::string bootstrap_path;
        std::string engine_path;
        std::string game_path;
        std::string asset_path;

        desc.add_options()
            ("help", "Print help message")
            ("language", po::value<std::string>(&bootstrap_path)->required(), "Path to core Io language scripts.")
            ("engine", po::value<std::string>(&engine_path)->required(), "Path to Engine scripts.")
            ("game", po::value<std::string>(&game_path)->required(), "Path to game startup scripts.")
            ("assets", po::value<std::string>(&asset_path)->required(), "Path to game assets.") ;

        po::variables_map var_map;

        po::store(po::parse_command_line(argc, argv, desc),
                var_map); // can throw

        /** --help option
        */
        if ( var_map.count("help") )
        {
            std::cout << "Iocaste interpreter." << std::endl
                << desc << std::endl;
            return SUCCESS;
        }

        po::notify(var_map);    // throws on error, so do after help in case
                                // there are any problems

        (*add_bindings)();

        cout << "Loading Io init files at " << bootstrap_path << endl;
        vm = new IoVM(bootstrap_path);
        vm->set_path("engine", engine_path);
        vm->set_path("game", game_path);
        vm->set_path("assets", asset_path);

        for (int i=2; i<argc; ++i)
        {
            cout << flush;
            if (string(argv[i]) == "--runCLI")
                do_cli(*vm);
            else
                do_file(*vm, argv[i]);
        }

        delete vm;
        vm=NULL;
        delete type_system;
        type_system=NULL;

        cout << "Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );

        return SUCCESS;
    }
    catch(po::error& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return ERROR_IN_COMMAND_LINE;
    }
    catch (Iocaste::ScriptException const& ex)
    {
        cerr << "main.cpp caught unhandled script exception: " << ex.what() << endl << flush;

        if( auto err=boost::get_error_info<Iocaste::Exception::file_name_info>(ex) )
        {
            for (size_t i=0; i<err->size(); ++i)
                std::cerr << std::string(i, '\t')  << "via file: " << (*err)[i] << endl << flush;
        }
    }
    catch (Iocaste::Exception const& iex)
    {
        cerr << "main.cpp caught unhandled boost exception: " << iex.what() << endl << flush;

        if( auto err=boost::get_error_info<Iocaste::Exception::file_name_info>(iex) )
        {
            for (size_t i=0; i<err->size(); ++i)
                std::cerr << std::string(i, '\t')  << "via file: " << (*err)[i] << endl << flush;
        }
    }
    catch (std::logic_error const& e)
    {
        cerr << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
    }
    catch (std::exception const& e)
    {
        cerr << "Exited with exception " << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "main.cpp caught unhandled unknown exception" << endl;
    }

    cerr << "Exiting with error" << endl;

    delete vm;
    delete type_system;

    cerr << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );
    return ERROR_UNHANDLED_EXCEPTION;
}
