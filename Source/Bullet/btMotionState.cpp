// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btMotionState()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btMotionState)
    LM_FUNC(btMotionState, (getWorldTransform)(setWorldTransform))
    LM_CLASS(ns_bullet, btDefaultMotionState)
    LM_BASE(btDefaultMotionState, btMotionState)
    LM_CONSTR(btDefaultMotionState, "new", btTransform const&, btTransform const&)
}

}}

