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

void add_bindings_btTransform(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btTransform)
    LM_CONSTR(btTransform,,)
    LM_CONSTR(btTransform,, btTransform const&)
    LM_CONSTR(btTransform,, btQuaternion const&, btVector3 const&)
    LM_STATIC_FUNC_OVERLOAD(ns_bullet, btTransform, "getIdentityTransform", getIdentity, btTransform const&)
    LM_FUNC(btTransform, (getOpenGLMatrix)(getRotation)(inverse)(inverseTimes)(invXform)(mult)(serialize)
            (serializeFloat)(setBasis)(setFromOpenGLMatrix)(setIdentity)(setOrigin)(setRotation))

    LM_FUNC_OVERLOAD_BOTH(btTransform, getBasis, btMatrix3x3&)
    LM_FUNC_OVERLOAD_BOTH(btTransform, getOrigin, btVector3&)

}

}}

