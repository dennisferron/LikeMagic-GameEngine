#pragma once

#include "ChainPolicy.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T, typename LHS, typename RHS, typename Policy>
struct ChainBuilder
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
    {
        static_assert(
            sizeof(T) && false, "Unrecognized chaining policy."
        );
        throw 0;
    }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::None>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(std::get<Indices>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::RHS>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(rhs, std::get<Indices>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::Both>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(*lhs.force().second, rhs, std::get<Indices>(args)...); }
};

    }
}
