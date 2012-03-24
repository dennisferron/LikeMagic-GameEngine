// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

#include "LikeMagic/Utility/UserMacros.hpp"
#include "Bindings/Bullet/ScriptedClosestRayResultCallback.hpp"
#include "Bindings/Bullet/ScriptedContactResultCallback.hpp"
#include "Bindings/Bullet/ScriptedWorldManager.hpp"

using namespace LikeMagic;
using namespace Iocaste::LikeMagicAdapters;

namespace Bindings { namespace Bullet {

void add_bindings_btCollisionWorld(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btCollisionWorld)
    LM_FUNC(btCollisionWorld, (rayTest)(contactTest))

    LM_CLASS(ns_bullet, btDynamicsWorld)
    LM_BASE(btDynamicsWorld, btCollisionWorld)

    LM_FUNC_OVERLOAD(btDynamicsWorld, "addRigidBody", addRigidBody, void, btRigidBody*)
    LM_FUNC_OVERLOAD(btDynamicsWorld, "addRigidBody", addRigidBody, void, btRigidBody*, short, short)

    LM_FUNC(btDynamicsWorld, (debugDrawWorld))
    LM_FUNC(btDynamicsWorld, (addConstraint))
    LM_FUNC(btDynamicsWorld, (removeConstraint)(addAction)(removeAction))
    LM_FUNC(btDynamicsWorld, (setGravity)(getGravity)(addCharacter)(addVehicle)(clearForces)(getConstraintSolver)(getNumConstraints))
    LM_FUNC(btDynamicsWorld, (getSolverInfo)(getWorldType)(removeCharacter)(removeRigidBody)(removeVehicle)(setConstraintSolver))
    LM_FUNC(btDynamicsWorld, (setInternalTickCallback)(setWorldUserInfo)(stepSimulation)(synchronizeMotionStates))

    LM_CLASS(ns_bullet, btDiscreteDynamicsWorld)
    LM_BASE(btDiscreteDynamicsWorld, btDynamicsWorld)
    LM_CONSTR(btDiscreteDynamicsWorld,, btDispatcher*, btBroadphaseInterface*, btConstraintSolver*, btCollisionConfiguration*)
    LM_FUNC(btDiscreteDynamicsWorld, (setGravity)(setDebugDrawer)(getDebugDrawer)(debugDrawWorld))

    LM_FUNC_OVERLOAD(btDiscreteDynamicsWorld, "addRigidBody", addRigidBody, void, btRigidBody*, short, short)

    LM_CLASS(ns_bullet, btSoftRigidDynamicsWorld)
    LM_BASE(btSoftRigidDynamicsWorld, btDiscreteDynamicsWorld)
    LM_CONSTR(btSoftRigidDynamicsWorld,, btDispatcher*, btBroadphaseInterface*, btConstraintSolver*, btCollisionConfiguration*)
    LM_FUNC(btSoftRigidDynamicsWorld, (addSoftBody)(removeSoftBody)(getDrawFlags)(setDrawFlags))
    LM_STATIC_MEMBER_FUNC(btSoftRigidDynamicsWorld, (rayTestSingle))

    LM_FUNC_OVERLOAD_BOTH(btSoftRigidDynamicsWorld, getWorldInfo, btSoftBodyWorldInfo&)
    LM_FUNC_OVERLOAD_BOTH(btSoftRigidDynamicsWorld, getSoftBodyArray, btSoftBodyArray&)

    LM_CLASS(ns_bullet, btIDebugDraw)
    LM_FUNC(btIDebugDraw, (setDebugMode)(getDebugMode))

    typedef btIDebugDraw::DebugDrawModes DebugDrawModes;
    LM_CLASS(ns_bullet, DebugDrawModes)
    ns_bullet.get_type_system().add_conv<DebugDrawModes, int, LikeMagic::TypeConv::NumberConv>();

