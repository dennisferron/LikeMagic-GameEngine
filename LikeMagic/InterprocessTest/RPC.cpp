#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include "RPC.hpp"

#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Interprocess;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;

using namespace boost::interprocess;
using namespace std;

RPC::~RPC()
{
    shared_memory_object::remove(shared_memory_name);
}

std::string RPC::get_state_name(ProcessState s) const
{
    switch (s)
    {
        case ProcessState::NotStarted: return "NotStarted";
        case ProcessState::WaitForReturn: return "WaitForReturn";
        case ProcessState::WaitForCommand: return "WaitForCommand";
        case ProcessState::WaitingToFillCallRequest: return "WaitingToFillCallRequest";
        case ProcessState::LockingToWriteCallRequest: return "LockingToWriteCallRequest";
        case ProcessState::LockingToReadCallRequest: return "LockingToReadCallRequest";
        case ProcessState::WaitingToFillCallReturn: return "WaitingToFillCallReturn";
        case ProcessState::LockingToWriteCallReturn: return "LockingToWriteCallReturn";
        case ProcessState::LockingToReadCallReturn: return "LockingToReadCallReturn";
        case ProcessState::LockAcquired: return "LockAcquired";
        case ProcessState::LockReleased: return "LockReleased";
        case ProcessState::WaitFinished: return "WaitFinished";
        case ProcessState::ExecutingCallRequest: return "ExecutingCallRequest";
        default: return "<Unknown>";
    }
}

void RPC::scan() const
{
    for (int i=0; i < 3; ++i)
    {
        auto& p = data->processes[i];
        cout << i << ": " << get_state_name(p.state) << endl;
    }
}

RPC::RPC(AbstractTypeSystem& type_system_, bool is_first_)
    :
        type_system(type_system_),
        shared_memory_name("MySharedMemory"),
        is_first(is_first_),
        invocation_counter(0),
        transporter(type_system_)
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

CallReturn RPC::listen(int wanted_invocation_id, bool wants_rvalue)
{
    while (true)
    {
        cout << "Process " << is_first << " listening for invocation_id " << wanted_invocation_id << endl;

        // First check if we already have the rvalue that we
        // wish to receive (can happen if one process returned
        // a value while we were busy servicing another process).
        if (wants_rvalue)
        {
            auto found_rvalue
                = cached_rvalues.find(wanted_invocation_id);
            if (found_rvalue != cached_rvalues.end())
            {
                return found_rvalue->second;
            }
        }

        if (wants_rvalue)
            pcs->state = ProcessState::WaitForReturn;
        else
            pcs->state = ProcessState::WaitForCommand;

        // If we don't have the rvalue we want yet, or if we
        // are only waiting for a method to execute, then wait
        // to be signaled that something is ready for us.
        cout << "Process " << is_first << " waiting on action_required." << endl;
        this->pcs->action_required.wait();
        pcs->state = ProcessState::WaitFinished;

        // Next figure out why we were awoken.

        // If we were awoken for an rvalue, add it to the cache.
        auto& rval_reg = this->pcs->call_return;

        // We wait against the writing_in_progress semaphore in
        // order to not see the DataRegister in inconsistent state.
        pcs->state = ProcessState::LockingToReadCallReturn;
        rval_reg.writing_in_progress.wait();
        pcs->state = ProcessState::LockAcquired;

        if (rval_reg.has_data)
        {
            int found_invocation_id = rval_reg.data.invocation_id;
            cached_rvalues[found_invocation_id] = rval_reg.data;
            rval_reg.writing_in_progress.post();
            rval_reg.available_for_write.post();
            pcs->state = ProcessState::LockReleased;
            continue;
        }
        else
        {
            rval_reg.writing_in_progress.post();
            pcs->state = ProcessState::LockReleased;

            // If we weren't awoken for an rvalue check
            // if we were awoken to execute a call command.
            auto& args_reg = this->pcs->call_request;

            pcs->state = ProcessState::LockingToReadCallRequest;
            args_reg.writing_in_progress.wait();
            pcs->state = ProcessState::LockAcquired;

            if (args_reg.has_data)
            {
                CallRequest temp = args_reg.data;
                args_reg.writing_in_progress.post();
                args_reg.available_for_write.post();
                pcs->state = ProcessState::LockReleased;

                // Execute the args and enplace the rvalue
                pcs->state = ProcessState::ExecutingCallRequest;
                int arg = *(int*)temp.args_buffer;
                int result = execute(temp.method_id, arg);

                DataRegister<CallReturn>& wrv_reg = temp.sender->call_return;

                pcs->state = ProcessState::WaitingToFillCallReturn;
                wrv_reg.available_for_write.wait();
                pcs->state = ProcessState::LockingToWriteCallReturn;
                wrv_reg.writing_in_progress.wait();
                pcs->state = ProcessState::LockAcquired;

                CallReturn& wrv_val = wrv_reg.data;
                wrv_val.invocation_id = temp.invocation_id;
                *(int*)wrv_val.rvalue_buffer = result;
                wrv_reg.has_data = true;
                wrv_reg.writing_in_progress.post();
                pcs->state = ProcessState::LockReleased;
                cout << "Process " << is_first << " posting to other process action_required " << endl;
                temp.sender->action_required.post();

                continue;
            }
            else
            {
                // Not really sure why we were awoken then;
                // could be something wrong but what to do?
                // (If we switch to semaphores with a timeout,
                // or if we use a post to wake the process to
                // shut it down, this may not be an error.)
                cerr << "Something may have gone wrong; process was awoken with nothing to do." << endl;
                args_reg.writing_in_progress.post();
                args_reg.available_for_write.post();
                pcs->state = ProcessState::LockReleased;
            }
        }
    }
}

