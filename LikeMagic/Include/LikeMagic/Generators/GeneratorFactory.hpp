// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
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
using namespace LikeMagic::SFMO;
using namespace LikeMagic::CallTargets;

template <MemberKind K, typename R, typename ObjT, typename... Args>
struct GeneratorFactory
{
    typedef typename MemberPointer<K, R, ObjT, Args...>::type F;
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        typedef typename MemberPointer<K, R, AbstractDelegate, Args...>::type F_cast;
        return new DelegateCallTarget<K, R, Args...>(ref_type_, const_ref_type_, reinterpret_cast<F_cast>(func_ptr_), type_system_);
    }
};

template <typename R, typename... Args>
struct GeneratorFactory<MemberKind::static_method, R, StaticMethod, Args...>
{
    typedef R (*F)(Args...);
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        return new StaticMethodCallTarget<R, Args...>(func_ptr_, type_system_);
    }
};

template <typename R, typename FirstArg, typename... Args>
struct GeneratorFactory<MemberKind::nonmember_op, R, StaticMethod, FirstArg, Args...>
{
    typedef R (*F)(FirstArg, Args...);
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        return new ExtensionMethodCallTarget<R, FirstArg, Args...>(func_ptr_, type_system_);
    }
};


}}
