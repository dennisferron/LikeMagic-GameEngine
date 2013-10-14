// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Bullet/Bindings.hpp"
#include "Bindings/Bullet/AddValues.hpp"

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btBroadphaseProxy();
void add_bindings_btBroadphaseInterface();
void add_bindings_btCollisionConfiguration();
void add_bindings_btCollisionObject();
void add_bindings_btCollisionShape();
void add_bindings_btCollisionWorld();
void add_bindings_btConcaveShape();
void add_bindings_btConstraintSolver();
void add_bindings_btDispatcher();
void add_bindings_btMatrix3x3();
void add_bindings_btMotionState();
void add_bindings_btQuaternion();
void add_bindings_btSoftBody();
void add_bindings_btStridingMeshInterface();
void add_bindings_btTransform();
void add_bindings_btTypedConstraint();
void add_bindings_btVector3();

BULLET_BINDINGS_API void add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bindings = register_namespace("Bindings", global_ns);
    TypeMirror& ns_bullet_bindings = register_namespace("Bullet", ns_bindings);

    Bindings::Bullet::add_bindings_btBroadphaseProxy();
    Bindings::Bullet::add_bindings_btBroadphaseInterface();
    Bindings::Bullet::add_bindings_btCollisionConfiguration();
    Bindings::Bullet::add_bindings_btCollisionObject();
    Bindings::Bullet::add_bindings_btCollisionShape();
    Bindings::Bullet::add_bindings_btCollisionWorld();
    Bindings::Bullet::add_bindings_btConcaveShape();
    Bindings::Bullet::add_bindings_btConstraintSolver();
    Bindings::Bullet::add_bindings_btDispatcher();
    Bindings::Bullet::add_bindings_btMatrix3x3();
    Bindings::Bullet::add_bindings_btMotionState();
    Bindings::Bullet::add_bindings_btQuaternion();
    Bindings::Bullet::add_bindings_btSoftBody();
    Bindings::Bullet::add_bindings_btStridingMeshInterface();
    Bindings::Bullet::add_bindings_btTransform();
    Bindings::Bullet::add_bindings_btTypedConstraint();
    Bindings::Bullet::add_bindings_btVector3();

    LM_STATIC_FUNC_NAME(ns_bullet_bindings, "add_values", Bindings::Bullet::add_values)
}

}}
