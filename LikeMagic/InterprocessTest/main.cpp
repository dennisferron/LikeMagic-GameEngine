#include <cstdlib> //std::system
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "RPC.hpp"
#include "WindowsProcess.hpp"
#include "LikeMagic/StdBindings/TypeSystemInstance.hpp"

using namespace std;

using namespace LM;
using namespace LM::Interprocess;
using namespace LM::StdBindings;

void do_call(RPC& rpc, string order)
{
    std::cout << order << " running do_call" << std::endl;
    int arg0 = 2;
    int ret0 = rpc.call_int(0,arg0);
    std::cout << order << "call(" << arg0 << ") -> " << ret0 << std::endl;
}

void do_listen(RPC& rpc, string order)
{
    std::cout << order << " listening" << std::endl;
    rpc.listen(-1, false);
    std::cout << order << " exiting" << std::endl;
}

void do_mode(RPC& rpc, string order, string mode)
{
    if (mode == "call")
        do_call(rpc, order);
    else if (mode == "listen")
        do_listen(rpc, order);
    else
        throw std::runtime_error("Invalid mode");
}

int main (int argc, char *argv[])
{
    RuntimeTypeSystem* type_system = create_typesystem();

    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <parent|child|scan> <call|listen>" << endl;
    }
    else
    {
        string order = argv[1];
        string mode = argv[2];

        if (order == "scan")
        {
            RPC scan_rpc(*type_system, false);
            scan_rpc.scan();
        }
        else if (order == "parent")
        {
            // in parent

            std::cout << "Parent starting" << std::endl;
            RPC rpc0(*type_system, true);

            // launch child
            create_process(string(argv[0]) + " " + "child" + " " +
                (mode == "listen" ? "call" : "listen"), false);

            do_mode(rpc0, order, mode);

            std::cout << "Parent process exiting." << std::endl;
        }
        else
        {
            // in child

            std::cout << "Child starting" << std::endl;
            RPC rpc1(*type_system, false);

            do_mode(rpc1, order, mode);

            std::cout << "Child exiting" << std::endl;
        }
    }

    return 0;
}
