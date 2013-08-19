// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btTransform()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btTransform)
    LM_CONSTR(btTransform,"new")
    LM_CONSTR(btTransform, "new", btTransform const&)
    LM_CONSTR(btTransform, "new", btQuaternion const&, btVector3 const&)
    LM_STATIC_FUNC_OVERLOAD(btTransform_LM, "getIdentityTransform", btTransform::getIdentity, btTransform const&)
    LM_FUNC(btTransform, (getOpenGLMatrix)(getRotation)(inverse)(inverseTimes)(invXform)(mult)(serialize)
            (serializeFloat)(setBasis)(setFromOpenGLMatrix)(setIdentity)(setOrigin)(setRotation))

    LM_FUNC_OVERLOAD_BOTH(btTransform, getBasis, btMatrix3x3&)
    LM_FUNC_OVERLOAD_BOTH(btTransform, getOrigin, btVector3&)

}

}}

