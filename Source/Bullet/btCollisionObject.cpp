// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btCollisionObject()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    typedef btRigidBody::btRigidBodyConstructionInfo btRigidBodyConstructionInfo;
    LM_CLASS(ns_bullet, btRigidBodyConstructionInfo)
    LM_CONSTR(btRigidBodyConstructionInfo, "new", btScalar, btMotionState *, btCollisionShape *, btVector3 const&)
    LM_FIELD(btRigidBodyConstructionInfo, (m_mass)(m_motionState)(m_startWorldTransform)(m_collisionShape)
             (m_localInertia)(m_linearDamping)(m_angularDamping)(m_friction)(m_restitution)(m_linearSleepingThreshold)
             (m_angularSleepingThreshold)(m_additionalDamping)(m_additionalDampingFactor)(m_additionalLinearDampingThresholdSqr)
             (m_additionalAngularDampingThresholdSqr)(m_additionalAngularDampingFactor)
    )

    LM_CLASS(ns_bullet, btCollisionObject)
    LM_FUNC(btCollisionObject,
            (activate)(calculateSerializeBufferSize)(checkCollideWith)(forceActivationState)
            (getActivationState)(getCcdMotionThreshold)(getCcdSquareMotionThreshold)
            (getCcdSweptSphereRadius)(getCollisionFlags)(getCompanionId)(getContactProcessingThreshold)(getDeactivationTime)(getFriction)
            (getHitFraction)(getInterpolationAngularVelocity)(getInterpolationLinearVelocity)(getIslandTag)(getRestitution)(getUserPointer)
            (hasAnisotropicFriction)(hasContactResponse)(isActive)(isKinematicObject)(isStaticObject)(isStaticOrKinematicObject)(mergesSimulationIslands)
            (serialize)(setActivationState)(setAnisotropicFriction)(setBroadphaseHandle)(setCcdMotionThreshold)(setCcdSweptSphereRadius)(setCollisionFlags)
            (setCollisionShape)(setCompanionId)(setContactProcessingThreshold)(setDeactivationTime)(setFriction)(setHitFraction)(setInterpolationAngularVelocity)
            (setInterpolationLinearVelocity)(setInterpolationWorldTransform)(setIslandTag)(setRestitution)(setUserPointer)(setWorldTransform)
    )

    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getBroadphaseHandle, btBroadphaseProxy*)
    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getCollisionShape, btCollisionShape*)
    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getInterpolationWorldTransform, btTransform&)
    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getWorldTransform, btTransform&)


    LM_CLASS(ns_bullet, btRigidBody)
    LM_BASE(btRigidBody, btCollisionObject)
    LM_CONSTR(btRigidBody, "new", btRigidBodyConstructionInfo const&)

    LM_FUNC_OVERLOAD_BOTH(btRigidBody, getMotionState, btMotionState*)
    LM_FUNC_OVERLOAD_BOTH(btRigidBody, getBroadphaseProxy, btBroadphaseProxy*)

    LM_FUNC_OVERLOAD(btRigidBody, "setAngularFactorScalar", setAngularFactor, void, btScalar)
    LM_FUNC_OVERLOAD(btRigidBody, "setAngularFactor", setAngularFactor, void, btVector3 const&)

    LM_FUNC(btRigidBody, (addConstraintRef)(applyCentralForce)(applyCentralImpulse)(applyDamping)(applyForce)(applyGravity)(applyImpulse)(applyTorque)(applyTorqueImpulse)
            (calculateSerializeBufferSize)(checkCollideWithOverride)(clearForces)(computeAngularImpulseDenominator)(computeImpulseDenominator)(getAabb)(getAngularDamping)
            (getAngularFactor)(getAngularSleepingThreshold)(getAngularVelocity)(getCenterOfMassPosition)(getCenterOfMassTransform)(getConstraintRef)(getFlags)(getGravity)
            (getInvInertiaDiagLocal)(getInvInertiaTensorWorld)(getInvMass)(getLinearDamping)(getLinearFactor)(getLinearSleepingThreshold)(getLinearVelocity)(getNumConstraintRefs)
            (getOrientation)(getTotalForce)(getTotalTorque)(getVelocityInLocalPoint)(isInWorld)(predictIntegratedTransform)(proceedToTransform)(removeConstraintRef)(saveKinematicState)
            (serialize)(setAngularVelocity)(setCenterOfMassTransform)(setDamping)(setFlags)(setGravity)(setInvInertiaDiagLocal)(setLinearFactor)
            (setLinearVelocity)(setMassProps)(setMotionState)(setNewBroadphaseProxy)(setSleepingThresholds)(translate)(updateDeactivation)(updateInertiaTensor)
            (wantsSleeping))


    LM_CLASS(ns_bullet, btGhostObject)
    LM_BASE(btGhostObject, btCollisionObject)
    LM_CONSTR(btGhostObject,"new")
    LM_FUNC(btGhostObject, (convexSweepTest)(getNumOverlappingObjects)(rayTest))

    LM_FUNC_OVERLOAD_BOTH(btGhostObject, getOverlappingObject, btCollisionObject*, int)

    LM_CLASS(ns_bullet, btPairCachingGhostObject)
    LM_BASE(btPairCachingGhostObject, btGhostObject)
    LM_CONSTR(btPairCachingGhostObject,"new")
    LM_FUNC(btPairCachingGhostObject, (getOverlappingPairCache))
}

}}

