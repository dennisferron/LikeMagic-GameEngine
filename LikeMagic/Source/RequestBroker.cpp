#include "LikeMagic/Interprocess/RequestBroker.hpp"

#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include <iostream>

#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/TypeSystem.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Interprocess;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Utility;

using namespace boost::interprocess;
using namespace std;

RequestBroker::~RequestBroker()
{
}

std::string RequestBroker::get_state_name(ProcessState s) const
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

RequestBroker::RequestBroker(SharedObjectRegistry& object_registry_, ProcessControlStructure* pcs_)
    :
        object_registry(object_registry_),
        invocation_counter(0),
        pcs(pcs_),
        transporter()
{
}

CallReturn RequestBroker::listen(int wanted_invocation_id, bool wants_rvalue)
{
    return CallReturn();
    /*
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
                LikeMagic::Utility::TypeIndex arg_type_index
                    = LikeMagic::Utility::BetterTypeInfo::create_index<int>();
                LikeMagic::Utility::TypeInfoList arg_types;
                arg_types.push_back(arg_type_index);
                ArgList arg_list = transporter.read_args(arg_types, temp.args_buffer);
                int arg = try_conv<int>(arg_list[0])->eval();
                int result = execute(temp.method_id, arg);
                auto method_call = Term<int, true>::create(result);

                DataRegister<CallReturn>& wrv_reg = temp.sender->call_return;

                pcs->state = ProcessState::WaitingToFillCallReturn;
                wrv_reg.available_for_write.wait();
                pcs->state = ProcessState::LockingToWriteCallReturn;
                wrv_reg.writing_in_progress.wait();
                pcs->state = ProcessState::LockAcquired;

                CallReturn& wrv_val = wrv_reg.data;
                wrv_val.invocation_id = temp.invocation_id;
                LikeMagic::Utility::TypeIndex ret_type_index
                    = LikeMagic::Utility::BetterTypeInfo::create_index<int>();
                transporter.write_value(ret_type_index, wrv_val.rvalue_buffer, method_call);
                wrv_reg.has_data = true;
                wrv_reg.writing_in_progress.post();
                pcs->state = ProcessState::LockReleased;
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
    */
}

CallReturn RequestBroker::call(ProcessControlStructure* target_pcs, ObjectHandle object_handle,
                               MethodId method_id, TypeInfoList arg_types, ArgList args)
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
    request_args.method_id = method_id;
    request_args.object_handle = 0;

    // In this demo there's only a single int arg.
    request_args.args_count = args.size();

    transporter.write_args(arg_types, request_args.args_buffer, args);

    // This is the call procedure:
    //  1.  Wait for destination register to be empty.
    //  2.  Lock the register from reading while we write.
    //  3.  Write the register
    //  4.  Mark data available.
    //  5.  Release the lock for reading.
    //  6.  Signal the waiting target process.
    // (We do not ourselves post the available semaphore.
    //  The target procedure does that itself when ready.)
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

