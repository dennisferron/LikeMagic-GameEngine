
#include "Interpreter/Bindings.hpp"
#include "Iocaste/Run.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    try
    {
        int result = Iocaste_run(argc, argv, &Interpreter::add_bindings);

        if (result != 0)
        {
            cerr << "Exit with error code " << result << endl;
            cerr << "Press enter..." << std::endl;
            std::cin.ignore( 99, '\n' );
        }
    }
    catch (std::exception const& ex)
    {
        cerr << ex.what() << endl;
        return -1;
    }
}
