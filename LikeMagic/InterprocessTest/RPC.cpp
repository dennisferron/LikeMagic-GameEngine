
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include "RPC.hpp"

using namespace boost::interprocess;

RPC::~RPC()
{
    shared_memory_object::remove(shared_memory_name);
}

RPC::RPC(bool is_first_) : shared_memory_name("MySharedMemory"), is_first(is_first_)
{
    if (is_first)
        shared_memory_object::remove(shared_memory_name);

    shm = new shared_memory_object( open_or_create, shared_memory_name, read_write);

    shm->truncate(sizeof(SharedMemoryFormat));
    region = new mapped_region(*shm, read_write);

    void* addr = region->get_address();

    if (is_first)
        data = new (addr) SharedMemoryFormat;
    else
        data = reinterpret_cast<SharedMemoryFormat*>(addr);
}

void RPC::listen(int org_depth, char const* purpose, int hintmethod)
{
    std::cout << "Before " << purpose << " Process " << is_first << " hintmethod=" << hintmethod << " sp=" << data->stack_depth << " org_depth=" << org_depth << std::endl;

    // "wait_call_or_rvalue()"
    // Wait for a signal to this process
    if (is_first)
        data->process_a.wait();
    else
        data->process_b.wait();

    std::cout << "After " << purpose << " Process " << is_first << " hintmethod=" << hintmethod << " sp=" << data->stack_depth << " org_depth=" << org_depth << std::endl;

    // Detect if a call was made (otherwise we are merely waiting for rvalue from OTHER process)
    while (data->stack_depth > org_depth)
    {
        int method = data->method;
        int arg = data->arg;

        int rvalue;

        // "Do work" and possibly call other proce
        switch (method)
        {
            case 0:
                std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
                rvalue = call(1,arg+1)+call(1,arg+2); break;
                std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            case 1:
                std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" <<  hintmethod<< " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
                rvalue = call(2,arg+10)+call(2,arg+10); break;
                std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            case 2: default:
                std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
                rvalue = arg+200; break;
                std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
        }

        data->rvalue = rvalue;

        std::cout << purpose << " Process " << is_first << " hintmethod=" << hintmethod << " method=" << method << " was executed at stack_depth=" << data->stack_depth << " arg=" << arg << " rvalue=" << rvalue << std::endl;

        // "post_return()"
        // Post other process that a return value is ready.
        if (is_first)
            data->process_b.post();
        else
            data->process_a.post();

        // "wait_call_or_rvalue()"
        // Wait for a signal to this process
        if (is_first)
            data->process_a.wait();
        else
            data->process_b.wait();
    }
    // Else nothing to do; we were just waiting on other process.
    std::cout << purpose << " Process " << is_first << " hintmethod=" << hintmethod << " just returned at stack_depth=" << data->stack_depth << " data->arg=" << data->arg << " data->rvalue=" << data->rvalue << std::endl;
}

int RPC::call(int method, int arg)
{
    if (data->stack_depth >= 10)
    {
        std::cout << "Infinite recursion detected, aborting." << std::endl;
        return 0;
    }

    std::cout << "Start call from Process " << is_first << " method=" << method << " prior stack_depth=" << data->stack_depth << " this arg=" << arg << " old data arg=" << data->arg << " old rvalue=" << data->rvalue << std::endl;

    int depth = ++data->stack_depth;
    data->method = method;
    data->arg = arg;

    // "post_call()"
    // Post other process that an arg value is ready.
    if (is_first)
        data->process_b.post();
    else
        data->process_a.post();

    // listen for rvalue or for a re-entrant call.
    listen(depth, "Wait for return", method);

    int rvalue = data->rvalue;

    // Take the rvalue we got off the stack
    std::cout << "After call from " << is_first << " method=" << method << " this depth=" << depth << " sp=" << data->stack_depth << " this arg=" << arg << " data arg=" << data->arg << " rvalue=" << rvalue << std::endl;

    // "Pop" the frame we created.
    --data->stack_depth;

    return rvalue;
}

