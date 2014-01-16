#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/StdBindings/StdBindings.hpp"

#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

#include <iostream>

using namespace Iocaste;
using namespace Iocaste::LMAdapters;
using namespace std;

void add_binding_test_bindings();
void add_term_test_bindings();
void add_typesystem_test_bindings();

IoVM* io_vm = nullptr;

void setup_io_vm()
{
    string bootstrap_path = "../../Iocaste/iovm/io/";
    io_vm = new IoVM(bootstrap_path);
}

int main()
{
    try
    {
        LM::type_system = LM::create_type_system();
        LM::add_bindings();
        add_binding_test_bindings();
        add_typesystem_test_bindings();
        add_term_test_bindings();
        setup_io_vm();
        int result = UnitTest::RunAllTests();
        delete io_vm;
        delete LM::type_system;
        //std::cout << "Done" << std::endl;
        std::cout << "Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
        return result;
    }
    catch (std::logic_error const& e)
    {
        std::cerr << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
        std::cout << "Error. Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
        return -1;
    }
    catch (...)
    {
        std::cout << "Error. Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
        return -1;
    }
}
