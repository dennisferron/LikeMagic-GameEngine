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

void add_bindings_btQuaternion()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btQuaternion)
    LM_CONSTR(btQuaternion,"new")
    LM_CONSTR(btQuaternion, "new", const btVector3 &, const btScalar &)
    LM_CONSTR(btQuaternion, "new", const btScalar &, const btScalar &, const btScalar &)
    LM_CONSTR(btQuaternion, "new", btScalar const&, btScalar const&, btScalar const&, btScalar const&)
    LM_STATIC_FUNC_OVERLOAD(btQuaternion_LM, "getIdentityQuaternion", btQuaternion::getIdentity, btQuaternion const&)

    LM_FUNC(btQuaternion, (angle)(dot)(farthest)(getAngle)(getAxis)(getW)(inverse)(length)(length2)(nearest)(normalize)(normalized)
            (setEuler)(setEulerZYX)(setRotation)(slerp))

}

}}

