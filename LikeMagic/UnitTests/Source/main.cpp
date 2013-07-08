#include "UnitTest++.h"
#include "LikeMagic/StdBindings/TypeSystemInstance.hpp"
#include "UnitTests/TypeSystemInstance.hpp"

#include <iostream>

int main()
{
    type_sys = LikeMagic::StdBindings::create_typesystem();
    int result = UnitTest::RunAllTests();
    delete type_sys;
    std::cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );
    return result;
}
