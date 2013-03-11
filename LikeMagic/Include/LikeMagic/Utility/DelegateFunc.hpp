// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic { namespace Utility {

// A dummy type used to abstract away the type of the target object for a member function pointer.
struct AbstractDelegate {};

template <bool is_const, bool is_static, typename R, typename... Args>
struct DelegateFunc
{
    // All valid combinations for DelegateFunc are in the specializations.
    static_assert(sizeof...(Args) || true, "Invalid template arguments to DelegateFunc.");
};

// Nonconst member function.
template <typename R, typename... Args>
struct DelegateFunc<false, false, R, Args...>
{
    typedef R (AbstractDelegate::*PtrT)(Args...);
};

// Const member function.
template <typename R, typename... Args>
struct DelegateFunc<true, false, R, Args...>
{
    typedef R (AbstractDelegate::*PtrT)(Args...) const;
};

// Static function.
template <typename R, typename... Args>
struct DelegateFunc<false, true, R, Args...>
{
    typedef R (*PtrT)(Args...);
};

}}
