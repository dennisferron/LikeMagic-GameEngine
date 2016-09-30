#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace Bullet
	{

struct btSparseSdf_3
{
    ::LM::ExprPtr expr;
    auto Lerp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::float_expr;
    auto Decompose(GameBindings::float_expr) -> MissingType /* C++ btSparseSdf<3>::IntFrac */ ;
    auto Evaluate(GameBindings::Bullet::btVector3, GameBindings::Bullet::btCollisionShape, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::float_expr;
    auto RemoveReferences(GameBindings::Bullet::btCollisionShape) -> GameBindings::int_expr;
    auto GarbageCollect(GameBindings::int_expr) -> GameBindings::void_expr;
    auto get_nqueries() -> GameBindings::int_expr;
    auto set_nqueries(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_nprobes() -> GameBindings::int_expr;
    auto DistanceToShape(GameBindings::Bullet::btVector3, GameBindings::Bullet::btCollisionShape) -> GameBindings::float_expr;
    auto set_nprobes(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_ncells() -> GameBindings::int_expr;
    auto BuildCell(MissingType /* C++ btSparseSdf<3>::Cell& (end) */ ) -> GameBindings::void_expr;
    auto get_ncells() -> GameBindings::int_expr;
    auto ref_puid() -> GameBindings::int_expr;
    auto get_puid() -> GameBindings::int_expr;
    auto Reset() -> GameBindings::void_expr;
    auto set_puid(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_nqueries() -> GameBindings::int_expr;
    auto set_voxelsz(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_cells() -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*>& */ ;
    auto ref_nprobes() -> GameBindings::int_expr;
    auto set_cells(MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> */ ;
    auto set_ncells(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_voxelsz() -> GameBindings::float_expr;
    auto Initialize(GameBindings::int_expr) -> GameBindings::void_expr;
    auto get_voxelsz() -> GameBindings::float_expr;
    auto tmp() -> GameBindings::Bullet::btSparseSdf_3;
    auto lm_new() -> GameBindings::Bullet::btSparseSdf_3;
    auto get_cells() -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> */ ;
    auto Hash(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::Bullet::btCollisionShape) -> GameBindings::uint_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btHingeConstraint
{
    ::LM::ExprPtr expr;
    auto getHingeAngle() -> GameBindings::float_expr;
    auto getHingeAngle(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::float_expr;
    auto getBFrame_c() -> GameBindings::Bullet::btTransform;
    auto getAFrame_nc() -> GameBindings::Bullet::btTransform;
    auto getBFrame_nc() -> GameBindings::Bullet::btTransform;
    auto getAFrame_c() -> GameBindings::Bullet::btTransform;
    auto updateRHS(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setUseFrameOffset(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setMotorTargetScalarScalar(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setAxis(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getUseFrameOffset() -> GameBindings::bool_expr;
    auto getUpperLimit() -> GameBindings::float_expr;
    auto testLimit(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto setMaxMotorImpulse(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSolveLimit() -> GameBindings::int_expr;
    auto getMotorTargetVelosity() -> GameBindings::float_expr;
    auto setAngularOnly(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getMaxMotorImpulse() -> GameBindings::float_expr;
    auto getLowerLimit() -> GameBindings::float_expr;
    auto getLimitSign() -> GameBindings::float_expr;
    auto setMotorTargetQuatScalar(GameBindings::Bullet::btQuaternion, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getEnableAngularMotor() -> GameBindings::bool_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto setLimit(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getAngularOnly() -> GameBindings::bool_expr;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btHingeConstraint;
    auto lm_delete() -> GameBindings::void_expr;
    auto enableAngularMotor(GameBindings::bool_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto enableMotor(GameBindings::bool_expr) -> GameBindings::void_expr;
};struct btConeTwistConstraint
{
    ::LM::ExprPtr expr;
    auto updateRHS(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setMaxMotorImpulse(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setAngularOnly(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto isPastSwingLimit() -> GameBindings::bool_expr;
    auto getTwistSpan() -> GameBindings::float_expr;
    auto setMotorTargetInConstraintSpace(GameBindings::Bullet::btQuaternion) -> GameBindings::void_expr;
    auto setMaxMotorImpulseNormalized(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getTwistAngle() -> GameBindings::float_expr;
    auto setMotorTarget(GameBindings::Bullet::btQuaternion) -> GameBindings::void_expr;
    auto getSwingSpan2() -> GameBindings::float_expr;
    auto getRigidBodyA() -> GameBindings::Bullet::btRigidBody;
    auto getFixThresh() -> GameBindings::float_expr;
    auto GetPointForAngle(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btVector3;
    auto getTwistLimitSign() -> GameBindings::float_expr;
    auto getBFrame() -> GameBindings::Bullet::btTransform;
    auto setFixThresh(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSwingSpan1() -> GameBindings::float_expr;
    auto getAFrame() -> GameBindings::Bullet::btTransform;
    auto calcAngleInfo2(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::Bullet::btMatrix3x3, GameBindings::Bullet::btMatrix3x3) -> GameBindings::void_expr;
    auto setDamping(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSolveSwingLimit() -> GameBindings::int_expr;
    auto calcAngleInfo() -> GameBindings::void_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btConeTwistConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btConeTwistConstraint;
    auto setLimit(GameBindings::int_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setLimit(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSolveTwistLimit() -> GameBindings::int_expr;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btConeTwistConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btConeTwistConstraint;
    auto getRigidBodyB() -> GameBindings::Bullet::btRigidBody;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto enableMotor(GameBindings::bool_expr) -> GameBindings::void_expr;
};struct btTransform
{
    ::LM::ExprPtr expr;
    auto getBasis_c() -> GameBindings::Bullet::btMatrix3x3;
    auto setRotation(GameBindings::Bullet::btQuaternion) -> GameBindings::void_expr;
    auto setOrigin(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setIdentity() -> GameBindings::void_expr;
    auto setFromOpenGLMatrix(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setBasis(GameBindings::Bullet::btMatrix3x3) -> GameBindings::void_expr;
    auto serialize(MissingType /* C++ btTransformFloatData& (end) */ ) -> GameBindings::void_expr;
    auto getOrigin_c() -> GameBindings::Bullet::btVector3;
    auto mult(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto getOrigin_nc() -> GameBindings::Bullet::btVector3;
    auto inverse() -> GameBindings::Bullet::btTransform;
    auto serializeFloat(MissingType /* C++ btTransformFloatData& (end) */ ) -> GameBindings::void_expr;
    auto getRotation() -> GameBindings::Bullet::btQuaternion;
    auto tmp() -> GameBindings::Bullet::btTransform;
    auto tmp(GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btTransform;
    auto tmp(GameBindings::Bullet::btQuaternion, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btTransform;
    auto lm_new() -> GameBindings::Bullet::btTransform;
    auto lm_new(GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btTransform;
    auto lm_new(GameBindings::Bullet::btQuaternion, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btTransform;
    auto getIdentityTransform() -> GameBindings::Bullet::btTransform;
    auto getOpenGLMatrix(GameBindings::float_expr) -> GameBindings::void_expr;
    auto inverseTimes(GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btTransform;
    auto getBasis_nc() -> GameBindings::Bullet::btMatrix3x3;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto invXform(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
};struct btIndexedMesh
{
    ::LM::ExprPtr expr;
    auto ref_m_vertexType() -> GameBindings::Bullet::PHY_ScalarType;
    auto ref_m_indexType() -> GameBindings::Bullet::PHY_ScalarType;
    auto get_m_indexType() -> GameBindings::Bullet::PHY_ScalarType;
    auto ref_m_vertexStride() -> GameBindings::int_expr;
    auto get_m_vertexStride() -> GameBindings::int_expr;
    auto set_m_vertexBase(GameBindings::uchar_expr) -> GameBindings::uchar_expr;
    auto set_m_numVertices(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_vertexBase() -> GameBindings::uchar_expr;
    auto ref_m_triangleIndexStride() -> GameBindings::int_expr;
    auto set_m_vertexType(GameBindings::Bullet::PHY_ScalarType) -> GameBindings::Bullet::PHY_ScalarType;
    auto get_m_triangleIndexStride() -> GameBindings::int_expr;
    auto set_m_indexType(GameBindings::Bullet::PHY_ScalarType) -> GameBindings::Bullet::PHY_ScalarType;
    auto get_m_triangleIndexBase() -> GameBindings::uchar_expr;
    auto ref_m_triangleIndexBase() -> GameBindings::uchar_expr;
    auto set_m_triangleIndexStride(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_m_vertexBase() -> GameBindings::uchar_expr;
    auto ref_m_numTriangles() -> GameBindings::int_expr;
    auto get_m_numVertices() -> GameBindings::int_expr;
    auto tmp() -> GameBindings::Bullet::btIndexedMesh;
    auto get_m_vertexType() -> GameBindings::Bullet::PHY_ScalarType;
    auto lm_new() -> GameBindings::Bullet::btIndexedMesh;
    auto get_m_numTriangles() -> GameBindings::int_expr;
    auto ref_m_numVertices() -> GameBindings::int_expr;
    auto set_m_triangleIndexBase(GameBindings::uchar_expr) -> GameBindings::uchar_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_m_vertexStride(GameBindings::int_expr) -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto set_m_numTriangles(GameBindings::int_expr) -> GameBindings::int_expr;
};struct btStridingMeshInterface
{
    ::LM::ExprPtr expr;
    auto calculateSerializeBufferSize() -> GameBindings::int_expr;
    auto setScaling(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getScaling() -> GameBindings::Bullet::btVector3;
    auto getPremadeAabb(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setPremadeAabb(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto preallocateVertices(GameBindings::int_expr) -> GameBindings::void_expr;
    auto hasPremadeAabb() -> GameBindings::bool_expr;
    auto unLockReadOnlyVertexBase(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getLockedReadOnlyVertexIndexBase(MissingType /* C++ unsigned char const** (end) */ , GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::int_expr, MissingType /* C++ unsigned char const** (end) */ , GameBindings::int_expr, GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::int_expr) -> GameBindings::void_expr;
    auto getLockedVertexIndexBase(MissingType /* C++ unsigned char** (end) */ , GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::int_expr, MissingType /* C++ unsigned char** (end) */ , GameBindings::int_expr, GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::int_expr) -> GameBindings::void_expr;
    auto preallocateIndices(GameBindings::int_expr) -> GameBindings::void_expr;
    auto serialize(GameBindings::void_expr, MissingType /* C++ btSerializer* (end) */ ) -> GameBindings::char_expr;
    auto calculateAabbBruteForce(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getNumSubParts() -> GameBindings::int_expr;
    auto InternalProcessAllTriangles(MissingType /* C++ btInternalTriangleIndexCallback* (end) */ , GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto unLockVertexBase(GameBindings::int_expr) -> GameBindings::void_expr;
};struct btTriangleMesh
{
    ::LM::ExprPtr expr;
    auto addIndex(GameBindings::int_expr) -> GameBindings::void_expr;
    auto addTriangle(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getUse4componentVertices() -> GameBindings::bool_expr;
    auto getNumTriangles() -> GameBindings::int_expr;
    auto getUse32bitIndices() -> GameBindings::bool_expr;
    auto tmp(GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btTriangleMesh;
    auto lm_new(GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btTriangleMesh;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionObject
{
    ::LM::ExprPtr expr;
    auto getWorldTransform_nc() -> GameBindings::Bullet::btTransform;
    auto getInterpolationWorldTransform_c() -> GameBindings::Bullet::btTransform;
    auto getCollisionShape_nc() -> GameBindings::Bullet::btCollisionShape;
    auto getBroadphaseHandle_nc() -> MissingType /* C++ btBroadphaseProxy* */ ;
    auto getBroadphaseHandle_c() -> MissingType /* C++ btBroadphaseProxy const* */ ;
    auto getInterpolationWorldTransform_nc() -> GameBindings::Bullet::btTransform;
    auto setUserPointer(GameBindings::void_expr) -> GameBindings::void_expr;
    auto setRestitution(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setIslandTag(GameBindings::int_expr) -> GameBindings::void_expr;
    auto setInterpolationAngularVelocity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setHitFraction(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getCollisionShape_c() -> GameBindings::Bullet::btCollisionShape;
    auto setFriction(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setContactProcessingThreshold(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setCompanionId(GameBindings::int_expr) -> GameBindings::void_expr;
    auto setWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto setAnisotropicFriction(GameBindings::Bullet::btVector3, GameBindings::int_expr) -> GameBindings::void_expr;
    auto serialize(GameBindings::void_expr, MissingType /* C++ btSerializer* (end) */ ) -> GameBindings::char_expr;
    auto isStaticOrKinematicObject() -> GameBindings::bool_expr;
    auto isStaticObject() -> GameBindings::bool_expr;
    auto getRestitution() -> GameBindings::float_expr;
    auto getIslandTag() -> GameBindings::int_expr;
    auto setCollisionFlags(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getHitFraction() -> GameBindings::float_expr;
    auto setActivationState(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getInterpolationAngularVelocity() -> GameBindings::Bullet::btVector3;
    auto getFriction() -> GameBindings::float_expr;
    auto getDeactivationTime() -> GameBindings::float_expr;
    auto isKinematicObject() -> GameBindings::bool_expr;
    auto getCollisionFlags() -> GameBindings::int_expr;
    auto isActive() -> GameBindings::bool_expr;
    auto getWorldTransform_c() -> GameBindings::Bullet::btTransform;
    auto getContactProcessingThreshold() -> GameBindings::float_expr;
    auto getCompanionId() -> GameBindings::int_expr;
    auto hasAnisotropicFriction(GameBindings::int_expr) -> GameBindings::bool_expr;
    auto setDeactivationTime(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getCcdSquareMotionThreshold() -> GameBindings::float_expr;
    auto getCcdMotionThreshold() -> GameBindings::float_expr;
    auto getActivationState() -> GameBindings::int_expr;
    auto forceActivationState(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getCcdSweptSphereRadius() -> GameBindings::float_expr;
    auto checkCollideWith(GameBindings::Bullet::btCollisionObject) -> GameBindings::bool_expr;
    auto setInterpolationLinearVelocity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto hasContactResponse() -> GameBindings::bool_expr;
    auto calculateSerializeBufferSize() -> GameBindings::int_expr;
    auto setCcdSweptSphereRadius(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setBroadphaseHandle(MissingType /* C++ btBroadphaseProxy* (end) */ ) -> GameBindings::void_expr;
    auto activate(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto mergesSimulationIslands() -> GameBindings::bool_expr;
    auto getInterpolationLinearVelocity() -> GameBindings::Bullet::btVector3;
    auto getUserPointer() -> GameBindings::void_expr;
    auto setInterpolationWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto setCollisionShape(GameBindings::Bullet::btCollisionShape) -> GameBindings::void_expr;
    auto setCcdMotionThreshold(GameBindings::float_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btPairCachingGhostObject
{
    ::LM::ExprPtr expr;
    auto getOverlappingPairCache() -> MissingType /* C++ btHashedOverlappingPairCache* */ ;
    auto tmp() -> GameBindings::Bullet::btPairCachingGhostObject;
    auto lm_new() -> GameBindings::Bullet::btPairCachingGhostObject;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btIDebugDraw
{
    ::LM::ExprPtr expr;
    auto getDebugMode() -> GameBindings::int_expr;
    auto setDebugMode(GameBindings::int_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btTypedConstraint
{
    ::LM::ExprPtr expr;
    auto getRigidBodyB_c() -> GameBindings::Bullet::btRigidBody;
    auto getRigidBodyA_nc() -> GameBindings::Bullet::btRigidBody;
    auto solveConstraintObsolete(MissingType /* C++ btSolverBody& (end) */ , MissingType /* C++ btSolverBody& (end) */ , GameBindings::float_expr) -> GameBindings::void_expr;
    auto serialize(GameBindings::void_expr, MissingType /* C++ btSerializer* (end) */ ) -> GameBindings::char_expr;
    auto getUserConstraintType() -> GameBindings::int_expr;
    auto getUserConstraintId() -> GameBindings::int_expr;
    auto setDbgDrawSize(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getParam(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::float_expr;
    auto setUserConstraintType(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getDbgDrawSize() -> GameBindings::float_expr;
    auto getConstraintType() -> MissingType /* C++ btTypedConstraintType */ ;
    auto enableFeedback(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setUserConstraintId(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getAppliedImpulse() -> GameBindings::float_expr;
    auto calculateSerializeBufferSize() -> GameBindings::int_expr;
    auto getRigidBodyB_nc() -> GameBindings::Bullet::btRigidBody;
    auto getRigidBodyA_c() -> GameBindings::Bullet::btRigidBody;
    auto needsFeedback() -> GameBindings::bool_expr;
    auto buildJacobian() -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getUid() -> GameBindings::int_expr;
    auto setParam(GameBindings::int_expr, GameBindings::float_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedContactResultCallback
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::LangBlockExpr, GameBindings::LangBlockExpr) -> GameBindings::Bullet::ScriptedContactResultCallback;
    auto lm_new(GameBindings::LangBlockExpr, GameBindings::LangBlockExpr) -> GameBindings::Bullet::ScriptedContactResultCallback;
    auto lm_delete() -> GameBindings::void_expr;
    auto baseNeedsCollision(MissingType /* C++ btBroadphaseProxy* (end) */ ) -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btDbvtBroadphase
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::Bullet::btDbvtBroadphase;
    auto lm_new() -> GameBindings::Bullet::btDbvtBroadphase;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btTriangleMeshShape
{
    ::LM::ExprPtr expr;
    auto getMeshInterface_nc() -> GameBindings::Bullet::btStridingMeshInterface;
    auto getLocalAabbMax() -> GameBindings::Bullet::btVector3;
    auto getLocalAabbMin() -> GameBindings::Bullet::btVector3;
    auto recalcLocalAabb() -> GameBindings::void_expr;
    auto localGetSupportingVertexWithoutMargin(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto localGetSupportingVertex(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto getMeshInterface_c() -> GameBindings::Bullet::btStridingMeshInterface;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btRotationalLimitMotor
{
    ::LM::ExprPtr expr;
    auto ref_m_stopERP() -> GameBindings::float_expr;
    auto set_m_stopERP(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_stopCFM() -> GameBindings::float_expr;
    auto ref_m_maxMotorForce() -> GameBindings::float_expr;
    auto set_m_maxMotorForce(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_normalCFM() -> GameBindings::float_expr;
    auto ref_m_maxLimitForce() -> GameBindings::float_expr;
    auto ref_m_targetVelocity() -> GameBindings::float_expr;
    auto get_m_stopCFM() -> GameBindings::float_expr;
    auto ref_m_loLimit() -> GameBindings::float_expr;
    auto ref_m_limitSoftness() -> GameBindings::float_expr;
    auto set_m_limitSoftness(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_hiLimit() -> GameBindings::float_expr;
    auto ref_m_normalCFM() -> GameBindings::float_expr;
    auto set_m_normalCFM(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_hiLimit(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_limitSoftness() -> GameBindings::float_expr;
    auto set_m_enableMotor(GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto set_m_damping(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_currentPosition() -> GameBindings::float_expr;
    auto ref_m_currentLimitError() -> GameBindings::float_expr;
    auto get_m_currentLimitError() -> GameBindings::float_expr;
    auto set_m_currentLimitError(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_damping() -> GameBindings::float_expr;
    auto ref_m_currentLimit() -> GameBindings::int_expr;
    auto get_m_maxMotorForce() -> GameBindings::float_expr;
    auto set_m_maxLimitForce(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_currentPosition(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_currentLimit(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_stopERP() -> GameBindings::float_expr;
    auto ref_m_bounce() -> GameBindings::float_expr;
    auto ref_m_currentPosition() -> GameBindings::float_expr;
    auto get_m_bounce() -> GameBindings::float_expr;
    auto get_m_maxLimitForce() -> GameBindings::float_expr;
    auto get_m_loLimit() -> GameBindings::float_expr;
    auto set_m_bounce(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_enableMotor() -> GameBindings::bool_expr;
    auto testLimitValue(GameBindings::float_expr) -> GameBindings::int_expr;
    auto solveAngularLimits(GameBindings::float_expr, GameBindings::Bullet::btVector3, GameBindings::float_expr, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody) -> GameBindings::float_expr;
    auto get_m_enableMotor() -> GameBindings::bool_expr;
    auto get_m_targetVelocity() -> GameBindings::float_expr;
    auto needApplyTorques() -> GameBindings::bool_expr;
    auto set_m_accumulatedImpulse(GameBindings::float_expr) -> GameBindings::float_expr;
    auto isLimited() -> GameBindings::bool_expr;
    auto tmp() -> GameBindings::Bullet::btRotationalLimitMotor;
    auto lm_new() -> GameBindings::Bullet::btRotationalLimitMotor;
    auto get_m_hiLimit() -> GameBindings::float_expr;
    auto get_m_accumulatedImpulse() -> GameBindings::float_expr;
    auto set_m_targetVelocity(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_loLimit(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_accumulatedImpulse() -> GameBindings::float_expr;
    auto set_m_stopCFM(GameBindings::float_expr) -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_m_damping() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto get_m_currentLimit() -> GameBindings::int_expr;
};struct btDispatcher
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btTypedObject
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionDispatcher
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btCollisionDispatcher;
    auto lm_new(GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btCollisionDispatcher;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftBodyHelpers
{
    ::LM::ExprPtr expr;
    auto CreateFromTetGenData(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::char_expr, GameBindings::char_expr, GameBindings::char_expr, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btSoftBody;
    auto CreateEllipsoid(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::int_expr) -> GameBindings::Bullet::btSoftBody;
    auto DrawFrame(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw) -> GameBindings::void_expr;
    auto DrawFaceTree(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto CreatePatch(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btSoftBody;
    auto DrawClusterTree(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto DrawNodeTree(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto CreatePatchUV(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::bool_expr, GameBindings::float_expr) -> GameBindings::Bullet::btSoftBody;
    auto DrawInfos(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto CalculateUV(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::float_expr;
    auto CreateRope(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::Bullet::btSoftBody;
    auto Draw(GameBindings::Bullet::btSoftBody, GameBindings::Bullet::btIDebugDraw, GameBindings::int_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto CreateFromConvexHull(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::Bullet::btVector3, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btSoftBody;
    auto CreateFromTriMesh(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::float_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btSoftBody;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftBodyWorldInfo
{
    ::LM::ExprPtr expr;
    auto get_m_sparsesdf() -> GameBindings::Bullet::btSparseSdf_3;
    auto get_m_gravity() -> GameBindings::Bullet::btVector3;
    auto get_m_dispatcher() -> GameBindings::Bullet::btDispatcher;
    auto ref_m_broadphase() -> GameBindings::Bullet::btBroadphaseInterface;
    auto get_m_broadphase() -> GameBindings::Bullet::btBroadphaseInterface;
    auto set_m_gravity(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto set_m_broadphase(GameBindings::Bullet::btBroadphaseInterface) -> GameBindings::Bullet::btBroadphaseInterface;
    auto set_water_normal(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_gravity() -> GameBindings::Bullet::btVector3;
    auto ref_water_offset() -> GameBindings::float_expr;
    auto get_water_density() -> GameBindings::float_expr;
    auto ref_air_density() -> GameBindings::float_expr;
    auto get_water_offset() -> GameBindings::float_expr;
    auto get_water_normal() -> GameBindings::Bullet::btVector3;
    auto ref_water_normal() -> GameBindings::Bullet::btVector3;
    auto ref_m_sparsesdf() -> GameBindings::Bullet::btSparseSdf_3;
    auto tmp() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto get_air_density() -> GameBindings::float_expr;
    auto ref_water_density() -> GameBindings::float_expr;
    auto set_m_sparsesdf(GameBindings::Bullet::btSparseSdf_3) -> GameBindings::Bullet::btSparseSdf_3;
    auto set_air_density(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_dispatcher(GameBindings::Bullet::btDispatcher) -> GameBindings::Bullet::btDispatcher;
    auto lm_new() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_water_offset(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_dispatcher() -> GameBindings::Bullet::btDispatcher;
    auto set_water_density(GameBindings::float_expr) -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftBody_Config
{
    ::LM::ExprPtr expr;
    auto ref_m_dsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_>& */ ;
    auto get_m_psequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ ;
    auto set_m_psequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ ;
    auto ref_m_vsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_>& */ ;
    auto get_m_vsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> */ ;
    auto ref_collisions() -> GameBindings::int_expr;
    auto ref_citerations() -> GameBindings::int_expr;
    auto set_citerations(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_diterations() -> GameBindings::int_expr;
    auto get_diterations() -> GameBindings::int_expr;
    auto set_diterations(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_piterations() -> GameBindings::int_expr;
    auto ref_viterations() -> GameBindings::int_expr;
    auto set_viterations(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_timescale() -> GameBindings::float_expr;
    auto get_timescale() -> GameBindings::float_expr;
    auto get_maxvolume() -> GameBindings::float_expr;
    auto set_maxvolume(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kSK_SPLT_CL() -> GameBindings::float_expr;
    auto set_kSR_SPLT_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_kSSHR_CL() -> GameBindings::float_expr;
    auto get_piterations() -> GameBindings::int_expr;
    auto set_kSSHR_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kSKHR_CL() -> GameBindings::float_expr;
    auto ref_m_psequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_>& */ ;
    auto get_kSKHR_CL() -> GameBindings::float_expr;
    auto ref_kSRHR_CL() -> GameBindings::float_expr;
    auto get_kSRHR_CL() -> GameBindings::float_expr;
    auto ref_kAHR() -> GameBindings::float_expr;
    auto get_kAHR() -> GameBindings::float_expr;
    auto set_kAHR(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_kSK_SPLT_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_kSHR(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kSR_SPLT_CL() -> GameBindings::float_expr;
    auto set_kKHR(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kMT() -> GameBindings::float_expr;
    auto set_collisions(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_kDF() -> GameBindings::float_expr;
    auto get_kSS_SPLT_CL() -> GameBindings::float_expr;
    auto get_collisions() -> GameBindings::int_expr;
    auto set_kCHR(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_dsequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ ;
    auto get_kSHR() -> GameBindings::float_expr;
    auto set_kDF(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kVC() -> GameBindings::float_expr;
    auto get_kSR_SPLT_CL() -> GameBindings::float_expr;
    auto ref_kPR() -> GameBindings::float_expr;
    auto get_kVC() -> GameBindings::float_expr;
    auto get_kPR() -> GameBindings::float_expr;
    auto get_kCHR() -> GameBindings::float_expr;
    auto get_citerations() -> GameBindings::int_expr;
    auto get_kMT() -> GameBindings::float_expr;
    auto ref_kSHR() -> GameBindings::float_expr;
    auto set_kPR(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kDG() -> GameBindings::float_expr;
    auto ref_maxvolume() -> GameBindings::float_expr;
    auto set_kVC(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_kLF() -> GameBindings::float_expr;
    auto set_kSRHR_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_kDP(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kDP() -> GameBindings::float_expr;
    auto get_kSK_SPLT_CL() -> GameBindings::float_expr;
    auto get_kKHR() -> GameBindings::float_expr;
    auto get_m_dsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ ;
    auto ref_kLF() -> GameBindings::float_expr;
    auto get_kDG() -> GameBindings::float_expr;
    auto set_m_vsequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> */ ;
    auto set_timescale(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kVCF() -> GameBindings::float_expr;
    auto ref_kKHR() -> GameBindings::float_expr;
    auto get_kDP() -> GameBindings::float_expr;
    auto get_kVCF() -> GameBindings::float_expr;
    auto ref_kDF() -> GameBindings::float_expr;
    auto ref_kSSHR_CL() -> GameBindings::float_expr;
    auto set_kMT(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kSS_SPLT_CL() -> GameBindings::float_expr;
    auto set_kDG(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_aeromodel() -> MissingType /* C++ btSoftBody::eAeroModel::_& */ ;
    auto set_kVCF(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_kSKHR_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_aeromodel() -> MissingType /* C++ btSoftBody::eAeroModel::_ */ ;
    auto set_aeromodel(MissingType /* C++ btSoftBody::eAeroModel::_ const& (end) */ ) -> MissingType /* C++ btSoftBody::eAeroModel::_ */ ;
    auto set_kSS_SPLT_CL(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_kCHR() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_piterations(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_viterations() -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto set_kLF(GameBindings::float_expr) -> GameBindings::float_expr;
};struct btConstraintSolver
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct PHY_ScalarType
{
    ::LM::ExprPtr expr;
    auto value() -> GameBindings::int_expr;
    auto asString() -> GameBindings::string_expr;
    auto operator ==(GameBindings::Bullet::PHY_ScalarType) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::Bullet::PHY_ScalarType) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btBvhTriangleMeshShape
{
    ::LM::ExprPtr expr;
    auto usesQuantizedAabbCompression() -> GameBindings::bool_expr;
    auto buildOptimizedBvh() -> GameBindings::void_expr;
    auto setOptimizedBvh(MissingType /* C++ btOptimizedBvh* (end) */ , GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getOptimizedBvh() -> MissingType /* C++ btOptimizedBvh* */ ;
    auto refitTree(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto performRaycast(MissingType /* C++ btTriangleCallback* (end) */ , GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getOwnsBvh() -> GameBindings::bool_expr;
    auto performConvexcast(MissingType /* C++ btTriangleCallback* (end) */ , GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto tmp(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btBvhTriangleMeshShape;
    auto tmp(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btBvhTriangleMeshShape;
    auto partialRefitTree(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lm_new(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btBvhTriangleMeshShape;
    auto lm_new(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btBvhTriangleMeshShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSequentialImpulseConstraintSolver
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::Bullet::btSequentialImpulseConstraintSolver;
    auto lm_new() -> GameBindings::Bullet::btSequentialImpulseConstraintSolver;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btDefaultMotionState
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btDefaultMotionState;
    auto lm_new(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btDefaultMotionState;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btHeightfieldTerrainShape
{
    ::LM::ExprPtr expr;
    auto setUseDiamondSubdivision(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr, GameBindings::void_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::bool_expr) -> GameBindings::Bullet::btHeightfieldTerrainShape;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr, GameBindings::void_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::int_expr, GameBindings::Bullet::PHY_ScalarType, GameBindings::bool_expr) -> GameBindings::Bullet::btHeightfieldTerrainShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftRigidDynamicsWorld
{
    ::LM::ExprPtr expr;
    auto getSoftBodyArray_nc() -> MissingType /* C++ btAlignedObjectArray<btSoftBody*>& */ ;
    auto getWorldInfo_c() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto rayTestSingle(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::Bullet::btCollisionObject, GameBindings::Bullet::btCollisionShape, GameBindings::Bullet::btTransform, GameBindings::Bullet::btCollisionWorld_RayResultCallback) -> GameBindings::void_expr;
    auto setDrawFlags(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getDrawFlags() -> GameBindings::int_expr;
    auto addSoftBody(GameBindings::Bullet::btSoftBody, GameBindings::short_expr, GameBindings::short_expr) -> GameBindings::void_expr;
    auto getWorldInfo_nc() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto tmp(GameBindings::Bullet::btDispatcher, GameBindings::Bullet::btBroadphaseInterface, GameBindings::Bullet::btConstraintSolver, GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btSoftRigidDynamicsWorld;
    auto removeSoftBody(GameBindings::Bullet::btSoftBody) -> GameBindings::void_expr;
    auto lm_new(GameBindings::Bullet::btDispatcher, GameBindings::Bullet::btBroadphaseInterface, GameBindings::Bullet::btConstraintSolver, GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btSoftRigidDynamicsWorld;
    auto lm_delete() -> GameBindings::void_expr;
    auto getSoftBodyArray_c() -> MissingType /* C++ btAlignedObjectArray<btSoftBody*> const& */ ;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld_ContactResultCallback
{
    ::LM::ExprPtr expr;
    auto needsCollision(MissingType /* C++ btBroadphaseProxy* (end) */ ) -> GameBindings::bool_expr;
    auto get_m_collisionFilterMask() -> GameBindings::short_expr;
    auto get_m_collisionFilterGroup() -> GameBindings::short_expr;
    auto addSingleResult(GameBindings::Bullet::btManifoldPoint, MissingType /* C++ btCollisionObjectWrapper const* (end) */ , GameBindings::int_expr, GameBindings::int_expr, MissingType /* C++ btCollisionObjectWrapper const* (end) */ , GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::float_expr;
    auto set_m_collisionFilterMask(GameBindings::short_expr) -> GameBindings::short_expr;
    auto ref_m_collisionFilterGroup() -> GameBindings::short_expr;
    auto set_m_collisionFilterGroup(GameBindings::short_expr) -> GameBindings::short_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto ref_m_collisionFilterMask() -> GameBindings::short_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedClosestRayResultCallback
{
    ::LM::ExprPtr expr;
    auto test_equals(GameBindings::Bullet::btCollisionObject, GameBindings::Bullet::btCollisionObject) -> GameBindings::bool_expr;
    auto baseAddSingleResult(GameBindings::Bullet::btCollisionWorld_LocalRayResult, GameBindings::bool_expr) -> GameBindings::float_expr;
    auto tmp(GameBindings::LangBlockExpr) -> GameBindings::Bullet::ScriptedClosestRayResultCallback;
    auto lm_new(GameBindings::LangBlockExpr) -> GameBindings::Bullet::ScriptedClosestRayResultCallback;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld_ClosestRayResultCallback
{
    ::LM::ExprPtr expr;
    auto set_m_hitPointWorld(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_hitPointWorld() -> GameBindings::Bullet::btVector3;
    auto get_m_hitNormalWorld() -> GameBindings::Bullet::btVector3;
    auto get_m_hitPointWorld() -> GameBindings::Bullet::btVector3;
    auto set_m_hitNormalWorld(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_hitNormalWorld() -> GameBindings::Bullet::btVector3;
    auto ref_m_rayToWorld() -> GameBindings::Bullet::btVector3;
    auto set_m_rayToWorld(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_rayFromWorld() -> GameBindings::Bullet::btVector3;
    auto get_m_rayFromWorld() -> GameBindings::Bullet::btVector3;
    auto set_m_rayFromWorld(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto get_m_rayToWorld() -> GameBindings::Bullet::btVector3;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct DebugDrawModes
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld_RayResultCallback
{
    ::LM::ExprPtr expr;
    auto ref_m_flags() -> GameBindings::uint_expr;
    auto get_m_flags() -> GameBindings::uint_expr;
    auto ref_m_collisionFilterMask() -> GameBindings::short_expr;
    auto set_m_flags(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto get_m_collisionFilterMask() -> GameBindings::short_expr;
    auto get_m_collisionFilterGroup() -> GameBindings::short_expr;
    auto ref_m_collisionObject() -> GameBindings::Bullet::btCollisionObject;
    auto set_m_closestHitFraction(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_collisionObject(GameBindings::Bullet::btCollisionObject) -> GameBindings::Bullet::btCollisionObject;
    auto needsCollision(MissingType /* C++ btBroadphaseProxy* (end) */ ) -> GameBindings::bool_expr;
    auto hasHit() -> GameBindings::bool_expr;
    auto get_m_closestHitFraction() -> GameBindings::float_expr;
    auto set_m_collisionFilterGroup(GameBindings::short_expr) -> GameBindings::short_expr;
    auto ref_m_collisionFilterGroup() -> GameBindings::short_expr;
    auto set_m_collisionFilterMask(GameBindings::short_expr) -> GameBindings::short_expr;
    auto addSingleResult(GameBindings::Bullet::btCollisionWorld_LocalRayResult, GameBindings::bool_expr) -> GameBindings::float_expr;
    auto ref_m_closestHitFraction() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_m_collisionObject() -> GameBindings::Bullet::btCollisionObject;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftBody
{
    ::LM::ExprPtr expr;
    auto ref_m_bounds(MissingType /* C++ unsigned long long (end) */ ) -> MissingType /* C++ btVector3 []& */ ;
    auto get_m_bounds(MissingType /* C++ unsigned long long (end) */ ) -> MissingType /* C++ btVector3 [] */ ;
    auto set_m_bounds(MissingType /* C++ unsigned long long (end) */ , GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto ref_m_userIndexMapping() -> MissingType /* C++ btAlignedObjectArray<int>& */ ;
    auto get_m_userIndexMapping() -> MissingType /* C++ btAlignedObjectArray<int> */ ;
    auto get_m_initialWorldTransform() -> GameBindings::Bullet::btTransform;
    auto set_m_initialWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btTransform;
    auto ref_m_clusterConnectivity() -> MissingType /* C++ btAlignedObjectArray<bool>& */ ;
    auto get_m_clusterConnectivity() -> MissingType /* C++ btAlignedObjectArray<bool> */ ;
    auto set_m_clusterConnectivity(MissingType /* C++ btAlignedObjectArray<bool> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<bool> */ ;
    auto ref_m_bUpdateRtCst() -> GameBindings::bool_expr;
    auto set_m_bUpdateRtCst(GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto ref_m_timeacc() -> GameBindings::float_expr;
    auto get_m_timeacc() -> GameBindings::float_expr;
    auto set_m_materials(MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> */ ;
    auto ref_m_joints() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*>& */ ;
    auto set_m_joints(MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> */ ;
    auto ref_m_rcontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact>& */ ;
    auto get_m_clusters() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> */ ;
    auto ref_m_anchors() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor>& */ ;
    auto set_m_anchors(MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> */ ;
    auto ref_m_scontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact>& */ ;
    auto set_m_tetras(MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> */ ;
    auto get_m_faces() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> */ ;
    auto get_m_nodes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> */ ;
    auto get_m_notes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> */ ;
    auto set_m_notes(MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> */ ;
    auto set_m_scontacts(MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> */ ;
    auto set_m_timeacc(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_worldInfo(GameBindings::Bullet::btSoftBodyWorldInfo) -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto set_m_nodes(MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> */ ;
    auto set_m_clusters(MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> */ ;
    auto ref_m_tag() -> GameBindings::void_expr;
    auto get_m_materials() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> */ ;
    auto ref_m_worldInfo() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto get_m_tag() -> GameBindings::void_expr;
    auto get_m_scontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> */ ;
    auto get_m_rcontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> */ ;
    auto ref_m_pose() -> MissingType /* C++ btSoftBody::Pose& */ ;
    auto get_m_bUpdateRtCst() -> GameBindings::bool_expr;
    auto ref_m_nodes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node>& */ ;
    auto ref_m_clusters() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*>& */ ;
    auto ref_m_sst() -> MissingType /* C++ btSoftBody::SolverState& */ ;
    auto get_m_sst() -> MissingType /* C++ btSoftBody::SolverState */ ;
    auto get_m_tetras() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> */ ;
    auto set_m_tag(GameBindings::void_expr) -> GameBindings::void_expr;
    auto set_m_rcontacts(MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> */ ;
    auto set_m_sst(MissingType /* C++ btSoftBody::SolverState const& (end) */ ) -> MissingType /* C++ btSoftBody::SolverState */ ;
    auto set_m_cfg(GameBindings::Bullet::btSoftBody_Config) -> GameBindings::Bullet::btSoftBody_Config;
    auto set_m_links(MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> */ ;
    auto rotate(GameBindings::Bullet::btQuaternion) -> GameBindings::void_expr;
    auto get_m_cfg() -> GameBindings::Bullet::btSoftBody_Config;
    auto get_m_collisionDisabledObjects() -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> */ ;
    auto ref_m_links() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link>& */ ;
    auto transform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto ref_m_notes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note>& */ ;
    auto tmp(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::int_expr, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btSoftBody;
    auto ref_m_collisionDisabledObjects() -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*>& */ ;
    auto translate(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto set_m_pose(MissingType /* C++ btSoftBody::Pose const& (end) */ ) -> MissingType /* C++ btSoftBody::Pose */ ;
    auto ref_m_cfg() -> GameBindings::Bullet::btSoftBody_Config;
    auto ref_m_tetras() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra>& */ ;
    auto lm_new(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::int_expr, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btSoftBody;
    auto ref_m_faces() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face>& */ ;
    auto set_m_userIndexMapping(MissingType /* C++ btAlignedObjectArray<int> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<int> */ ;
    auto set_m_collisionDisabledObjects(MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> */ ;
    auto get_m_worldInfo() -> GameBindings::Bullet::btSoftBodyWorldInfo;
    auto ref_m_materials() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*>& */ ;
    auto get_m_anchors() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> */ ;
    auto ref_m_initialWorldTransform() -> GameBindings::Bullet::btTransform;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_m_links() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> */ ;
    auto get_m_joints() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> */ ;
    auto get_m_pose() -> MissingType /* C++ btSoftBody::Pose */ ;
    auto set_m_faces(MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> const& (end) */ ) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> */ ;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btDynamicsWorld
{
    ::LM::ExprPtr expr;
    auto setWorldUserInfo(GameBindings::void_expr) -> GameBindings::void_expr;
    auto setConstraintSolver(GameBindings::Bullet::btConstraintSolver) -> GameBindings::void_expr;
    auto removeVehicle(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto removeRigidBody(GameBindings::Bullet::btRigidBody) -> GameBindings::void_expr;
    auto synchronizeMotionStates() -> GameBindings::void_expr;
    auto getWorldType() -> MissingType /* C++ btDynamicsWorldType */ ;
    auto getSolverInfo() -> MissingType /* C++ btContactSolverInfo& */ ;
    auto setInternalTickCallback(MissingType /* C++ void (btDynamicsWorld*, float)* (end) */ , GameBindings::void_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getNumConstraints() -> GameBindings::int_expr;
    auto removeCharacter(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto getConstraintSolver() -> GameBindings::Bullet::btConstraintSolver;
    auto clearForces() -> GameBindings::void_expr;
    auto getGravity() -> GameBindings::Bullet::btVector3;
    auto removeAction(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto addAction(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto addVehicle(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto setGravity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto debugDrawWorld() -> GameBindings::void_expr;
    auto addCharacter(MissingType /* C++ btActionInterface* (end) */ ) -> GameBindings::void_expr;
    auto removeConstraint(GameBindings::Bullet::btTypedConstraint) -> GameBindings::void_expr;
    auto addRigidBody(GameBindings::Bullet::btRigidBody) -> GameBindings::void_expr;
    auto addRigidBody(GameBindings::Bullet::btRigidBody, GameBindings::short_expr, GameBindings::short_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto stepSimulation(GameBindings::float_expr, GameBindings::int_expr, GameBindings::float_expr) -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto addConstraint(GameBindings::Bullet::btTypedConstraint, GameBindings::bool_expr) -> GameBindings::void_expr;
};struct btCompoundShape
{
    ::LM::ExprPtr expr;
    auto getChildTransform_c(GameBindings::int_expr) -> GameBindings::Bullet::btTransform;
    auto getChildTransform_nc(GameBindings::int_expr) -> GameBindings::Bullet::btTransform;
    auto updateChildTransform(GameBindings::int_expr, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto removeChildShapeByIndex(GameBindings::int_expr) -> GameBindings::void_expr;
    auto removeChildShape(GameBindings::Bullet::btCollisionShape) -> GameBindings::void_expr;
    auto getUpdateRevision() -> GameBindings::int_expr;
    auto getNumChildShapes() -> GameBindings::int_expr;
    auto getDynamicAabbTree_nc() -> MissingType /* C++ btDbvt* */ ;
    auto getChildList() -> MissingType /* C++ btCompoundShapeChild* */ ;
    auto addChildShape(GameBindings::Bullet::btTransform, GameBindings::Bullet::btCollisionShape) -> GameBindings::void_expr;
    auto getDynamicAabbTree_c() -> MissingType /* C++ btDbvt const* */ ;
    auto getChildShape_nc(GameBindings::int_expr) -> GameBindings::Bullet::btCollisionShape;
    auto tmp(GameBindings::bool_expr) -> GameBindings::Bullet::btCompoundShape;
    auto getChildShape_c(GameBindings::int_expr) -> GameBindings::Bullet::btCollisionShape;
    auto recalculateLocalAabb() -> GameBindings::void_expr;
    auto lm_new(GameBindings::bool_expr) -> GameBindings::Bullet::btCompoundShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto calculatePrincipalAxisTransform(GameBindings::float_expr, GameBindings::Bullet::btTransform, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btDiscreteDynamicsWorld
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btDispatcher, GameBindings::Bullet::btBroadphaseInterface, GameBindings::Bullet::btConstraintSolver, GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btDiscreteDynamicsWorld;
    auto lm_new(GameBindings::Bullet::btDispatcher, GameBindings::Bullet::btBroadphaseInterface, GameBindings::Bullet::btConstraintSolver, GameBindings::Bullet::btCollisionConfiguration) -> GameBindings::Bullet::btDiscreteDynamicsWorld;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld
{
    ::LM::ExprPtr expr;
    auto getDebugDrawer() -> GameBindings::Bullet::btIDebugDraw;
    auto setDebugDrawer(GameBindings::Bullet::btIDebugDraw) -> GameBindings::void_expr;
    auto contactTest(GameBindings::Bullet::btCollisionObject, GameBindings::Bullet::btCollisionWorld_ContactResultCallback) -> GameBindings::void_expr;
    auto rayTest(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btCollisionWorld_RayResultCallback) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btConeShapeZ
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShapeZ;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShapeZ;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedWorldManager
{
    ::LM::ExprPtr expr;
    auto setOnTick(GameBindings::Bullet::btDynamicsWorld, GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto tmp() -> GameBindings::Bullet::ScriptedWorldManager;
    auto lm_new() -> GameBindings::Bullet::ScriptedWorldManager;
    auto setOnPreTick(GameBindings::Bullet::btDynamicsWorld, GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btMatrix3x3
{
    ::LM::ExprPtr expr;
    auto transposeTimes(GameBindings::Bullet::btMatrix3x3) -> GameBindings::Bullet::btMatrix3x3;
    auto transpose() -> GameBindings::Bullet::btMatrix3x3;
    auto tdotx(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto setIdentity() -> GameBindings::void_expr;
    auto setValue(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setEulerZYX(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setFromOpenGLSubMatrix(GameBindings::float_expr) -> GameBindings::void_expr;
    auto serialize(MissingType /* C++ btMatrix3x3FloatData& (end) */ ) -> GameBindings::void_expr;
    auto scaled(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btMatrix3x3;
    auto serializeFloat(MissingType /* C++ btMatrix3x3FloatData& (end) */ ) -> GameBindings::void_expr;
    auto inverse() -> GameBindings::Bullet::btMatrix3x3;
    auto getRow(GameBindings::int_expr) -> GameBindings::Bullet::btVector3;
    auto tdoty(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto getRotation(GameBindings::Bullet::btQuaternion) -> GameBindings::void_expr;
    auto getEulerZYX(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto tdotz(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto getEulerYPR(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto deSerialize(MissingType /* C++ btMatrix3x3FloatData const& (end) */ ) -> GameBindings::void_expr;
    auto getOpenGLSubMatrix(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getColumn(GameBindings::int_expr) -> GameBindings::Bullet::btVector3;
    auto adjoint() -> GameBindings::Bullet::btMatrix3x3;
    auto deSerializeDouble(MissingType /* C++ btMatrix3x3DoubleData const& (end) */ ) -> GameBindings::void_expr;
    auto absolute() -> GameBindings::Bullet::btMatrix3x3;
    auto getIdentityMatrix() -> GameBindings::Bullet::btMatrix3x3;
    auto diagonalize(GameBindings::Bullet::btMatrix3x3, GameBindings::float_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto timesTranspose(GameBindings::Bullet::btMatrix3x3) -> GameBindings::Bullet::btMatrix3x3;
    auto tmp() -> GameBindings::Bullet::btMatrix3x3;
    auto lm_new() -> GameBindings::Bullet::btMatrix3x3;
    auto determinant() -> GameBindings::float_expr;
    auto setEulerYPR(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto cofac(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::float_expr;
    auto deSerializeFloat(MissingType /* C++ btMatrix3x3FloatData const& (end) */ ) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btConeShapeX
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShapeX;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShapeX;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btConeShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShape;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btConeShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btTriangleIndexVertexArray
{
    ::LM::ExprPtr expr;
    auto getIndexedMeshArray_nc() -> MissingType /* C++ btAlignedObjectArray<btIndexedMesh>& */ ;
    auto addIndexedMesh(GameBindings::Bullet::btIndexedMesh, GameBindings::Bullet::PHY_ScalarType) -> GameBindings::void_expr;
    auto getIndexedMeshArray_c() -> MissingType /* C++ btAlignedObjectArray<btIndexedMesh> const& */ ;
    auto tmp() -> GameBindings::Bullet::btTriangleIndexVertexArray;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::float_expr, GameBindings::int_expr) -> GameBindings::Bullet::btTriangleIndexVertexArray;
    auto lm_new() -> GameBindings::Bullet::btTriangleIndexVertexArray;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::float_expr, GameBindings::int_expr) -> GameBindings::Bullet::btTriangleIndexVertexArray;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCapsuleShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btCapsuleShape;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btCapsuleShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCylinderShapeZ
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShapeZ;
    auto lm_new(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShapeZ;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btBoxShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btBoxShape;
    auto lm_new(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btBoxShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btGhostObject
{
    ::LM::ExprPtr expr;
    auto getOverlappingObject_nc(GameBindings::int_expr) -> GameBindings::Bullet::btCollisionObject;
    auto tmp() -> GameBindings::Bullet::btGhostObject;
    auto convexSweepTest(MissingType /* C++ btConvexShape const* (end) */ , GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, MissingType /* C++ btCollisionWorld::ConvexResultCallback& (end) */ , GameBindings::float_expr) -> GameBindings::void_expr;
    auto lm_new() -> GameBindings::Bullet::btGhostObject;
    auto getOverlappingObject_c(GameBindings::int_expr) -> GameBindings::Bullet::btCollisionObject;
    auto rayTest(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btCollisionWorld_RayResultCallback) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getNumOverlappingObjects() -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSliderConstraint
{
    ::LM::ExprPtr expr;
    auto getFrameOffsetB_nc() -> GameBindings::Bullet::btTransform;
    auto getFrameOffsetA_nc() -> GameBindings::Bullet::btTransform;
    auto setUpperLinLimit(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setTargetLinMotorVelocity(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setTargetAngMotorVelocity(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setSoftnessOrthoLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setSoftnessLimLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setSoftnessLimAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setSoftnessOrthoAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setSoftnessDirAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setRestitutionDirLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setRestitutionDirAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setPoweredLinMotor(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getFrameOffsetA_c() -> GameBindings::Bullet::btTransform;
    auto setPoweredAngMotor(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setMaxLinMotorForce(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setLowerAngLimit(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setDampingOrthoLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setDampingLimAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setDampingDirAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getUseFrameOffset() -> GameBindings::bool_expr;
    auto getUpperAngLimit() -> GameBindings::float_expr;
    auto getSolveAngLimit() -> GameBindings::bool_expr;
    auto getSoftnessOrthoAng() -> GameBindings::float_expr;
    auto getSoftnessLimAng() -> GameBindings::float_expr;
    auto setLowerLinLimit(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSoftnessDirLin() -> GameBindings::float_expr;
    auto setRestitutionLimAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSoftnessDirAng() -> GameBindings::float_expr;
    auto getUpperLinLimit() -> GameBindings::float_expr;
    auto setSoftnessDirLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getRigidBodyA() -> GameBindings::Bullet::btRigidBody;
    auto getSoftnessOrthoLin() -> GameBindings::float_expr;
    auto getRestitutionLimAng() -> GameBindings::float_expr;
    auto setUpperAngLimit(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getRestitutionLimLin() -> GameBindings::float_expr;
    auto getRestitutionDirAng() -> GameBindings::float_expr;
    auto getPoweredAngMotor() -> GameBindings::bool_expr;
    auto getMaxLinMotorForce() -> GameBindings::float_expr;
    auto getUseLinearReferenceFrameA() -> GameBindings::bool_expr;
    auto getMaxAngMotorForce() -> GameBindings::float_expr;
    auto getRestitutionDirLin() -> GameBindings::float_expr;
    auto getLowerAngLimit() -> GameBindings::float_expr;
    auto getTargetAngMotorVelocity() -> GameBindings::float_expr;
    auto setDampingOrthoAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setRestitutionOrthoLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getLinDepth() -> GameBindings::float_expr;
    auto getDampingLimAng() -> GameBindings::float_expr;
    auto getPoweredLinMotor() -> GameBindings::bool_expr;
    auto setMaxAngMotorForce(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getLinearPos() -> GameBindings::float_expr;
    auto getDampingDirLin() -> GameBindings::float_expr;
    auto getCalculatedTransformB() -> GameBindings::Bullet::btTransform;
    auto getFrameOffsetB_c() -> GameBindings::Bullet::btTransform;
    auto getCalculatedTransformA() -> GameBindings::Bullet::btTransform;
    auto getDampingLimLin() -> GameBindings::float_expr;
    auto getLowerLinLimit() -> GameBindings::float_expr;
    auto getSoftnessLimLin() -> GameBindings::float_expr;
    auto getAngDepth() -> GameBindings::float_expr;
    auto getAncorInB() -> GameBindings::Bullet::btVector3;
    auto getTargetLinMotorVelocity() -> GameBindings::float_expr;
    auto setDampingDirLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSolveLinLimit() -> GameBindings::bool_expr;
    auto getAncorInA() -> GameBindings::Bullet::btVector3;
    auto calculateTransforms(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto setRestitutionLimLin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setUseFrameOffset(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getRestitutionOrthoAng() -> GameBindings::float_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btSliderConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btSliderConstraint;
    auto getDampingOrthoLin() -> GameBindings::float_expr;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btSliderConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btSliderConstraint;
    auto setRestitutionOrthoAng(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getRigidBodyB() -> GameBindings::Bullet::btRigidBody;
    auto getDampingDirAng() -> GameBindings::float_expr;
    auto getRestitutionOrthoLin() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto getDampingOrthoAng() -> GameBindings::float_expr;
    auto setDampingLimLin(GameBindings::float_expr) -> GameBindings::void_expr;
};struct btRigidBodyConstructionInfo
{
    ::LM::ExprPtr expr;
    auto ref_m_additionalAngularDampingFactor() -> GameBindings::float_expr;
    auto get_m_additionalAngularDampingThresholdSqr() -> GameBindings::float_expr;
    auto set_m_additionalAngularDampingFactor(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_additionalAngularDampingThresholdSqr(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_additionalLinearDampingThresholdSqr() -> GameBindings::float_expr;
    auto set_m_additionalLinearDampingThresholdSqr(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_additionalDampingFactor() -> GameBindings::float_expr;
    auto set_m_additionalDampingFactor(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_additionalDamping() -> GameBindings::bool_expr;
    auto set_m_additionalDamping(GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto get_m_additionalDampingFactor() -> GameBindings::float_expr;
    auto ref_m_angularSleepingThreshold() -> GameBindings::float_expr;
    auto set_m_angularSleepingThreshold(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_linearSleepingThreshold(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_restitution() -> GameBindings::float_expr;
    auto get_m_angularSleepingThreshold() -> GameBindings::float_expr;
    auto ref_m_linearSleepingThreshold() -> GameBindings::float_expr;
    auto get_m_restitution() -> GameBindings::float_expr;
    auto get_m_additionalAngularDampingFactor() -> GameBindings::float_expr;
    auto ref_m_friction() -> GameBindings::float_expr;
    auto ref_m_angularDamping() -> GameBindings::float_expr;
    auto get_m_linearDamping() -> GameBindings::float_expr;
    auto set_m_angularDamping(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_linearDamping(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_linearSleepingThreshold() -> GameBindings::float_expr;
    auto get_m_localInertia() -> GameBindings::Bullet::btVector3;
    auto set_m_localInertia(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_startWorldTransform() -> GameBindings::Bullet::btTransform;
    auto ref_m_additionalDamping() -> GameBindings::bool_expr;
    auto get_m_startWorldTransform() -> GameBindings::Bullet::btTransform;
    auto set_m_motionState(GameBindings::Bullet::btMotionState) -> GameBindings::Bullet::btMotionState;
    auto get_m_motionState() -> GameBindings::Bullet::btMotionState;
    auto ref_m_localInertia() -> GameBindings::Bullet::btVector3;
    auto ref_m_mass() -> GameBindings::float_expr;
    auto ref_m_additionalAngularDampingThresholdSqr() -> GameBindings::float_expr;
    auto get_m_mass() -> GameBindings::float_expr;
    auto get_m_collisionShape() -> GameBindings::Bullet::btCollisionShape;
    auto set_m_mass(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_motionState() -> GameBindings::Bullet::btMotionState;
    auto set_m_startWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::Bullet::btTransform;
    auto tmp(GameBindings::float_expr, GameBindings::Bullet::btMotionState, GameBindings::Bullet::btCollisionShape, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btRigidBodyConstructionInfo;
    auto set_m_restitution(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_collisionShape() -> GameBindings::Bullet::btCollisionShape;
    auto set_m_collisionShape(GameBindings::Bullet::btCollisionShape) -> GameBindings::Bullet::btCollisionShape;
    auto set_m_friction(GameBindings::float_expr) -> GameBindings::float_expr;
    auto lm_new(GameBindings::float_expr, GameBindings::Bullet::btMotionState, GameBindings::Bullet::btCollisionShape, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btRigidBodyConstructionInfo;
    auto ref_m_additionalLinearDampingThresholdSqr() -> GameBindings::float_expr;
    auto get_m_friction() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto get_m_angularDamping() -> GameBindings::float_expr;
    auto ref_m_linearDamping() -> GameBindings::float_expr;
};struct btDefaultCollisionConstructionInfo
{
    ::LM::ExprPtr expr;
    auto get_m_useEpaPenetrationAlgorithm() -> GameBindings::int_expr;
    auto set_m_useEpaPenetrationAlgorithm(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_defaultStackAllocatorSize() -> GameBindings::int_expr;
    auto set_m_defaultStackAllocatorSize(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_m_useEpaPenetrationAlgorithm() -> GameBindings::int_expr;
    auto ref_m_defaultMaxCollisionAlgorithmPoolSize() -> GameBindings::int_expr;
    auto set_m_defaultMaxCollisionAlgorithmPoolSize(GameBindings::int_expr) -> GameBindings::int_expr;
    auto set_m_customCollisionAlgorithmMaxElementSize(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_defaultMaxPersistentManifoldPoolSize() -> GameBindings::int_expr;
    auto ref_m_customCollisionAlgorithmMaxElementSize() -> GameBindings::int_expr;
    auto ref_m_defaultMaxPersistentManifoldPoolSize() -> GameBindings::int_expr;
    auto get_m_defaultMaxCollisionAlgorithmPoolSize() -> GameBindings::int_expr;
    auto get_m_stackAlloc() -> MissingType /* C++ btStackAlloc* */ ;
    auto set_m_stackAlloc(MissingType /* C++ btStackAlloc* const& (end) */ ) -> MissingType /* C++ btStackAlloc* */ ;
    auto ref_m_defaultStackAllocatorSize() -> GameBindings::int_expr;
    auto ref_m_stackAlloc() -> MissingType /* C++ btStackAlloc*& */ ;
    auto set_m_defaultMaxPersistentManifoldPoolSize(GameBindings::int_expr) -> GameBindings::int_expr;
    auto tmp() -> GameBindings::Bullet::btDefaultCollisionConstructionInfo;
    auto lm_new() -> GameBindings::Bullet::btDefaultCollisionConstructionInfo;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_m_customCollisionAlgorithmMaxElementSize() -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSoftBodyRigidBodyCollisionConfiguration
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration;
    auto tmp(GameBindings::Bullet::btDefaultCollisionConstructionInfo) -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration;
    auto lm_new() -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration;
    auto lm_new(GameBindings::Bullet::btDefaultCollisionConstructionInfo) -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btDefaultCollisionConfiguration
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::Bullet::btDefaultCollisionConfiguration;
    auto tmp(GameBindings::Bullet::btDefaultCollisionConstructionInfo) -> GameBindings::Bullet::btDefaultCollisionConfiguration;
    auto lm_new() -> GameBindings::Bullet::btDefaultCollisionConfiguration;
    auto lm_new(GameBindings::Bullet::btDefaultCollisionConstructionInfo) -> GameBindings::Bullet::btDefaultCollisionConfiguration;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btBroadphaseInterface
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld_LocalShapeInfo
{
    ::LM::ExprPtr expr;
    auto ref_m_triangleIndex() -> GameBindings::int_expr;
    auto ref_m_shapePart() -> GameBindings::int_expr;
    auto get_m_triangleIndex() -> GameBindings::int_expr;
    auto set_m_shapePart(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_shapePart() -> GameBindings::int_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_m_triangleIndex(GameBindings::int_expr) -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btConcaveShape
{
    ::LM::ExprPtr expr;
    auto processAllTriangles(MissingType /* C++ btTriangleCallback* (end) */ , GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btGeneric6DofSpringConstraint
{
    ::LM::ExprPtr expr;
    auto setEquilibriumPoint() -> GameBindings::void_expr;
    auto setEquilibriumPoint(GameBindings::int_expr) -> GameBindings::void_expr;
    auto setDamping(GameBindings::int_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto enableSpring(GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofSpringConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofSpringConstraint;
    auto setStiffness(GameBindings::int_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct CollisionFilterGroups
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionShape
{
    ::LM::ExprPtr expr;
    auto setUserPointer(GameBindings::void_expr) -> GameBindings::void_expr;
    auto serialize(GameBindings::void_expr, MissingType /* C++ btSerializer* (end) */ ) -> GameBindings::char_expr;
    auto isSoftBody() -> GameBindings::bool_expr;
    auto isPolyhedral() -> GameBindings::bool_expr;
    auto isInfinite() -> GameBindings::bool_expr;
    auto isConvex2d() -> GameBindings::bool_expr;
    auto setLocalScaling(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto isConvex() -> GameBindings::bool_expr;
    auto isConcave() -> GameBindings::bool_expr;
    auto getName() -> GameBindings::char_expr;
    auto getLocalScaling() -> GameBindings::Bullet::btVector3;
    auto getBoundingSphere(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getShapeType() -> GameBindings::int_expr;
    auto getAngularMotionDisc() -> GameBindings::float_expr;
    auto getAabb(GameBindings::Bullet::btTransform, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getMargin() -> GameBindings::float_expr;
    auto calculateTemporalAabb(GameBindings::Bullet::btTransform, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::float_expr, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setMargin(GameBindings::float_expr) -> GameBindings::void_expr;
    auto calculateSerializeBufferSize() -> GameBindings::int_expr;
    auto calculateLocalInertia(GameBindings::float_expr, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getUserPointer() -> GameBindings::void_expr;
    auto isCompound() -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto getContactBreakingThreshold(GameBindings::float_expr) -> GameBindings::float_expr;
};struct btPoint2PointConstraint
{
    ::LM::ExprPtr expr;
    auto updateRHS(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setPivotB(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getPivotInB() -> GameBindings::Bullet::btVector3;
    auto getPivotInA() -> GameBindings::Bullet::btVector3;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btPoint2PointConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btPoint2PointConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btPoint2PointConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btPoint2PointConstraint;
    auto lm_delete() -> GameBindings::void_expr;
    auto setPivotA(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btRigidBody
{
    ::LM::ExprPtr expr;
    auto wantsSleeping() -> GameBindings::bool_expr;
    auto updateInertiaTensor() -> GameBindings::void_expr;
    auto translate(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setSleepingThresholds(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto updateDeactivation(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setLinearVelocity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setInvInertiaDiagLocal(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setLinearFactor(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setGravity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto proceedToTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto isInWorld() -> GameBindings::bool_expr;
    auto getVelocityInLocalPoint(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto getTotalTorque() -> GameBindings::Bullet::btVector3;
    auto getTotalForce() -> GameBindings::Bullet::btVector3;
    auto getOrientation() -> GameBindings::Bullet::btQuaternion;
    auto getLinearVelocity() -> GameBindings::Bullet::btVector3;
    auto getLinearSleepingThreshold() -> GameBindings::float_expr;
    auto getLinearFactor() -> GameBindings::Bullet::btVector3;
    auto getLinearDamping() -> GameBindings::float_expr;
    auto setMassProps(GameBindings::float_expr, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getInvMass() -> GameBindings::float_expr;
    auto getNumConstraintRefs() -> GameBindings::int_expr;
    auto setDamping(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getInvInertiaTensorWorld() -> GameBindings::Bullet::btMatrix3x3;
    auto removeConstraintRef(GameBindings::Bullet::btTypedConstraint) -> GameBindings::void_expr;
    auto getInvInertiaDiagLocal() -> GameBindings::Bullet::btVector3;
    auto getGravity() -> GameBindings::Bullet::btVector3;
    auto saveKinematicState(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getCenterOfMassTransform() -> GameBindings::Bullet::btTransform;
    auto getCenterOfMassPosition() -> GameBindings::Bullet::btVector3;
    auto setAngularVelocity(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getAngularVelocity() -> GameBindings::Bullet::btVector3;
    auto predictIntegratedTransform(GameBindings::float_expr, GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto getAngularDamping() -> GameBindings::float_expr;
    auto computeImpulseDenominator(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto checkCollideWithOverride(GameBindings::Bullet::btCollisionObject) -> GameBindings::bool_expr;
    auto getAngularFactor() -> GameBindings::Bullet::btVector3;
    auto getAabb(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto applyImpulse(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setCenterOfMassTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto applyGravity() -> GameBindings::void_expr;
    auto applyForce(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto applyDamping(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setFlags(GameBindings::int_expr) -> GameBindings::void_expr;
    auto applyTorque(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getConstraintRef(GameBindings::int_expr) -> GameBindings::Bullet::btTypedConstraint;
    auto applyCentralForce(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setMotionState(GameBindings::Bullet::btMotionState) -> GameBindings::void_expr;
    auto setAngularFactorScalar(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getMotionState_nc() -> GameBindings::Bullet::btMotionState;
    auto getFlags() -> GameBindings::int_expr;
    auto clearForces() -> GameBindings::void_expr;
    auto getMotionState_c() -> GameBindings::Bullet::btMotionState;
    auto getBroadphaseProxy_nc() -> MissingType /* C++ btBroadphaseProxy* */ ;
    auto applyCentralImpulse(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto tmp(GameBindings::Bullet::btRigidBodyConstructionInfo) -> GameBindings::Bullet::btRigidBody;
    auto getAngularSleepingThreshold() -> GameBindings::float_expr;
    auto setAngularFactor(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lm_new(GameBindings::Bullet::btRigidBodyConstructionInfo) -> GameBindings::Bullet::btRigidBody;
    auto applyTorqueImpulse(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getBroadphaseProxy_c() -> MissingType /* C++ btBroadphaseProxy const* */ ;
    auto setNewBroadphaseProxy(MissingType /* C++ btBroadphaseProxy* (end) */ ) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto addConstraintRef(GameBindings::Bullet::btTypedConstraint) -> GameBindings::void_expr;
    auto computeAngularImpulseDenominator(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btSphereShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::float_expr) -> GameBindings::Bullet::btSphereShape;
    auto lm_new(GameBindings::float_expr) -> GameBindings::Bullet::btSphereShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btManifoldPoint
{
    ::LM::ExprPtr expr;
    auto ref_m_userPersistentData() -> GameBindings::void_expr;
    auto get_m_userPersistentData() -> GameBindings::void_expr;
    auto set_m_userPersistentData(GameBindings::void_expr) -> GameBindings::void_expr;
    auto ref_m_positionWorldOnB() -> GameBindings::Bullet::btVector3;
    auto get_m_positionWorldOnB() -> GameBindings::Bullet::btVector3;
    auto set_m_positionWorldOnB(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_positionWorldOnA() -> GameBindings::Bullet::btVector3;
    auto set_m_positionWorldOnA(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto get_m_partId1() -> GameBindings::int_expr;
    auto ref_m_partId0() -> GameBindings::int_expr;
    auto get_m_partId0() -> GameBindings::int_expr;
    auto ref_m_partId1() -> GameBindings::int_expr;
    auto set_m_partId0(GameBindings::int_expr) -> GameBindings::int_expr;
    auto set_m_normalWorldOnB(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto get_m_localPointB() -> GameBindings::Bullet::btVector3;
    auto set_m_localPointB(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto get_m_positionWorldOnA() -> GameBindings::Bullet::btVector3;
    auto set_m_partId1(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_m_localPointA() -> GameBindings::Bullet::btVector3;
    auto get_m_localPointA() -> GameBindings::Bullet::btVector3;
    auto set_m_localPointA(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_lifeTime() -> GameBindings::int_expr;
    auto set_m_lifeTime(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_m_lateralFrictionInitialized() -> GameBindings::bool_expr;
    auto set_m_lateralFrictionInitialized(GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto get_m_lateralFrictionDir2() -> GameBindings::Bullet::btVector3;
    auto set_m_lateralFrictionDir2(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto set_m_lateralFrictionDir1(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto set_m_index1(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_m_index0() -> GameBindings::int_expr;
    auto get_m_index0() -> GameBindings::int_expr;
    auto set_m_index0(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_m_distance1() -> GameBindings::float_expr;
    auto ref_m_contactMotion2() -> GameBindings::float_expr;
    auto set_m_contactMotion2(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_m_contactMotion1() -> GameBindings::float_expr;
    auto set_m_distance1(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_contactMotion1() -> GameBindings::float_expr;
    auto ref_m_contactCFM2() -> GameBindings::float_expr;
    auto set_m_contactCFM2(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_contactCFM1() -> GameBindings::float_expr;
    auto get_m_combinedRestitution() -> GameBindings::float_expr;
    auto ref_m_index1() -> GameBindings::int_expr;
    auto ref_m_combinedFriction() -> GameBindings::float_expr;
    auto set_m_combinedFriction(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_contactMotion1(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_appliedImpulseLateral2() -> GameBindings::float_expr;
    auto set_m_combinedRestitution(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_lifeTime() -> GameBindings::int_expr;
    auto ref_m_normalWorldOnB() -> GameBindings::Bullet::btVector3;
    auto set_m_appliedImpulseLateral1(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_combinedFriction() -> GameBindings::float_expr;
    auto ref_m_appliedImpulseLateral1() -> GameBindings::float_expr;
    auto ref_m_contactCFM1() -> GameBindings::float_expr;
    auto ref_m_appliedImpulse() -> GameBindings::float_expr;
    auto get_m_appliedImpulse() -> GameBindings::float_expr;
    auto get_m_index1() -> GameBindings::int_expr;
    auto setDistance(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getPositionWorldOnB() -> GameBindings::Bullet::btVector3;
    auto ref_m_localPointB() -> GameBindings::Bullet::btVector3;
    auto ref_m_combinedRestitution() -> GameBindings::float_expr;
    auto getPositionWorldOnA() -> GameBindings::Bullet::btVector3;
    auto set_m_appliedImpulseLateral2(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_lateralFrictionInitialized() -> GameBindings::bool_expr;
    auto ref_m_lateralFrictionDir1() -> GameBindings::Bullet::btVector3;
    auto getDistance() -> GameBindings::float_expr;
    auto get_m_contactMotion2() -> GameBindings::float_expr;
    auto set_m_contactCFM1(GameBindings::float_expr) -> GameBindings::float_expr;
    auto tmp() -> GameBindings::Bullet::btManifoldPoint;
    auto tmp(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btManifoldPoint;
    auto get_m_lateralFrictionDir1() -> GameBindings::Bullet::btVector3;
    auto get_m_appliedImpulseLateral1() -> GameBindings::float_expr;
    auto get_m_contactCFM2() -> GameBindings::float_expr;
    auto lm_new() -> GameBindings::Bullet::btManifoldPoint;
    auto lm_new(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btManifoldPoint;
    auto set_m_appliedImpulse(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_m_normalWorldOnB() -> GameBindings::Bullet::btVector3;
    auto ref_m_appliedImpulseLateral2() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto ref_m_distance1() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto ref_m_lateralFrictionDir2() -> GameBindings::Bullet::btVector3;
    auto getLifeTime() -> GameBindings::int_expr;
};struct btMotionState
{
    ::LM::ExprPtr expr;
    auto setWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto getWorldTransform(GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCylinderShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShape;
    auto lm_new(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionConfiguration
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btVector3
{
    ::LM::ExprPtr expr;
    auto operator +=(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto z() -> GameBindings::float_expr;
    auto y() -> GameBindings::float_expr;
    auto x() -> GameBindings::float_expr;
    auto w() -> GameBindings::float_expr;
    auto triple(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto setY(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setX(GameBindings::float_expr) -> GameBindings::void_expr;
    auto setValue(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setInterpolate3(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::void_expr;
    auto serializeFloat(MissingType /* C++ btVector3FloatData& (end) */ ) -> GameBindings::void_expr;
    auto rotate(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btVector3;
    auto normalized() -> GameBindings::Bullet::btVector3;
    auto normalize() -> GameBindings::Bullet::btVector3;
    auto setMin(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto lerp(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btVector3;
    auto minAxis() -> GameBindings::int_expr;
    auto length() -> GameBindings::float_expr;
    auto isZero() -> GameBindings::bool_expr;
    auto getY() -> GameBindings::float_expr;
    auto setZero() -> GameBindings::void_expr;
    auto getX() -> GameBindings::float_expr;
    auto setZ(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getSkewSymmetricMatrix(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto dot(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto distance(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto maxAxis() -> GameBindings::int_expr;
    auto deSerializeDouble(MissingType /* C++ btVector3DoubleData const& (end) */ ) -> GameBindings::void_expr;
    auto setMax(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto cross(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto serializeDouble(MissingType /* C++ btVector3DoubleData& (end) */ ) -> GameBindings::void_expr;
    auto furthestAxis() -> GameBindings::int_expr;
    auto closestAxis() -> GameBindings::int_expr;
    auto setW(GameBindings::float_expr) -> GameBindings::void_expr;
    auto angle(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto deSerialize(MissingType /* C++ btVector3FloatData const& (end) */ ) -> GameBindings::void_expr;
    auto distance2(GameBindings::Bullet::btVector3) -> GameBindings::float_expr;
    auto absolute() -> GameBindings::Bullet::btVector3;
    auto length2() -> GameBindings::float_expr;
    auto tmp() -> GameBindings::Bullet::btVector3;
    auto tmp(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btVector3;
    auto fuzzyZero() -> GameBindings::bool_expr;
    auto operator -=(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto lm_new() -> GameBindings::Bullet::btVector3;
    auto lm_new(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btVector3;
    auto deSerializeFloat(MissingType /* C++ btVector3FloatData const& (end) */ ) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getZ() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btGeneric6DofConstraint
{
    ::LM::ExprPtr expr;
    auto getFrameOffsetB_nc() -> GameBindings::Bullet::btTransform;
    auto updateRHS(GameBindings::float_expr) -> GameBindings::void_expr;
    auto calculateTransforms() -> GameBindings::void_expr;
    auto calculateTransforms(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::void_expr;
    auto setUseFrameOffset(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setLinearLowerLimit(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto setLimit(GameBindings::int_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setAngularUpperLimit(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getFrameOffsetA_nc() -> GameBindings::Bullet::btTransform;
    auto getUseFrameOffset() -> GameBindings::bool_expr;
    auto getFrameOffsetA_c() -> GameBindings::Bullet::btTransform;
    auto getRotationalLimitMotor(GameBindings::int_expr) -> GameBindings::Bullet::btRotationalLimitMotor;
    auto setAngularLowerLimit(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto getRelativePivotPosition(GameBindings::int_expr) -> GameBindings::float_expr;
    auto getCalculatedTransformB() -> GameBindings::Bullet::btTransform;
    auto getAxis(GameBindings::int_expr) -> GameBindings::Bullet::btVector3;
    auto setLinearUpperLimit(GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto isLimited(GameBindings::int_expr) -> GameBindings::bool_expr;
    auto get_limit_motor_info2(GameBindings::Bullet::btRotationalLimitMotor, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, MissingType /* C++ btTypedConstraint::btConstraintInfo2* (end) */ , GameBindings::int_expr, GameBindings::Bullet::btVector3, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::int_expr;
    auto getFrameOffsetB_c() -> GameBindings::Bullet::btTransform;
    auto getCalculatedTransformA() -> GameBindings::Bullet::btTransform;
    auto calcAnchorPos() -> GameBindings::void_expr;
    auto getAngle(GameBindings::int_expr) -> GameBindings::float_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofConstraint;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform, GameBindings::bool_expr) -> GameBindings::Bullet::btGeneric6DofConstraint;
    auto lm_delete() -> GameBindings::void_expr;
    auto getTranslationalLimitMotor() -> MissingType /* C++ btTranslationalLimitMotor* */ ;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCollisionWorld_LocalRayResult
{
    ::LM::ExprPtr expr;
    auto ref_m_hitFraction() -> GameBindings::float_expr;
    auto get_m_hitFraction() -> GameBindings::float_expr;
    auto ref_m_hitNormalLocal() -> GameBindings::Bullet::btVector3;
    auto get_m_hitNormalLocal() -> GameBindings::Bullet::btVector3;
    auto set_m_hitNormalLocal(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btVector3;
    auto ref_m_localShapeInfo() -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo;
    auto get_m_localShapeInfo() -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo;
    auto set_m_hitFraction(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_m_localShapeInfo(GameBindings::Bullet::btCollisionWorld_LocalShapeInfo) -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo;
    auto ref_m_collisionObject() -> GameBindings::Bullet::btCollisionObject;
    auto set_m_collisionObject(GameBindings::Bullet::btCollisionObject) -> GameBindings::Bullet::btCollisionObject;
    auto get_m_collisionObject() -> GameBindings::Bullet::btCollisionObject;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btStaticPlaneShape
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btStaticPlaneShape;
    auto lm_new(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btStaticPlaneShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btQuaternion
{
    ::LM::ExprPtr expr;
    auto setRotation(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setEulerZYX(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto normalized() -> GameBindings::Bullet::btQuaternion;
    auto normalize() -> GameBindings::Bullet::btQuaternion;
    auto length() -> GameBindings::float_expr;
    auto getW() -> GameBindings::float_expr;
    auto length2() -> GameBindings::float_expr;
    auto inverse() -> GameBindings::Bullet::btQuaternion;
    auto getAngle() -> GameBindings::float_expr;
    auto dot(GameBindings::Bullet::btQuaternion) -> GameBindings::float_expr;
    auto getAxis() -> GameBindings::Bullet::btVector3;
    auto setEuler(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto angle(GameBindings::Bullet::btQuaternion) -> GameBindings::float_expr;
    auto nearest(GameBindings::Bullet::btQuaternion) -> GameBindings::Bullet::btQuaternion;
    auto slerp(GameBindings::Bullet::btQuaternion, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto farthest(GameBindings::Bullet::btQuaternion) -> GameBindings::Bullet::btQuaternion;
    auto getIdentityQuaternion() -> GameBindings::Bullet::btQuaternion;
    auto tmp() -> GameBindings::Bullet::btQuaternion;
    auto tmp(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto lm_new() -> GameBindings::Bullet::btQuaternion;
    auto lm_new(GameBindings::Bullet::btVector3, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::Bullet::btQuaternion;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btMultimaterialTriangleMeshShape
{
    ::LM::ExprPtr expr;
    auto getMaterialProperties(GameBindings::int_expr, GameBindings::int_expr) -> MissingType /* C++ btMaterial const* */ ;
    auto tmp(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape;
    auto tmp(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape;
    auto lm_new(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape;
    auto lm_new(GameBindings::Bullet::btStridingMeshInterface, GameBindings::bool_expr, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::bool_expr) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct btCylinderShapeX
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShapeX;
    auto lm_new(GameBindings::Bullet::btVector3) -> GameBindings::Bullet::btCylinderShapeX;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
