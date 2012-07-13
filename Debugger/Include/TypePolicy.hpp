#pragma once

#include "LikeMagic/Utility/IndexPack.hpp"

namespace Iocaste {
    namespace Debugger {

using LikeMagic::Utility::IndexPack;
using LikeMagic::Utility::MakeIndexPack;

struct UnusedType {};

template <typename Policy, typename T>
struct UndefinedPolicy
{
    static_assert(sizeof(T) && false, "This policy is undefined for this type.");
};

template <typename Policy, typename T>
struct PolicyGetter
{
    typedef decltype(get(Policy(), *(T*)0)) type;
};

    }
}
