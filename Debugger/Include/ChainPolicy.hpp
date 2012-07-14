#pragma once

#include "TypePolicy.hpp"

namespace Iocaste {
    namespace Debugger {

struct ChainPolicy
{
    struct None {};
    struct RHS {};
    struct Both {};
};

template <typename T>
struct GetChainPolicy
{
    static_assert(sizeof(T) && false, "No chain policy defined for type T.");
};

    }
}
