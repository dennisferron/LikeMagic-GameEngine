// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btTypedConstraint(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btTypedObject)
    LM_CLASS(ns_bullet, btTypedConstraint)
    LM_BASE(btTypedConstraint, btTypedObject)
    LM_FUNC(btTypedConstraint, (buildJacobian)(calculateSerializeBufferSize)(enableFeedback)(getAppliedImpulse)(getConstraintType)
            (getDbgDrawSize)(getParam)(getUid)(getUserConstraintId)(getUserConstraintType)(needsFeedback)
            (serialize)(setDbgDrawSize)(setParam)(setUserConstraintId)(setUserConstraintType)(solveConstraintObsolete)
    )

    LM_FUNC_OVERLOAD_BOTH(btTypedConstraint, getRigidBodyA, btRigidBody&)
    LM_FUNC_OVERLOAD_BOTH(btTypedConstraint, getRigidBodyB, btRigidBody&)

    LM_CLASS(ns_bullet, btHingeConstraint)
    LM_BASE(btHingeConstraint, btTypedConstraint)
    LM_CONSTR(btHingeConstraint,,
        btRigidBody &, btRigidBody &,
        const btVector3 &, const btVector3 &,
        btVector3 &, btVector3 &,
        bool)
    LM_CONSTR(btHingeConstraint,,
        btRigidBody &,
        const btVector3 &,
        btVector3 &,
        bool)
    LM_CONSTR(btHingeConstraint,,
        btRigidBody &, btRigidBody &,
        const btTransform &, const btTransform &,
        bool)
    LM_CONSTR(btHingeConstraint,,
        btRigidBody &,
        const btTransform &,
        bool)

    LM_FUNC(btHingeConstraint, (calculateSerializeBufferSize)(enableAngularMotor)(enableMotor)(getAngularOnly)(getEnableAngularMotor)(getLimitSign)(getLowerLimit)(getMaxMotorImpulse)(getMotorTargetVelosity)
            (getParam)(getSolveLimit)(getUpperLimit)(getUseFrameOffset)(serialize)(setAngularOnly)(setAxis)(setLimit)(setMaxMotorImpulse)(setParam)(setUseFrameOffset)(testLimit)(updateRHS))

    LM_FUNC_OVERLOAD_BOTH(btHingeConstraint, getAFrame, btTransform&)
    LM_FUNC_OVERLOAD_BOTH(btHingeConstraint, getBFrame, btTransform&)

    LM_FUNC_OVERLOAD(btHingeConstraint, "setMotorTargetScalarScalar", setMotorTarget, void, btScalar, btScalar)
    LM_FUNC_OVERLOAD(btHingeConstraint, "setMotorTargetQuatScalar", setMotorTarget, void, const btQuaternion &, btScalar)


    LM_FUNC_OVERLOAD(btHingeConstraint, "getHingeAngle", getHingeAngle, btScalar, const btTransform &, const btTransform &)
    LM_FUNC_OVERLOAD(btHingeConstraint, "getHingeAngle", getHingeAngle, btScalar)



    LM_CLASS(ns_bullet, btSliderConstraint)
    LM_BASE(btSliderConstraint, btTypedConstraint)
    LM_CONSTR(btSliderConstraint,,
        btRigidBody &, btRigidBody &,
        const btTransform &, const btTransform &,
        bool)
    LM_CONSTR(btSliderConstraint,,
        btRigidBody &,
        const btTransform &,
        bool)

    LM_FUNC(btSliderConstraint, (calculateSerializeBufferSize)(calculateTransforms)
            (getAncorInA)(getAncorInB)(getAngDepth)(getCalculatedTransformA)(getCalculatedTransformB)(getDampingDirAng)(getDampingDirLin)(getDampingLimAng)
            (getDampingLimLin)(getDampingOrthoAng)(getDampingOrthoLin)(getLinDepth)(getLinearPos)(getLowerAngLimit)(getLowerLinLimit)(getMaxAngMotorForce)(getMaxLinMotorForce)(getParam)(getPoweredAngMotor)(getPoweredLinMotor)
            (getRestitutionDirAng)(getRestitutionDirLin)(getRestitutionLimAng)(getRestitutionLimLin)(getRestitutionOrthoAng)(getRestitutionOrthoLin)(getRigidBodyA)(getRigidBodyB)(getSoftnessDirAng)(getSoftnessDirLin)
            (getSoftnessLimAng)(getSoftnessLimLin)(getSoftnessOrthoAng)(getSoftnessOrthoLin)(getSolveAngLimit)(getSolveLinLimit)(getTargetAngMotorVelocity)(getTargetLinMotorVelocity)(getUpperAngLimit)(getUpperLinLimit)
            (getUseFrameOffset)(getUseLinearReferenceFrameA)
            (serialize)
            (setDampingDirAng)(setDampingDirLin)(setDampingLimAng)
            (setDampingLimLin)(setDampingOrthoAng)(setDampingOrthoLin)(setLowerAngLimit)(setLowerLinLimit)(setMaxAngMotorForce)(setMaxLinMotorForce)(setParam)(setPoweredAngMotor)(setPoweredLinMotor)
            (setRestitutionDirAng)(setRestitutionDirLin)(setRestitutionLimAng)(setRestitutionLimLin)(setRestitutionOrthoAng)(setRestitutionOrthoLin)(setSoftnessDirAng)(setSoftnessDirLin)
            (setSoftnessLimAng)(setSoftnessLimLin)(setSoftnessOrthoAng)(setSoftnessOrthoLin)(setTargetAngMotorVelocity)(setTargetLinMotorVelocity)(setUpperAngLimit)(setUpperLinLimit)
            (setUseFrameOffset)
    )

    LM_FUNC_OVERLOAD_BOTH(btSliderConstraint, getFrameOffsetA, btTransform&)
    LM_FUNC_OVERLOAD_BOTH(btSliderConstraint, getFrameOffsetB, btTransform&)


    LM_CLASS(ns_bullet, btConeTwistConstraint)
    LM_BASE(btConeTwistConstraint, btTypedConstraint)
    LM_CONSTR(btConeTwistConstraint,,
        btRigidBody &, btRigidBody &,
        const btTransform &, const btTransform &)
    LM_CONSTR(btConeTwistConstraint,,
        btRigidBody &,
        const btTransform &)

    LM_FUNC(btConeTwistConstraint, (buildJacobian)(calcAngleInfo)(calcAngleInfo2)(calculateSerializeBufferSize)(enableMotor)
            (getAFrame)(getBFrame)(getFixThresh)(getParam)(GetPointForAngle)(getRigidBodyA)(getRigidBodyB)(getSolveSwingLimit)(getSolveTwistLimit)(getSwingSpan1)(getSwingSpan2)(getTwistAngle)(getTwistLimitSign)
            (getTwistSpan)(isPastSwingLimit)(serialize)(setAngularOnly)(setDamping)(setFixThresh)(setMaxMotorImpulse)(setMaxMotorImpulseNormalized)(setMotorTarget)(setMotorTargetInConstraintSpace)(setParam)
            (solveConstraintObsolete)(updateRHS)
    )

    LM_FUNC_OVERLOAD(btConeTwistConstraint, "setLimit", setLimit, void, btScalar, btScalar, btScalar, btScalar, btScalar, btScalar)
    LM_FUNC_OVERLOAD(btConeTwistConstraint, "setLimit", setLimit, void, int, btScalar)


    LM_CLASS(ns_bullet, btPoint2PointConstraint)
    LM_BASE(btPoint2PointConstraint, btTypedConstraint)
    LM_CONSTR(btPoint2PointConstraint,,
        btRigidBody &, btRigidBody &,
        btVector3 const&, btVector3 const&)
    LM_CONSTR(btPoint2PointConstraint,,
        btRigidBody &,
        btVector3 const&)

    LM_FUNC(btPoint2PointConstraint, (buildJacobian)(calculateSerializeBufferSize)
            (getParam)(getPivotInA)(getPivotInB)
            (serialize)(setParam)(setPivotA)(setPivotB)
            (updateRHS)
    )


    LM_CLASS(ns_bullet, btGeneric6DofConstraint)
    LM_BASE(btGeneric6DofConstraint, btTypedConstraint)
    LM_CONSTR(btGeneric6DofConstraint,,
        btRigidBody &, btRigidBody &,
        const btTransform &, const btTransform &,
        bool)
    LM_CONSTR(btGeneric6DofConstraint,,
        btRigidBody &,
        const btTransform &,
        bool)

    LM_FUNC(btGeneric6DofConstraint,
            (calcAnchorPos)
            (calculateSerializeBufferSize)
            (get_limit_motor_info2)
            (getAngle)
            (getAxis)
            (getCalculatedTransformA)(getCalculatedTransformB)
            (getParam)(getRelativePivotPosition)(getRotationalLimitMotor)(getTranslationalLimitMotor)
            (getUseFrameOffset)(isLimited)
            (serialize)(setAngularLowerLimit)(setAngularUpperLimit)(setLimit)
            (setLinearLowerLimit)(setLinearUpperLimit)(setUseFrameOffset)(updateRHS)
    )

    LM_FUNC_OVERLOAD_BOTH(btGeneric6DofConstraint, getFrameOffsetA, btTransform&)
    LM_FUNC_OVERLOAD_BOTH(btGeneric6DofConstraint, getFrameOffsetB, btTransform&)

    LM_FUNC_OVERLOAD(btGeneric6DofConstraint, "calculateTransforms", calculateTransforms, void)
    LM_FUNC_OVERLOAD(btGeneric6DofConstraint, "calculateTransforms", calculateTransforms, void, btTransform const&, btTransform const&)

    LM_CLASS(ns_bullet, btGeneric6DofSpringConstraint)
    LM_BASE(btGeneric6DofSpringConstraint, btGeneric6DofConstraint)
    LM_CONSTR(btGeneric6DofSpringConstraint,,
        btRigidBody &, btRigidBody &,
        const btTransform &, const btTransform &,
        bool)
    LM_FUNC(btGeneric6DofSpringConstraint, (enableSpring)(setDamping)(setStiffness))
    LM_FUNC_OVERLOAD(btGeneric6DofSpringConstraint, "setEquilibriumPoint", setEquilibriumPoint, void)
    LM_FUNC_OVERLOAD(btGeneric6DofSpringConstraint, "setEquilibriumPoint", setEquilibriumPoint, void, int)


    LM_CLASS(ns_bullet, btRotationalLimitMotor)
    LM_CONSTR(btRotationalLimitMotor,,)
    LM_FUNC(btRotationalLimitMotor, (isLimited)(needApplyTorques)(solveAngularLimits)(testLimitValue))
    LM_FIELD(btRotationalLimitMotor, (m_accumulatedImpulse)(m_bounce)(m_currentLimit)(m_currentLimitError)(m_currentPosition)(m_damping)(m_enableMotor)(m_hiLimit)(m_limitSoftness)
             (m_loLimit)(m_maxLimitForce)(m_maxMotorForce)(m_normalCFM)(m_stopCFM)(m_stopERP)(m_targetVelocity))

}

}}

