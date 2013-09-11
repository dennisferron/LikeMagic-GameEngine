#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/StdBindings/StdBindings.hpp"
#include <iostream>

void add_unit_test_bindings();

int main()
{
    try
    {
        LM::type_system = LM::create_type_system();
        LM::add_bindings();
        add_unit_test_bindings();
        int result = UnitTest::RunAllTests();
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
