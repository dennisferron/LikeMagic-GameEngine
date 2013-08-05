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

void add_bindings_btBroadphaseInterface(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btBroadphaseInterface)
    LM_CLASS_NO_COPY(ns_bullet, btDbvtBroadphase)
    LM_BASE(btDbvtBroadphase, btBroadphaseInterface)
    LM_CONSTR(btDbvtBroadphase,,)

}

}}

