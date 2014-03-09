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

void add_bindings_btBroadphaseInterface()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btBroadphaseInterface)
    LM_CLASS(ns_bullet, btDbvtBroadphase)
    LM_BASE(btDbvtBroadphase, btBroadphaseInterface)
    LM_CONSTR(btDbvtBroadphase,"new")
}

}}

