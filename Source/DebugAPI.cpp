#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Iocaste/DebugAPI.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/CShims/IoVMCpp.h"
using namespace Iocaste;
using namespace Iocaste::LikeMagicAdapters;

extern "C"
{

#pragma GCC push_options
#pragma GCC optimize ("0")

void io_debugger_init(void *io_state)
{
    cerr << "Io debugger init " << io_state << endl;

    // Add some assembly lines to discourage the complier from optimizing away this function.
    asm ("nop;");

    /*
    // Testing
    io_debugger_set_breakpoint(
        io_state,
        1,
        "/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/Test.io.inl",
        2
    );
    */
}


int io_debugger_break_here(void *self, void *locals, void *m,
    int breakpoint_number, const char *file_name, int line_number, int char_number)
{
    // Add some assembly lines to discourage the complier from optimizing away this function.
    asm ("nop;");

    // The Iocaste debugger will use gdb to change the return value
    // of the function to a different value if necessary.
    return StepMode_Run;
}

int io_debugger_set_breakpoint(void *io_state, int breakpoint_number, const char *file_name, int line_number)
{
    cerr << "Io setting breakpoint " << io_state << ", " << breakpoint_number << ", \"" << file_name << "\", " << line_number << endl;

    IoVM::get((IoState*)io_state)->set_breakpoint(
          breakpoint_number, file_name, line_number);

    return breakpoint_number;
}

char const* io_debugger_eval(void *self, void *target, const char *s)
{
    // TODO: Create an Io object to safely eval watches using similar code to Z_CLI.io
    //IoObject *result = IoState_on_doCString_withLabel_((IoState *)self, (IoObject *)target, s, null);
    return "not implemented";
}


#pragma GCC pop_options

}

