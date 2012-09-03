#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Breakpoint
{
    std::string file_name;
    int line_number;

    bool operator ==(Breakpoint const& that) const
    {
        return this->file_name == that.file_name && this->line_number == that.line_number;
    }
};

std::vector<Breakpoint> breakpoints;

extern "C"
{
    struct CollectorMarker {};
    typedef struct CollectorMarker IoObject;
    typedef IoObject IoMessage;
    struct IoState {};
}

extern "C"
{

#pragma GCC push_options
#pragma GCC optimize ("0")

void io_debugger_init(void *io_state)
{
    // Add some assembly lines to discourage the complier from optimizing away this function.
    asm ("nop;");
}

void io_debugger_break_here(void *self, void *locals, void *m,
    int breakpoint_number, const char *file_name, int line_number)
{
    // Add some assembly lines to discourage the complier from optimizing away this function.
    asm ("nop;");
}

int io_debugger_set_breakpoint(void *io_state, int breakpoint_number, const char *file_name, int line_number)
{
    cerr << "Io setting breakpoint " << io_state << ", " << breakpoint_number << ", \"" << file_name << "\", " << line_number << endl;

    if (breakpoint_number >= (int)breakpoints.size())
        breakpoints.resize(breakpoint_number);

    breakpoints[breakpoint_number] = {file_name, line_number};

    return breakpoint_number;
}

#pragma GCC pop_options
}

std::string file_name =
#ifdef __linux__
    "/home/dennis/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io"
#else // mac os
    "/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io"
#endif
;

void run_io()
{
    IoState io_state;
    io_debugger_init(&io_state);

    for (int line=0; line < 10; ++line)
    {
        IoObject self;
        IoObject locals;
        IoMessage m;

        auto it = find(breakpoints.begin(), breakpoints.end(), Breakpoint { file_name, line });

        if (it != breakpoints.end())
        {
            int breakpoint_number = it - breakpoints.begin();

            io_debugger_break_here(
                &self, &locals, &m,
                breakpoint_number, file_name.c_str(), line
            );
        }
    }
}

int main()
{
    cout << "Hello world!" << endl;
    cout << "Another line" << endl;
    cout << "Another line" << endl;

    cout << "About to run io code" << endl;
    run_io();
    cout << "Finished running io code" << endl;

    cout << "Goodbye, cruel world!" << endl;
    return 0;
}
