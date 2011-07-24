// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Generators/MethodCallGenerator.hpp"
#include "LikeMagic/Generators/DeferredCallGenerator.hpp"
#include "LikeMagic/Generators/DelegateCallGenerator.hpp"

namespace LikeMagic { namespace Generators {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <MemberKind K, typename R, typename ObjT, typename... Args>
struct GeneratorFactory
{
    typedef typename MemberPointer<K, R, ObjT, Args...>::type F;
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        #ifdef USE_DELEGATES_HACK
            return new DelegateCallGenerator<K, R, Args...>(ref_type_, const_ref_type_, func_ptr_, type_system_);
        #else
            return new MethodCallGenerator<K, R, ObjT, Args...>(ref_type_, const_ref_type_, func_ptr_, type_system_);
        #endif
    }
};

template <typename R, typename... Args>
struct GeneratorFactory<MemberKind::static_method, R, StaticMethod, Args...>
{
    typedef R (*F)(Args...);
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        return new MethodCallGenerator<MemberKind::static_method, R, StaticMethod, Args...>(ref_type_, const_ref_type_, func_ptr_, type_system_);
    }
};

template <typename R, typename... Args>
struct GeneratorFactory<MemberKind::nonmember_op, R, StaticMethod, Args...>
{
    typedef R (*F)(Args...);
    static AbstractCallTargetSelector* create(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
    {
        return new MethodCallGenerator<MemberKind::static_method, R, StaticMethod, Args...>(ref_type_, const_ref_type_, func_ptr_, type_system_);
    }
};


}}
