// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btQuaternion(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btQuaternion)
    LM_CONSTR(btQuaternion,,)
    LM_CONSTR(btQuaternion,, const btVector3 &, const btScalar &)
    LM_CONSTR(btQuaternion,, const btScalar &, const btScalar &, const btScalar &)
    LM_CONSTR(btQuaternion,, btScalar const&, btScalar const&, btScalar const&, btScalar const&)
    LM_STATIC_FUNC_OVERLOAD(ns_bullet, btQuaternion, "getIdentityQuaternion", getIdentity, btQuaternion const&)

    LM_FUNC(btQuaternion, (angle)(dot)(farthest)(getAngle)(getAxis)(getW)(inverse)(length)(length2)(nearest)(normalize)(normalized)
            (setEuler)(setEulerZYX)(setRotation)(slerp))

}

}}

