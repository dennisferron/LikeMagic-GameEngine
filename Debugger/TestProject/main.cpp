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
#pragma GCC push_options
#pragma GCC optimize ("0")

void io_debugger_break_here(IoObject *self, IoObject *locals, IoMessage *m, int breakpoint_number, char const* file_name, int line_number)
{
    // Prevent this function from being optimized away.
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

    // Simulate hitting a breakpoint.
    //if (!breakpoints.empty())
    //    io_debugger_break_here(1, breakpoints.at(0).file_name.c_str(), breakpoints.at(0).line_number);

    io_debugger_break_here(1, "/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io", 5);

    cout << "Goodbye, cruel world!" << endl;
    return 0;
}
