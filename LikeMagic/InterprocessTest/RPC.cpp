
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include "RPC.hpp"

using namespace boost::interprocess;

RPC::~RPC()
{
    shared_memory_object::remove(shared_memory_name);
}

RPC::RPC(bool is_first_) : shared_memory_name("MySharedMemory"), is_first(is_first_), invocation_counter(0)
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

    pcs = &data->processes[(int)is_first];
    other_pcs = &data->processes[(int)!is_first];
}

void RPC::listen(int wanted_invocation_id, bool wants_rvalue)
{
    int rvalue_invocation_id;
    bool has_rvalue = false;

    while (true)
    {
        // First check if we already have the rvalue that we
        // wish to receive (can happen if one process returned
        // a value while we were busy servicing another process).
        if (wants_rvalue)
        {
            auto found_rvalue
                = cached_rvalues.find(wanted_invocation_id);
            if (found_rvalue != cached_rvalues.end())
            {
                return *found_rvalue;
            }
        }

        // If we don't have the rvalue we want yet, or if we
        // are only waiting for a method to execute, then wait
        // to be signaled that something is ready for us.
        this->pcs->action_required.wait();

        // Next figure out why we were woken.  If it was for
        // an rvalue, add it to the cache.
        // We wait against the writing_in_progress semaphore in
        // order to not see the DataRegister in inconsistent state.
        auto& rval_reg = this->pcs->call_return;
        rval_reg.writing_in_progress.wait();
        if (rval_reg.has_data)
            cached_rvalues[rval_reg.invocation_id] = rval_reg;
        rval_reg.writing_in_progress.post();

        // TODO:  Execute args reg.
    }


static int execute(int method, int arg)
{
    int rvalue;

    // "Do work" and possibly call other proce
    switch (method)
    {
        case 0:
            std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            rvalue = call(1,arg+1)+call(1,arg+2);
            std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            break;
        case 1:
            std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" <<  hintmethod<< " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            rvalue = call(2,arg+10)+call(2,arg+10);
            std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            break;
        case 2: default:
            std::cout << "Before execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            rvalue = arg+200;
            std::cout << "After execute: Process " << is_first << " purpose=" << purpose << " method=" << method << " hintmethod=" << hintmethod << " org_depth=" << org_depth << " stack_depth=" << data->stack_depth << std::endl;
            break;
    }

    return rvalue;
}

int RPC::call(int object_handle, int method, int arg)
{
    // We build the request in a temporary local buffer first.
    // It's actually pretty important that we don't lock the
    // destination DataRegister until after we've evaled all the
    // method arguments, because what if evaluation of one of
    // the arguments requires using the same target process?
    CallRequest request_args;

    request_args->sender = this->pcs;
    request_args->invocation_id = ++invocation_counter;
    request_args->object_handle = object_handle;
    request_args->method_id = method;
    request_args->object_handle =

    // In this demo there's only a single int arg.
    request_args->args_count = 1;
    *(int*)&request_args.args_buffer[0] = arg;

    // Typically would look up other proces using object_handle.
    // (Actually would probably have an object proxy that holds
    // both the object handle and the process control pointer.)
    auto target_pcs = other_pcs;

    // This is the call procedure:
    //  1.  Wait for destination register to be empty.
    //  2.  Lock the register from reading while we write.
    //  3.  Write the register
    //  4.  Mark data available.
    //  5.  Release the lock for reading.
    //  6.  Signal the waiting target process.
    // (We do not ourselves post the available semaphore.
    //  The target procedure does that itself when ready.)
    target_pcs->call_request.available_for_write.wait();
    target_pcs->call_request.writing_in_progress.wait();
    target_pcs->data = request_args;
    target_pcs->has_data = true;
    target_pcs->call_request.writing_in_progress.post();
    target_pcs->action_required->post();

    // listen for rvalue or for a re-entrant call.
    return listen(request_args->invocation_id);
}

