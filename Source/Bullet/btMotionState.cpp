// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btMotionState(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btMotionState)
    LM_FUNC(btMotionState, (getWorldTransform)(setWorldTransform))
    LM_CLASS(ns_bullet, btDefaultMotionState)
    LM_BASE(btDefaultMotionState, btMotionState)
    LM_CONSTR(btDefaultMotionState,, btTransform const&, btTransform const&)
}

}}

