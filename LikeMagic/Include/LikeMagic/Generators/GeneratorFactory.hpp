// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/CallTargets/StaticMethodCallTarget.hpp"
#include "LikeMagic/CallTargets/ExtensionMethodCallTarget.hpp"
#include "LikeMagic/CallTargets/DelegateCallTarget.hpp"

namespace LikeMagic { namespace Generators {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::CallTargets;

template <MemberKind K, typename R, typename ObjT, typename... Args>
struct GeneratorFactory
{
    typedef typename MemberPointer<K, R, ObjT, Args...>::type F;
    static CallTarget* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_)
    {
        typedef typename MemberPointer<K, R, AbstractDelegate, Args...>::type F_cast;
        return new DelegateCallTarget<K, R, Args...>(ref_type_, const_ref_type_, reinterpret_cast<F_cast>(func_ptr_));
    }
};

template <typename R, typename... Args>
struct GeneratorFactory<MemberKind::static_method, R, StaticMethod, Args...>
{
    typedef R (*F)(Args...);
    static CallTarget* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_)
    {
        return new StaticMethodCallTarget<R, Args...>(func_ptr_);
    }
};

template <typename R, typename FirstArg, typename... Args>
struct GeneratorFactory<MemberKind::nonmember_op, R, StaticMethod, FirstArg, Args...>
{
    typedef R (*F)(FirstArg, Args...);
    static CallTarget* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_)
    {
        return new ExtensionMethodCallTarget<R, FirstArg, Args...>(func_ptr_);
    }
};


}}
