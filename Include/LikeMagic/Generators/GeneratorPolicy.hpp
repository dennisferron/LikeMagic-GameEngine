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

template <MemberKind FMod, typename R, typename ObjT, typename... Args>
struct GeneratorPolicy
{
    //typedef DeferredCallGenerator<FMod, R, Args...> type;
#ifdef USE_DELEGATES_HACK
    typedef DelegateCallGenerator<FMod, R, Args...> type;
#else
    typedef MethodCallGenerator<FMod, R, ObjT, Args...> type;
#endif
};

template <typename R, typename... Args>
struct GeneratorPolicy<MemberKind::static_method, R, StaticMethod, Args...>
{
    typedef MethodCallGenerator<MemberKind::static_method, R, StaticMethod, Args...> type;
};


}}
