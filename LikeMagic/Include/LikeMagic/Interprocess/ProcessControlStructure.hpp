#pragma once

#include "LikeMagic/Interprocess/ProcessState.hpp"
#include "LikeMagic/Interprocess/DataRegister.hpp"
#include "LikeMagic/Interprocess/CallReturn.hpp"
#include "LikeMagic/Interprocess/CallRequest.hpp"

namespace LikeMagic { namespace Interprocess {

struct ProcessControlStructure
{
    ProcessState state;
    boost::interprocess::interprocess_semaphore action_required;
    DataRegister<CallRequest> call_request;
    DataRegister<CallReturn> call_return;

    ProcessControlStructure()
        : action_required(0)
    {
        state = ProcessState::NotStarted;
    }
};

}}