int RPC::call_int(int method, int arg)
{
    CallReturn ret = call(-1, method, arg);
    int rval = *(int*)ret.rvalue_buffer;
    return rval;
}

int RPC::execute(int method, int arg)
{
    int rvalue;

    // "Do work" and possibly call other proce
    switch (method)
    {
        case 0:
            rvalue = 1*arg + call_int(1,arg+1);
            break;
        case 1:
            rvalue = 10*arg + call_int(2,arg+1);
            break;
        case 2: default:
            rvalue = 100*arg;
            break;
    }

    return rvalue;
}

CallReturn RPC::call(int object_handle, int method, int arg)
{
    // We build the request in a temporary local buffer first.
    // It's actually pretty important that we don't lock the
    // destination DataRegister until after we've evaled all the
    // method arguments, because what if evaluation of one of
    // the arguments requires using the same target process?
    CallRequest request_args;

    request_args.sender = this->pcs;
    request_args.invocation_id = ++invocation_counter;
    request_args.object_handle = object_handle;
    request_args.method_id = method;
    request_args.object_handle = 0;

    // In this demo there's only a single int arg.
    request_args.args_count = 1;

    //*(int*)&request_args.args_buffer[0] = arg;

    auto term = Term<int, true>::create(arg);
    ArgList arg_list;
    arg_list.push_back(term);

    int temp = term->eval();
    cout << "Term is " << temp << endl;

    TypeIndex type_index = BetterTypeInfo::create_index<int>();
    TypeInfoList arg_types;
    arg_types.push_back(type_index);

    cout << "type_system has_conv<int>(term): " << type_system.has_conv<int>(term) << endl;
    cout << "type_system has_conv(type_index, type_index): " << type_system.has_conv(type_index, type_index) << endl;
    auto term2 = type_system.try_conv<int>(term);

    char* buffer = request_args.args_buffer;

    cout << "About to write_args original args=" << arg << " buffer="
        << (int)buffer[0] << ","
        << (int)buffer[1] << ","
        << (int)buffer[2] << ","
        << (int)buffer[3] << ","
        << (int)buffer[4] << endl;

    transporter.write_args(arg_types, request_args.args_buffer, arg_list);
    cout << "original args=" << arg << " buffer="
        << (int)buffer[0] << ","
        << (int)buffer[1] << ","
        << (int)buffer[2] << ","
        << (int)buffer[3] << ","
        << (int)buffer[4] << endl;

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
    cout << "caller waiting for request register available_for_write" << endl;
    pcs->state = ProcessState::WaitingToFillCallRequest;
    target_pcs->call_request.available_for_write.wait();
    pcs->state = ProcessState::LockingToWriteCallRequest;
    target_pcs->call_request.writing_in_progress.wait();
    pcs->state = ProcessState::LockAcquired;
    target_pcs->call_request.data = request_args;
    target_pcs->call_request.has_data = true;
    target_pcs->call_request.writing_in_progress.post();
    target_pcs->action_required.post();
    pcs->state = ProcessState::LockReleased;

    // listen for rvalue or for a re-entrant call.
    return listen(request_args.invocation_id, true);
}

