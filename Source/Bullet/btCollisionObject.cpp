// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletSoftBody/btSoftBody.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btCollisionObject(Namespace const& ns_bullet)
{
    typedef btRigidBody::btRigidBodyConstructionInfo btRigidBodyConstructionInfo;
    LM_CLASS(ns_bullet, btRigidBodyConstructionInfo)
    LM_CONSTR(btRigidBodyConstructionInfo,, btScalar, btMotionState *, btCollisionShape *, btVector3 const&)
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
    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getRootCollisionShape, btCollisionShape*)
    LM_FUNC_OVERLOAD_BOTH(btCollisionObject, getWorldTransform, btTransform&)


    LM_CLASS(ns_bullet, btRigidBody)
    LM_BASE(btRigidBody, btCollisionObject)
    LM_CONSTR(btRigidBody,, btRigidBodyConstructionInfo const&)

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
    LM_CONSTR(btGhostObject,,)
    LM_FUNC(btGhostObject, (convexSweepTest)(getNumOverlappingObjects)(rayTest))

    LM_FUNC_OVERLOAD_BOTH(btGhostObject, getOverlappingObject, btCollisionObject*, int)

    LM_CLASS(ns_bullet, btPairCachingGhostObject)
    LM_BASE(btPairCachingGhostObject, btGhostObject)
    LM_CONSTR(btPairCachingGhostObject,,)
    LM_FUNC(btPairCachingGhostObject, (getOverlappingPairCache))

    LM_CLASS_NO_COPY(ns_bullet, btSoftBody)
    LM_BASE(btSoftBody, btCollisionObject)
    LM_CONSTR(btSoftBody,, btSoftBodyWorldInfo*, int, const btVector3*, const btScalar*)

    // btSoftBody class has lots of functions; most of them overloaded.  I'll add them later.
    // Also has lots of fields.

    LM_CLASS(ns_bullet, btSoftBodyHelpers)
    LM_STATIC_MEMBER_FUNC(btSoftBodyHelpers,
        (Draw)
        (DrawInfos)
        (DrawNodeTree)
        (DrawFaceTree)
        (DrawClusterTree)
        (DrawFrame)
        (CreateRope)
        (CreatePatch)
        (CreatePatchUV)
        (CalculateUV)
        (CreateEllipsoid)
        (CreateFromTriMesh)
        (CreateFromConvexHull)
        (CreateFromTetGenData)
    )

}

}}

