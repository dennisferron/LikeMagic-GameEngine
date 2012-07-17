#pragma once

#include "ChainPolicy.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T> class AbstractOutput;

template <typename T>
AbstractOutput<T>& no_call_copy_constructor(AbstractOutput<T>& t)
    { return t; }

class LogChannel;
AbstractOutput<std::string>& no_call_copy_constructor(LogChannel& value);

class ActivityLog;
AbstractOutput<std::string>& no_call_copy_constructor(ActivityLog& value);

template <typename T, typename LHS, typename RHS, typename Policy>
struct ChainBuilder
{
    template <typename... Args>
    static T* create(LHS& lhs, RHS& rhs, Args&&...)
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
    template <typename... Args>
    static T* create(LHS& lhs, RHS& rhs, Args&&... args)
        { return new T(std::forward<Args>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::RHS>
{
    template <typename... Args>
    static T* create(LHS& lhs, RHS& rhs, Args&&... args)
        { return new T(no_call_copy_constructor(rhs), std::forward<Args>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS&, ChainPolicy::Both>
{
    template <typename... Args>
    static T* create(LHS& lhs, RHS& rhs, Args&&... args)
        { return new T(lhs.complete().tail(), rhs, std::forward<Args>(args)...); }
};

    }
}
