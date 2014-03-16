

extern "C" void io_debugger_init(void *io_state);

extern "C" int io_debugger_break_here(void *self, void *locals, void *m,
    int breakpoint_number, const char *file_name,
    int line_number, int char_number);

extern "C" int io_debugger_set_breakpoint(void *io_state, int breakpoint_number,
                               const char *file_name, int line_number);

