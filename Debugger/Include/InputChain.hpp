#pragma once

#include "StaticFuture.hpp"
#include "ChainBuilder.hpp"

namespace Iocaste {
    namespace Debugger {

    struct InputChain : BeginFuture<ChainPolicyGetter>
    {
    };


    }
}
