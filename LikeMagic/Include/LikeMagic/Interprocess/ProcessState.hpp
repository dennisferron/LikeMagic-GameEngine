#pragma once

namespace LM {

enum class ProcessState
{
    NotStarted = 0,
    WaitForReturn,
    WaitForCommand,

    WaitingToFillCallRequest,
    LockingToWriteCallRequest,
    LockingToReadCallRequest,

    WaitingToFillCallReturn,
    LockingToWriteCallReturn,
    LockingToReadCallReturn,

    LockAcquired,
    LockReleased,
    WaitFinished,

    ExecutingCallRequest
};

}
