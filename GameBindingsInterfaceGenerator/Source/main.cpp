#include "GameBindingsInterfaceGenerator/Bindings.hpp"
#include "Iocaste/Run.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

#include <iostream>
using namespace std;

#include "InterfaceGenerator/Generator.hpp"
using namespace LM;

int main(int argc, const char *argv[])
{
    try
    {
        int result = 0;

        Interpreter::add_bindings();

        generate_interface_classes();

        cerr << "Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
    }
    catch (std::exception const& ex)
    {
        cerr << ex.what() << endl;
        return -1;
    }
}
