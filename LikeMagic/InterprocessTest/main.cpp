#include <cstdlib> //std::system
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "RPC.hpp"

int main (int argc, char *argv[])
{
    std::cout << "Parent starting" << std::endl;
    RPC rpc0(true);
    int childPID = fork();

    if (childPID !=0 )
    {
        // parent
        std::cout << "Parent completed fork of child " << childPID << std::endl;
        std::cout << "Parent calling child" << std::endl;
        int arg0 = 1;
        int ret0 = rpc0.call(0,arg0);
        std::cout << "call(" << arg0 << ") -> " << ret0 << std::endl;
        std::cout << "Parent process exiting." << std::endl;
    }
    else
    {
        // child
        std::cout << "Child starting" << std::endl;
        RPC rpc1(false);
        std::cout << "Child listening" << std::endl;
        rpc1.listen(-1, "Just listening",-1);
        std::cout << "Child exiting" << std::endl;
    }

    return 0;
}
