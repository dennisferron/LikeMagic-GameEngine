#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Breakpoint
{
    int breakpoint_number;
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
    cerr << "Io debugger init " << io_state << endl;

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

    breakpoints[breakpoint_number-1] = { breakpoint_number, file_name, line_number};

    for (Breakpoint bk : breakpoints)
        cerr << "Breakpoint " << bk.breakpoint_number << " " << bk.file_name << ":" << bk.line_number << endl;

    return breakpoint_number;
}

#pragma GCC pop_options

}

extern "C"
{
void iovm_set_breakpoints(IoMessage *self) /* sets label for children too */
{
    IoState* state = get_io_state(self);
    iovm = reinterpret_cast<IoVM*>(state->callbackContext);
    iovm->setPendingBreakpoints(self);

    DATA(self)->breakpoint = findBreakpoint(DATA(self)->label, DATA(self)->lineNumber, DATA(self)->charNumber));

	List_do_with_(DATA(self)->args, (ListDoWithCallback *)IoMessage_label_, ioSymbol);

	if (DATA(self)->next)
	{
		IoMessage_label_(DATA(self)->next, ioSymbol);
	}
}
}

