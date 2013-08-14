#include "UnitTest++.h"
#include "LikeMagic/StdBindings/TypeSystemInstance.hpp"

#include <iostream>

int main()
{
    int result = UnitTest::RunAllTests();
    std::cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );
    return result;
}
