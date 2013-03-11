#pragma once

#include "ChainPolicy.hpp"
#include "Worker.hpp"
#include "CharInput.hpp"
#include "LineInput.hpp"
#include "StreamOutput.hpp"
#include "Queue.hpp"
#include "LookForPrompt.hpp"
#include "ActivityLog.hpp"
#include "UserCmdParser.hpp"
#include "UserCmdWriter.hpp"
#include "GdbResponseParser.hpp"
#include "GdbResponseWriter.hpp"
#include "LogChannel.hpp"
#include "LogChannelWithPrompt.hpp"
#include "RecombinePrompt.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T> ChainPolicy::None get(ChainPolicy, AbstractInput<T> const&);
template <typename T> ChainPolicy::None get(ChainPolicy, AbstractOutput<T> const&);
template <typename T> ChainPolicy::RHS  get(ChainPolicy, AbstractAdapter<T> const&);
ChainPolicy::Both get(ChainPolicy, Worker const&);
template <typename T> ChainPolicy::None get(ChainPolicy, Queue<T> const&);
ChainPolicy::RHS get(ChainPolicy, LogChannel const&);
ChainPolicy::RHS get(ChainPolicy, LogChannelWithPrompt const&);
ChainPolicy::RHS get(ChainPolicy, ActivityLog const&);

    }
}
