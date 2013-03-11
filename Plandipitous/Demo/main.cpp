#include <iostream>

using namespace std;

int do_test();

namespace Plandipitous {
    void do_test_2();
}

int main()
{
    //do_test();
    Plandipitous::do_test_2();
    std::cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );
    return 0;
}
