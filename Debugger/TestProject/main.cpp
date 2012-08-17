#include <iostream>
#include <vector>
using namespace std;

struct Breakpoint
{
    std::string file_name;
    int line_number;
};

std::vector<Breakpoint> breakpoints;

extern "C"
{
    struct CollectorMarker {};
    typedef struct CollectorMarker IoObject;
    typedef IoObject IoMessage;

#pragma GCC push_options
#pragma GCC optimize ("0")

void io_debugger_break_here(IoObject *self, IoObject *locals, IoMessage *m,
                            int breakpoint_number, char const* file_name, int line_number)
{
    // Add some assembly lines to discourage the complier from optimizing away this function.
    asm ("nop;");
}

int io_debugger_set_breakpoint(char const* file_name, int line_number)
{
    breakpoints.push_back({file_name, line_number});
    return breakpoints.size();
}

#pragma GCC pop_options
}


int main()
{
    cout << "Hello world!" << endl;
    cout << "Another line" << endl;
    cout << "Another line" << endl;

    IoObject self;
    IoObject locals;
    IoMessage m;

    io_debugger_break_here(&self, &locals, &m,
           1, "/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io", 5);

    cout << "Goodbye, cruel world!" << endl;
    return 0;
}