    typedef btCollisionWorld::RayResultCallback btCollisionWorld_RayResultCallback;
    LM_CLASS(ns_bullet, btCollisionWorld_RayResultCallback)
    LM_FUNC(btCollisionWorld_RayResultCallback, (addSingleResult)(hasHit)(needsCollision))
    LM_FIELD(btCollisionWorld_RayResultCallback, (m_closestHitFraction)(m_collisionObject)
             (m_collisionFilterGroup)(m_collisionFilterMask)(m_flags))

    typedef btCollisionWorld::ClosestRayResultCallback btCollisionWorld_ClosestRayResultCallback;
    LM_CLASS(ns_bullet, btCollisionWorld_ClosestRayResultCallback)
    LM_BASE(btCollisionWorld_ClosestRayResultCallback, btCollisionWorld_RayResultCallback)
    LM_FIELD(btCollisionWorld_ClosestRayResultCallback, (m_rayFromWorld)(m_rayToWorld)(m_hitNormalWorld)(m_hitPointWorld))

    LM_CLASS(ns_bullet, ScriptedClosestRayResultCallback)
    LM_BASE(ScriptedClosestRayResultCallback, btCollisionWorld_ClosestRayResultCallback)
    LM_CONSTR(ScriptedClosestRayResultCallback,, IoBlock)
    LM_FUNC(ScriptedClosestRayResultCallback, (baseAddSingleResult)(test_equals))

    typedef btCollisionWorld::LocalRayResult btCollisionWorld_LocalRayResult;
    LM_CLASS(ns_bullet, btCollisionWorld_LocalRayResult)
    LM_FIELD(btCollisionWorld_LocalRayResult, (m_collisionObject)(m_localShapeInfo)(m_hitNormalLocal)(m_hitFraction))

    typedef btCollisionWorld::LocalShapeInfo btCollisionWorld_LocalShapeInfo;
    LM_CLASS(ns_bullet, btCollisionWorld_LocalShapeInfo)
    LM_FIELD(btCollisionWorld_LocalShapeInfo, (m_shapePart)(m_triangleIndex))

    typedef btCollisionWorld::ContactResultCallback btCollisionWorld_ContactResultCallback;
    LM_CLASS(ns_bullet, btCollisionWorld_ContactResultCallback)
    LM_FIELD(btCollisionWorld_ContactResultCallback, (m_collisionFilterGroup)(m_collisionFilterMask))
    LM_FUNC(btCollisionWorld_ContactResultCallback, (needsCollision)(addSingleResult))

    LM_CLASS(ns_bullet, ScriptedContactResultCallback)
    LM_BASE(ScriptedContactResultCallback, btCollisionWorld_ContactResultCallback)
    LM_CONSTR(ScriptedContactResultCallback,, IoBlock, IoBlock)
    LM_FUNC(ScriptedContactResultCallback, (baseNeedsCollision))

    LM_CLASS(ns_bullet, btManifoldPoint)
    LM_CONSTR(btManifoldPoint,,)
    LM_CONSTR(btManifoldPoint,, const btVector3 &, const btVector3 &, const btVector3 &, btScalar)
    LM_FUNC(btManifoldPoint, (getDistance)(getLifeTime)(getPositionWorldOnA)(getPositionWorldOnB)(setDistance))
    LM_FIELD(btManifoldPoint, (m_appliedImpulse)(m_appliedImpulseLateral1)(m_appliedImpulseLateral2)(m_combinedFriction)
             (m_combinedRestitution)(m_contactCFM1)(m_contactCFM2)(m_contactMotion1)(m_contactMotion2)(m_distance1)
             (m_index0)(m_index1)(m_lateralFrictionDir1)(m_lateralFrictionDir2)(m_lateralFrictionInitialized)(m_lifeTime)
             (m_localPointA)(m_localPointB)(m_normalWorldOnB)(m_partId0)(m_partId1)(m_positionWorldOnA)(m_positionWorldOnB)
             (m_userPersistentData))

    LM_CLASS(ns_bullet, ScriptedWorldManager)
    LM_CONSTR(ScriptedWorldManager,,)
    LM_FUNC(ScriptedWorldManager, (setOnTick)(setOnPreTick))
}

}}

