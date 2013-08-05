// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Bullet/Bindings.hpp"
#include "Bindings/Bullet/Protos.hpp"

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btBroadphaseProxy(Namespace const& ns_bullet);
void add_bindings_btBroadphaseInterface(Namespace const& ns_bullet);
void add_bindings_btCollisionConfiguration(Namespace const& ns_bullet);
void add_bindings_btCollisionObject(Namespace const& ns_bullet);
void add_bindings_btCollisionShape(Namespace const& ns_bullet);
void add_bindings_btCollisionWorld(Namespace const& ns_bullet);
void add_bindings_btConcaveShape(Namespace const& ns_bullet);
void add_bindings_btConstraintSolver(Namespace const& ns_bullet);
void add_bindings_btDispatcher(Namespace const& ns_bullet);
void add_bindings_btMatrix3x3(Namespace const& ns_bullet);
void add_bindings_btMotionState(Namespace const& ns_bullet);
void add_bindings_btQuaternion(Namespace const& ns_bullet);
void add_bindings_btSoftBody(Namespace const& ns_bullet);
void add_bindings_btStridingMeshInterface(Namespace const& ns_bullet);
void add_bindings_btTransform(Namespace const& ns_bullet);
void add_bindings_btTypedConstraint(Namespace const& ns_bullet);
void add_bindings_btVector3(Namespace const& ns_bullet);

DLL_PUBLIC void add_bindings(Namespace const& ns_bullet_bindings)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(ns_bullet_bindings)

    //auto ns_bullet = Namespace::global(ns_bullet).subspace("Bindings").subspace("Bullet");

    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btBroadphaseProxy)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btBroadphaseInterface)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btCollisionConfiguration)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btCollisionObject)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btCollisionShape)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btCollisionWorld)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btConcaveShape)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btConstraintSolver)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btDispatcher)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btMatrix3x3)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btMotionState)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btQuaternion)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btSoftBody)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btStridingMeshInterface)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btTransform)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btTypedConstraint)
    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_bindings_btVector3)

    LM_STATIC_FUNC(ns_bullet_bindings, Bindings::Bullet, add_protos)
}

}}
