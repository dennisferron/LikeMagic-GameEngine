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
UndefinedPolicy<ChainPolicy, T> get(ChainPolicy, T const&);

template <typename T>
struct ChainPolicyGetter : public PolicyGetter<ChainPolicy, T>
{
};

    }
}
