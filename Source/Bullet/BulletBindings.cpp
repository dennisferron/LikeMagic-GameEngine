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

#include "LikeMagic/BindingMacros.hpp"

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

void add_bindings()
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

    Bindings::Bullet::add_protos();
}

}}
