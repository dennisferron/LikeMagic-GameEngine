#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_Bullet.hpp"

namespace GameBindings
{
	namespace Bullet
	{

auto btSparseSdf_3::Lerp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "Lerp", args, 3) };
}
auto btSparseSdf_3::Decompose(GameBindings::float_expr arg0) -> MissingType /* C++ btSparseSdf<3>::IntFrac */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "Decompose", args, 1) };
}
auto btSparseSdf_3::Evaluate(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btCollisionShape arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "Evaluate", args, 4) };
}
auto btSparseSdf_3::RemoveReferences(GameBindings::Bullet::btCollisionShape arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "RemoveReferences", args, 1) };
}
auto btSparseSdf_3::GarbageCollect(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "GarbageCollect", args, 1) };
}
auto btSparseSdf_3::get_nqueries() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_nqueries", args, 0) };
}
auto btSparseSdf_3::set_nqueries(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_nqueries", args, 1) };
}
auto btSparseSdf_3::get_nprobes() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_nprobes", args, 0) };
}
auto btSparseSdf_3::DistanceToShape(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btCollisionShape arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "DistanceToShape", args, 2) };
}
auto btSparseSdf_3::set_nprobes(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_nprobes", args, 1) };
}
auto btSparseSdf_3::ref_ncells() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_ncells", args, 0) };
}
auto btSparseSdf_3::BuildCell(MissingType /* C++ btSparseSdf<3>::Cell& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "BuildCell", args, 1) };
}
auto btSparseSdf_3::get_ncells() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ncells", args, 0) };
}
auto btSparseSdf_3::ref_puid() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_puid", args, 0) };
}
auto btSparseSdf_3::get_puid() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_puid", args, 0) };
}
auto btSparseSdf_3::Reset() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Reset", args, 0) };
}
auto btSparseSdf_3::set_puid(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_puid", args, 1) };
}
auto btSparseSdf_3::ref_nqueries() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_nqueries", args, 0) };
}
auto btSparseSdf_3::set_voxelsz(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_voxelsz", args, 1) };
}
auto btSparseSdf_3::ref_cells() -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_cells", args, 0) };
}
auto btSparseSdf_3::ref_nprobes() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_nprobes", args, 0) };
}
auto btSparseSdf_3::set_cells(MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_cells", args, 1) };
}
auto btSparseSdf_3::set_ncells(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ncells", args, 1) };
}
auto btSparseSdf_3::ref_voxelsz() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_voxelsz", args, 0) };
}
auto btSparseSdf_3::Initialize(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "Initialize", args, 1) };
}
auto btSparseSdf_3::get_voxelsz() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_voxelsz", args, 0) };
}
auto btSparseSdf_3::tmp() -> GameBindings::Bullet::btSparseSdf_3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btSparseSdf_3::lm_new() -> GameBindings::Bullet::btSparseSdf_3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btSparseSdf_3::get_cells() -> MissingType /* C++ btAlignedObjectArray<btSparseSdf<3>::Cell*> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_cells", args, 0) };
}
auto btSparseSdf_3::Hash(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::Bullet::btCollisionShape arg3) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "Hash", args, 4) };
}
auto btSparseSdf_3::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSparseSdf_3::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btHingeConstraint::getHingeAngle() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHingeAngle", args, 0) };
}
auto btHingeConstraint::getHingeAngle(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getHingeAngle", args, 2) };
}
auto btHingeConstraint::getBFrame_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBFrame_c", args, 0) };
}
auto btHingeConstraint::getAFrame_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAFrame_nc", args, 0) };
}
auto btHingeConstraint::getBFrame_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBFrame_nc", args, 0) };
}
auto btHingeConstraint::getAFrame_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAFrame_c", args, 0) };
}
auto btHingeConstraint::updateRHS(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "updateRHS", args, 1) };
}
auto btHingeConstraint::setUseFrameOffset(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUseFrameOffset", args, 1) };
}
auto btHingeConstraint::setMotorTargetScalarScalar(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMotorTargetScalarScalar", args, 2) };
}
auto btHingeConstraint::setAxis(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAxis", args, 1) };
}
auto btHingeConstraint::getUseFrameOffset() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUseFrameOffset", args, 0) };
}
auto btHingeConstraint::getUpperLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUpperLimit", args, 0) };
}
auto btHingeConstraint::testLimit(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "testLimit", args, 2) };
}
auto btHingeConstraint::setMaxMotorImpulse(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxMotorImpulse", args, 1) };
}
auto btHingeConstraint::getSolveLimit() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolveLimit", args, 0) };
}
auto btHingeConstraint::getMotorTargetVelosity() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMotorTargetVelosity", args, 0) };
}
auto btHingeConstraint::setAngularOnly(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularOnly", args, 1) };
}
auto btHingeConstraint::getMaxMotorImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaxMotorImpulse", args, 0) };
}
auto btHingeConstraint::getLowerLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLowerLimit", args, 0) };
}
auto btHingeConstraint::getLimitSign() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLimitSign", args, 0) };
}
auto btHingeConstraint::setMotorTargetQuatScalar(GameBindings::Bullet::btQuaternion arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMotorTargetQuatScalar", args, 2) };
}
auto btHingeConstraint::getEnableAngularMotor() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getEnableAngularMotor", args, 0) };
}
auto btHingeConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btHingeConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::bool_expr arg3) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btHingeConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btHingeConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::Bullet::btVector3 arg5, GameBindings::bool_expr arg6) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "tmp", args, 7) };
}
auto btHingeConstraint::setLimit(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "setLimit", args, 5) };
}
auto btHingeConstraint::getAngularOnly() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularOnly", args, 0) };
}
auto btHingeConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btHingeConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::bool_expr arg3) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btHingeConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btHingeConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::Bullet::btVector3 arg5, GameBindings::bool_expr arg6) -> GameBindings::Bullet::btHingeConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "new", args, 7) };
}
auto btHingeConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btHingeConstraint::enableAngularMotor(GameBindings::bool_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "enableAngularMotor", args, 3) };
}
auto btHingeConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btHingeConstraint::enableMotor(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "enableMotor", args, 1) };
}

auto btConeTwistConstraint::updateRHS(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "updateRHS", args, 1) };
}
auto btConeTwistConstraint::setMaxMotorImpulse(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxMotorImpulse", args, 1) };
}
auto btConeTwistConstraint::setAngularOnly(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularOnly", args, 1) };
}
auto btConeTwistConstraint::isPastSwingLimit() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isPastSwingLimit", args, 0) };
}
auto btConeTwistConstraint::getTwistSpan() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTwistSpan", args, 0) };
}
auto btConeTwistConstraint::setMotorTargetInConstraintSpace(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMotorTargetInConstraintSpace", args, 1) };
}
auto btConeTwistConstraint::setMaxMotorImpulseNormalized(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxMotorImpulseNormalized", args, 1) };
}
auto btConeTwistConstraint::getTwistAngle() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTwistAngle", args, 0) };
}
auto btConeTwistConstraint::setMotorTarget(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMotorTarget", args, 1) };
}
auto btConeTwistConstraint::getSwingSpan2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSwingSpan2", args, 0) };
}
auto btConeTwistConstraint::getRigidBodyA() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyA", args, 0) };
}
auto btConeTwistConstraint::getFixThresh() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFixThresh", args, 0) };
}
auto btConeTwistConstraint::GetPointForAngle(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "GetPointForAngle", args, 2) };
}
auto btConeTwistConstraint::getTwistLimitSign() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTwistLimitSign", args, 0) };
}
auto btConeTwistConstraint::getBFrame() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBFrame", args, 0) };
}
auto btConeTwistConstraint::setFixThresh(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFixThresh", args, 1) };
}
auto btConeTwistConstraint::getSwingSpan1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSwingSpan1", args, 0) };
}
auto btConeTwistConstraint::getAFrame() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAFrame", args, 0) };
}
auto btConeTwistConstraint::calcAngleInfo2(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1, GameBindings::Bullet::btMatrix3x3 arg2, GameBindings::Bullet::btMatrix3x3 arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "calcAngleInfo2", args, 4) };
}
auto btConeTwistConstraint::setDamping(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDamping", args, 1) };
}
auto btConeTwistConstraint::getSolveSwingLimit() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolveSwingLimit", args, 0) };
}
auto btConeTwistConstraint::calcAngleInfo() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calcAngleInfo", args, 0) };
}
auto btConeTwistConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Bullet::btConeTwistConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btConeTwistConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3) -> GameBindings::Bullet::btConeTwistConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btConeTwistConstraint::setLimit(GameBindings::int_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setLimit", args, 2) };
}
auto btConeTwistConstraint::setLimit(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "setLimit", args, 6) };
}
auto btConeTwistConstraint::getSolveTwistLimit() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolveTwistLimit", args, 0) };
}
auto btConeTwistConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Bullet::btConeTwistConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btConeTwistConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3) -> GameBindings::Bullet::btConeTwistConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btConeTwistConstraint::getRigidBodyB() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyB", args, 0) };
}
auto btConeTwistConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConeTwistConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btConeTwistConstraint::enableMotor(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "enableMotor", args, 1) };
}

auto btTransform::getBasis_c() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBasis_c", args, 0) };
}
auto btTransform::setRotation(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRotation", args, 1) };
}
auto btTransform::setOrigin(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOrigin", args, 1) };
}
auto btTransform::setIdentity() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "setIdentity", args, 0) };
}
auto btTransform::setFromOpenGLMatrix(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFromOpenGLMatrix", args, 1) };
}
auto btTransform::setBasis(GameBindings::Bullet::btMatrix3x3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setBasis", args, 1) };
}
auto btTransform::serialize(MissingType /* C++ btTransformFloatData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serialize", args, 1) };
}
auto btTransform::getOrigin_c() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOrigin_c", args, 0) };
}
auto btTransform::mult(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "mult", args, 2) };
}
auto btTransform::getOrigin_nc() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOrigin_nc", args, 0) };
}
auto btTransform::inverse() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "inverse", args, 0) };
}
auto btTransform::serializeFloat(MissingType /* C++ btTransformFloatData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serializeFloat", args, 1) };
}
auto btTransform::getRotation() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRotation", args, 0) };
}
auto btTransform::tmp() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btTransform::tmp(GameBindings::Bullet::btTransform arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btTransform::tmp(GameBindings::Bullet::btQuaternion arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btTransform::lm_new() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btTransform::lm_new(GameBindings::Bullet::btTransform arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btTransform::lm_new(GameBindings::Bullet::btQuaternion arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btTransform::getIdentityTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIdentityTransform", args, 0) };
}
auto btTransform::getOpenGLMatrix(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getOpenGLMatrix", args, 1) };
}
auto btTransform::inverseTimes(GameBindings::Bullet::btTransform arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "inverseTimes", args, 1) };
}
auto btTransform::getBasis_nc() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBasis_nc", args, 0) };
}
auto btTransform::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTransform::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btTransform::invXform(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "invXform", args, 1) };
}

auto btIndexedMesh::ref_m_vertexType() -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_vertexType", args, 0) };
}
auto btIndexedMesh::ref_m_indexType() -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_indexType", args, 0) };
}
auto btIndexedMesh::get_m_indexType() -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_indexType", args, 0) };
}
auto btIndexedMesh::ref_m_vertexStride() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_vertexStride", args, 0) };
}
auto btIndexedMesh::get_m_vertexStride() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_vertexStride", args, 0) };
}
auto btIndexedMesh::set_m_vertexBase(GameBindings::uchar_expr arg0) -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_vertexBase", args, 1) };
}
auto btIndexedMesh::set_m_numVertices(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_numVertices", args, 1) };
}
auto btIndexedMesh::get_m_vertexBase() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_vertexBase", args, 0) };
}
auto btIndexedMesh::ref_m_triangleIndexStride() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_triangleIndexStride", args, 0) };
}
auto btIndexedMesh::set_m_vertexType(GameBindings::Bullet::PHY_ScalarType arg0) -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_vertexType", args, 1) };
}
auto btIndexedMesh::get_m_triangleIndexStride() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_triangleIndexStride", args, 0) };
}
auto btIndexedMesh::set_m_indexType(GameBindings::Bullet::PHY_ScalarType arg0) -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_indexType", args, 1) };
}
auto btIndexedMesh::get_m_triangleIndexBase() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_triangleIndexBase", args, 0) };
}
auto btIndexedMesh::ref_m_triangleIndexBase() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_triangleIndexBase", args, 0) };
}
auto btIndexedMesh::set_m_triangleIndexStride(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_triangleIndexStride", args, 1) };
}
auto btIndexedMesh::ref_m_vertexBase() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_vertexBase", args, 0) };
}
auto btIndexedMesh::ref_m_numTriangles() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_numTriangles", args, 0) };
}
auto btIndexedMesh::get_m_numVertices() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_numVertices", args, 0) };
}
auto btIndexedMesh::tmp() -> GameBindings::Bullet::btIndexedMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btIndexedMesh::get_m_vertexType() -> GameBindings::Bullet::PHY_ScalarType
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_vertexType", args, 0) };
}
auto btIndexedMesh::lm_new() -> GameBindings::Bullet::btIndexedMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btIndexedMesh::get_m_numTriangles() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_numTriangles", args, 0) };
}
auto btIndexedMesh::ref_m_numVertices() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_numVertices", args, 0) };
}
auto btIndexedMesh::set_m_triangleIndexBase(GameBindings::uchar_expr arg0) -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_triangleIndexBase", args, 1) };
}
auto btIndexedMesh::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btIndexedMesh::set_m_vertexStride(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_vertexStride", args, 1) };
}
auto btIndexedMesh::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btIndexedMesh::set_m_numTriangles(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_numTriangles", args, 1) };
}

auto btStridingMeshInterface::calculateSerializeBufferSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calculateSerializeBufferSize", args, 0) };
}
auto btStridingMeshInterface::setScaling(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setScaling", args, 1) };
}
auto btStridingMeshInterface::getScaling() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getScaling", args, 0) };
}
auto btStridingMeshInterface::getPremadeAabb(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getPremadeAabb", args, 2) };
}
auto btStridingMeshInterface::setPremadeAabb(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPremadeAabb", args, 2) };
}
auto btStridingMeshInterface::preallocateVertices(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "preallocateVertices", args, 1) };
}
auto btStridingMeshInterface::hasPremadeAabb() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "hasPremadeAabb", args, 0) };
}
auto btStridingMeshInterface::unLockReadOnlyVertexBase(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "unLockReadOnlyVertexBase", args, 1) };
}
auto btStridingMeshInterface::getLockedReadOnlyVertexIndexBase(MissingType /* C++ unsigned char const** (end) */  arg0, GameBindings::int_expr arg1, GameBindings::Bullet::PHY_ScalarType arg2, GameBindings::int_expr arg3, MissingType /* C++ unsigned char const** (end) */  arg4, GameBindings::int_expr arg5, GameBindings::int_expr arg6, GameBindings::Bullet::PHY_ScalarType arg7, GameBindings::int_expr arg8) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "getLockedReadOnlyVertexIndexBase", args, 9) };
}
auto btStridingMeshInterface::getLockedVertexIndexBase(MissingType /* C++ unsigned char** (end) */  arg0, GameBindings::int_expr arg1, GameBindings::Bullet::PHY_ScalarType arg2, GameBindings::int_expr arg3, MissingType /* C++ unsigned char** (end) */  arg4, GameBindings::int_expr arg5, GameBindings::int_expr arg6, GameBindings::Bullet::PHY_ScalarType arg7, GameBindings::int_expr arg8) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "getLockedVertexIndexBase", args, 9) };
}
auto btStridingMeshInterface::preallocateIndices(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "preallocateIndices", args, 1) };
}
auto btStridingMeshInterface::serialize(GameBindings::void_expr arg0, MissingType /* C++ btSerializer* (end) */  arg1) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "serialize", args, 2) };
}
auto btStridingMeshInterface::calculateAabbBruteForce(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "calculateAabbBruteForce", args, 2) };
}
auto btStridingMeshInterface::getNumSubParts() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumSubParts", args, 0) };
}
auto btStridingMeshInterface::InternalProcessAllTriangles(MissingType /* C++ btInternalTriangleIndexCallback* (end) */  arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "InternalProcessAllTriangles", args, 3) };
}
auto btStridingMeshInterface::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btStridingMeshInterface::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btStridingMeshInterface::unLockVertexBase(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "unLockVertexBase", args, 1) };
}

auto btTriangleMesh::addIndex(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addIndex", args, 1) };
}
auto btTriangleMesh::addTriangle(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::bool_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "addTriangle", args, 4) };
}
auto btTriangleMesh::getUse4componentVertices() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUse4componentVertices", args, 0) };
}
auto btTriangleMesh::getNumTriangles() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumTriangles", args, 0) };
}
auto btTriangleMesh::getUse32bitIndices() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUse32bitIndices", args, 0) };
}
auto btTriangleMesh::tmp(GameBindings::bool_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::Bullet::btTriangleMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btTriangleMesh::lm_new(GameBindings::bool_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::Bullet::btTriangleMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btTriangleMesh::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTriangleMesh::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionObject::getWorldTransform_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWorldTransform_nc", args, 0) };
}
auto btCollisionObject::getInterpolationWorldTransform_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInterpolationWorldTransform_c", args, 0) };
}
auto btCollisionObject::getCollisionShape_nc() -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCollisionShape_nc", args, 0) };
}
auto btCollisionObject::getBroadphaseHandle_nc() -> MissingType /* C++ btBroadphaseProxy* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBroadphaseHandle_nc", args, 0) };
}
auto btCollisionObject::getBroadphaseHandle_c() -> MissingType /* C++ btBroadphaseProxy const* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBroadphaseHandle_c", args, 0) };
}
auto btCollisionObject::getInterpolationWorldTransform_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInterpolationWorldTransform_nc", args, 0) };
}
auto btCollisionObject::setUserPointer(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUserPointer", args, 1) };
}
auto btCollisionObject::setRestitution(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitution", args, 1) };
}
auto btCollisionObject::setIslandTag(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setIslandTag", args, 1) };
}
auto btCollisionObject::setInterpolationAngularVelocity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInterpolationAngularVelocity", args, 1) };
}
auto btCollisionObject::setHitFraction(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setHitFraction", args, 1) };
}
auto btCollisionObject::getCollisionShape_c() -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCollisionShape_c", args, 0) };
}
auto btCollisionObject::setFriction(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFriction", args, 1) };
}
auto btCollisionObject::setContactProcessingThreshold(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setContactProcessingThreshold", args, 1) };
}
auto btCollisionObject::setCompanionId(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCompanionId", args, 1) };
}
auto btCollisionObject::setWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setWorldTransform", args, 1) };
}
auto btCollisionObject::setAnisotropicFriction(GameBindings::Bullet::btVector3 arg0, GameBindings::int_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setAnisotropicFriction", args, 2) };
}
auto btCollisionObject::serialize(GameBindings::void_expr arg0, MissingType /* C++ btSerializer* (end) */  arg1) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "serialize", args, 2) };
}
auto btCollisionObject::isStaticOrKinematicObject() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isStaticOrKinematicObject", args, 0) };
}
auto btCollisionObject::isStaticObject() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isStaticObject", args, 0) };
}
auto btCollisionObject::getRestitution() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitution", args, 0) };
}
auto btCollisionObject::getIslandTag() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIslandTag", args, 0) };
}
auto btCollisionObject::setCollisionFlags(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCollisionFlags", args, 1) };
}
auto btCollisionObject::getHitFraction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHitFraction", args, 0) };
}
auto btCollisionObject::setActivationState(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setActivationState", args, 1) };
}
auto btCollisionObject::getInterpolationAngularVelocity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInterpolationAngularVelocity", args, 0) };
}
auto btCollisionObject::getFriction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFriction", args, 0) };
}
auto btCollisionObject::getDeactivationTime() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDeactivationTime", args, 0) };
}
auto btCollisionObject::isKinematicObject() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isKinematicObject", args, 0) };
}
auto btCollisionObject::getCollisionFlags() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCollisionFlags", args, 0) };
}
auto btCollisionObject::isActive() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isActive", args, 0) };
}
auto btCollisionObject::getWorldTransform_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWorldTransform_c", args, 0) };
}
auto btCollisionObject::getContactProcessingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getContactProcessingThreshold", args, 0) };
}
auto btCollisionObject::getCompanionId() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCompanionId", args, 0) };
}
auto btCollisionObject::hasAnisotropicFriction(GameBindings::int_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "hasAnisotropicFriction", args, 1) };
}
auto btCollisionObject::setDeactivationTime(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDeactivationTime", args, 1) };
}
auto btCollisionObject::getCcdSquareMotionThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCcdSquareMotionThreshold", args, 0) };
}
auto btCollisionObject::getCcdMotionThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCcdMotionThreshold", args, 0) };
}
auto btCollisionObject::getActivationState() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getActivationState", args, 0) };
}
auto btCollisionObject::forceActivationState(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "forceActivationState", args, 1) };
}
auto btCollisionObject::getCcdSweptSphereRadius() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCcdSweptSphereRadius", args, 0) };
}
auto btCollisionObject::checkCollideWith(GameBindings::Bullet::btCollisionObject arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "checkCollideWith", args, 1) };
}
auto btCollisionObject::setInterpolationLinearVelocity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInterpolationLinearVelocity", args, 1) };
}
auto btCollisionObject::hasContactResponse() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "hasContactResponse", args, 0) };
}
auto btCollisionObject::calculateSerializeBufferSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calculateSerializeBufferSize", args, 0) };
}
auto btCollisionObject::setCcdSweptSphereRadius(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCcdSweptSphereRadius", args, 1) };
}
auto btCollisionObject::setBroadphaseHandle(MissingType /* C++ btBroadphaseProxy* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setBroadphaseHandle", args, 1) };
}
auto btCollisionObject::activate(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "activate", args, 1) };
}
auto btCollisionObject::mergesSimulationIslands() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "mergesSimulationIslands", args, 0) };
}
auto btCollisionObject::getInterpolationLinearVelocity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInterpolationLinearVelocity", args, 0) };
}
auto btCollisionObject::getUserPointer() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUserPointer", args, 0) };
}
auto btCollisionObject::setInterpolationWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInterpolationWorldTransform", args, 1) };
}
auto btCollisionObject::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionObject::setCollisionShape(GameBindings::Bullet::btCollisionShape arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCollisionShape", args, 1) };
}
auto btCollisionObject::setCcdMotionThreshold(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCcdMotionThreshold", args, 1) };
}
auto btCollisionObject::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btPairCachingGhostObject::getOverlappingPairCache() -> MissingType /* C++ btHashedOverlappingPairCache* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOverlappingPairCache", args, 0) };
}
auto btPairCachingGhostObject::tmp() -> GameBindings::Bullet::btPairCachingGhostObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btPairCachingGhostObject::lm_new() -> GameBindings::Bullet::btPairCachingGhostObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btPairCachingGhostObject::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btPairCachingGhostObject::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btIDebugDraw::getDebugMode() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDebugMode", args, 0) };
}
auto btIDebugDraw::setDebugMode(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDebugMode", args, 1) };
}
auto btIDebugDraw::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btIDebugDraw::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btTypedConstraint::getRigidBodyB_c() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyB_c", args, 0) };
}
auto btTypedConstraint::getRigidBodyA_nc() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyA_nc", args, 0) };
}
auto btTypedConstraint::solveConstraintObsolete(MissingType /* C++ btSolverBody& (end) */  arg0, MissingType /* C++ btSolverBody& (end) */  arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "solveConstraintObsolete", args, 3) };
}
auto btTypedConstraint::serialize(GameBindings::void_expr arg0, MissingType /* C++ btSerializer* (end) */  arg1) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "serialize", args, 2) };
}
auto btTypedConstraint::getUserConstraintType() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUserConstraintType", args, 0) };
}
auto btTypedConstraint::getUserConstraintId() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUserConstraintId", args, 0) };
}
auto btTypedConstraint::setDbgDrawSize(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDbgDrawSize", args, 1) };
}
auto btTypedConstraint::getParam(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getParam", args, 2) };
}
auto btTypedConstraint::setUserConstraintType(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUserConstraintType", args, 1) };
}
auto btTypedConstraint::getDbgDrawSize() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDbgDrawSize", args, 0) };
}
auto btTypedConstraint::getConstraintType() -> MissingType /* C++ btTypedConstraintType */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getConstraintType", args, 0) };
}
auto btTypedConstraint::enableFeedback(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "enableFeedback", args, 1) };
}
auto btTypedConstraint::setUserConstraintId(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUserConstraintId", args, 1) };
}
auto btTypedConstraint::getAppliedImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAppliedImpulse", args, 0) };
}
auto btTypedConstraint::calculateSerializeBufferSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calculateSerializeBufferSize", args, 0) };
}
auto btTypedConstraint::getRigidBodyB_nc() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyB_nc", args, 0) };
}
auto btTypedConstraint::getRigidBodyA_c() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyA_c", args, 0) };
}
auto btTypedConstraint::needsFeedback() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "needsFeedback", args, 0) };
}
auto btTypedConstraint::buildJacobian() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "buildJacobian", args, 0) };
}
auto btTypedConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTypedConstraint::getUid() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUid", args, 0) };
}
auto btTypedConstraint::setParam(GameBindings::int_expr arg0, GameBindings::float_expr arg1, GameBindings::int_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setParam", args, 3) };
}
auto btTypedConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedContactResultCallback::tmp(GameBindings::LangBlockExpr arg0, GameBindings::LangBlockExpr arg1) -> GameBindings::Bullet::ScriptedContactResultCallback
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto ScriptedContactResultCallback::lm_new(GameBindings::LangBlockExpr arg0, GameBindings::LangBlockExpr arg1) -> GameBindings::Bullet::ScriptedContactResultCallback
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto ScriptedContactResultCallback::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedContactResultCallback::baseNeedsCollision(MissingType /* C++ btBroadphaseProxy* (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "baseNeedsCollision", args, 1) };
}
auto ScriptedContactResultCallback::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btDbvtBroadphase::tmp() -> GameBindings::Bullet::btDbvtBroadphase
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btDbvtBroadphase::lm_new() -> GameBindings::Bullet::btDbvtBroadphase
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btDbvtBroadphase::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDbvtBroadphase::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btTriangleMeshShape::getMeshInterface_nc() -> GameBindings::Bullet::btStridingMeshInterface
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMeshInterface_nc", args, 0) };
}
auto btTriangleMeshShape::getLocalAabbMax() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLocalAabbMax", args, 0) };
}
auto btTriangleMeshShape::getLocalAabbMin() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLocalAabbMin", args, 0) };
}
auto btTriangleMeshShape::recalcLocalAabb() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "recalcLocalAabb", args, 0) };
}
auto btTriangleMeshShape::localGetSupportingVertexWithoutMargin(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "localGetSupportingVertexWithoutMargin", args, 1) };
}
auto btTriangleMeshShape::localGetSupportingVertex(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "localGetSupportingVertex", args, 1) };
}
auto btTriangleMeshShape::getMeshInterface_c() -> GameBindings::Bullet::btStridingMeshInterface
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMeshInterface_c", args, 0) };
}
auto btTriangleMeshShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTriangleMeshShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btRotationalLimitMotor::ref_m_stopERP() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_stopERP", args, 0) };
}
auto btRotationalLimitMotor::set_m_stopERP(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_stopERP", args, 1) };
}
auto btRotationalLimitMotor::ref_m_stopCFM() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_stopCFM", args, 0) };
}
auto btRotationalLimitMotor::ref_m_maxMotorForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_maxMotorForce", args, 0) };
}
auto btRotationalLimitMotor::set_m_maxMotorForce(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_maxMotorForce", args, 1) };
}
auto btRotationalLimitMotor::get_m_normalCFM() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_normalCFM", args, 0) };
}
auto btRotationalLimitMotor::ref_m_maxLimitForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_maxLimitForce", args, 0) };
}
auto btRotationalLimitMotor::ref_m_targetVelocity() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_targetVelocity", args, 0) };
}
auto btRotationalLimitMotor::get_m_stopCFM() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_stopCFM", args, 0) };
}
auto btRotationalLimitMotor::ref_m_loLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_loLimit", args, 0) };
}
auto btRotationalLimitMotor::ref_m_limitSoftness() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_limitSoftness", args, 0) };
}
auto btRotationalLimitMotor::set_m_limitSoftness(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_limitSoftness", args, 1) };
}
auto btRotationalLimitMotor::ref_m_hiLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_hiLimit", args, 0) };
}
auto btRotationalLimitMotor::ref_m_normalCFM() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_normalCFM", args, 0) };
}
auto btRotationalLimitMotor::set_m_normalCFM(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_normalCFM", args, 1) };
}
auto btRotationalLimitMotor::set_m_hiLimit(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_hiLimit", args, 1) };
}
auto btRotationalLimitMotor::get_m_limitSoftness() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_limitSoftness", args, 0) };
}
auto btRotationalLimitMotor::set_m_enableMotor(GameBindings::bool_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_enableMotor", args, 1) };
}
auto btRotationalLimitMotor::set_m_damping(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_damping", args, 1) };
}
auto btRotationalLimitMotor::get_m_currentPosition() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_currentPosition", args, 0) };
}
auto btRotationalLimitMotor::ref_m_currentLimitError() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_currentLimitError", args, 0) };
}
auto btRotationalLimitMotor::get_m_currentLimitError() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_currentLimitError", args, 0) };
}
auto btRotationalLimitMotor::set_m_currentLimitError(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_currentLimitError", args, 1) };
}
auto btRotationalLimitMotor::ref_m_damping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_damping", args, 0) };
}
auto btRotationalLimitMotor::ref_m_currentLimit() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_currentLimit", args, 0) };
}
auto btRotationalLimitMotor::get_m_maxMotorForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_maxMotorForce", args, 0) };
}
auto btRotationalLimitMotor::set_m_maxLimitForce(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_maxLimitForce", args, 1) };
}
auto btRotationalLimitMotor::set_m_currentPosition(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_currentPosition", args, 1) };
}
auto btRotationalLimitMotor::set_m_currentLimit(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_currentLimit", args, 1) };
}
auto btRotationalLimitMotor::get_m_stopERP() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_stopERP", args, 0) };
}
auto btRotationalLimitMotor::ref_m_bounce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_bounce", args, 0) };
}
auto btRotationalLimitMotor::ref_m_currentPosition() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_currentPosition", args, 0) };
}
auto btRotationalLimitMotor::get_m_bounce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_bounce", args, 0) };
}
auto btRotationalLimitMotor::get_m_maxLimitForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_maxLimitForce", args, 0) };
}
auto btRotationalLimitMotor::get_m_loLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_loLimit", args, 0) };
}
auto btRotationalLimitMotor::set_m_bounce(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_bounce", args, 1) };
}
auto btRotationalLimitMotor::ref_m_enableMotor() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_enableMotor", args, 0) };
}
auto btRotationalLimitMotor::testLimitValue(GameBindings::float_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "testLimitValue", args, 1) };
}
auto btRotationalLimitMotor::solveAngularLimits(GameBindings::float_expr arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::float_expr arg2, GameBindings::Bullet::btRigidBody arg3, GameBindings::Bullet::btRigidBody arg4) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "solveAngularLimits", args, 5) };
}
auto btRotationalLimitMotor::get_m_enableMotor() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_enableMotor", args, 0) };
}
auto btRotationalLimitMotor::get_m_targetVelocity() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_targetVelocity", args, 0) };
}
auto btRotationalLimitMotor::needApplyTorques() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "needApplyTorques", args, 0) };
}
auto btRotationalLimitMotor::set_m_accumulatedImpulse(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_accumulatedImpulse", args, 1) };
}
auto btRotationalLimitMotor::isLimited() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isLimited", args, 0) };
}
auto btRotationalLimitMotor::tmp() -> GameBindings::Bullet::btRotationalLimitMotor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btRotationalLimitMotor::lm_new() -> GameBindings::Bullet::btRotationalLimitMotor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btRotationalLimitMotor::get_m_hiLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_hiLimit", args, 0) };
}
auto btRotationalLimitMotor::get_m_accumulatedImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_accumulatedImpulse", args, 0) };
}
auto btRotationalLimitMotor::set_m_targetVelocity(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_targetVelocity", args, 1) };
}
auto btRotationalLimitMotor::set_m_loLimit(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_loLimit", args, 1) };
}
auto btRotationalLimitMotor::ref_m_accumulatedImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_accumulatedImpulse", args, 0) };
}
auto btRotationalLimitMotor::set_m_stopCFM(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_stopCFM", args, 1) };
}
auto btRotationalLimitMotor::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btRotationalLimitMotor::get_m_damping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_damping", args, 0) };
}
auto btRotationalLimitMotor::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btRotationalLimitMotor::get_m_currentLimit() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_currentLimit", args, 0) };
}

auto btDispatcher::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDispatcher::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btTypedObject::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTypedObject::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionDispatcher::tmp(GameBindings::Bullet::btCollisionConfiguration arg0) -> GameBindings::Bullet::btCollisionDispatcher
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btCollisionDispatcher::lm_new(GameBindings::Bullet::btCollisionConfiguration arg0) -> GameBindings::Bullet::btCollisionDispatcher
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btCollisionDispatcher::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionDispatcher::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftBodyHelpers::CreateFromTetGenData(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::char_expr arg1, GameBindings::char_expr arg2, GameBindings::char_expr arg3, GameBindings::bool_expr arg4, GameBindings::bool_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "CreateFromTetGenData", args, 7) };
}
auto btSoftBodyHelpers::CreateEllipsoid(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::int_expr arg3) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "CreateEllipsoid", args, 4) };
}
auto btSoftBodyHelpers::DrawFrame(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "DrawFrame", args, 2) };
}
auto btSoftBodyHelpers::DrawFaceTree(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "DrawFaceTree", args, 4) };
}
auto btSoftBodyHelpers::CreatePatch(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::int_expr arg5, GameBindings::int_expr arg6, GameBindings::int_expr arg7, GameBindings::bool_expr arg8) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "CreatePatch", args, 9) };
}
auto btSoftBodyHelpers::DrawClusterTree(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "DrawClusterTree", args, 4) };
}
auto btSoftBodyHelpers::DrawNodeTree(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "DrawNodeTree", args, 4) };
}
auto btSoftBodyHelpers::CreatePatchUV(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::int_expr arg5, GameBindings::int_expr arg6, GameBindings::int_expr arg7, GameBindings::bool_expr arg8, GameBindings::float_expr arg9) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr }; 
    return { ::LM::call(expr, "CreatePatchUV", args, 10) };
}
auto btSoftBodyHelpers::DrawInfos(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1, GameBindings::bool_expr arg2, GameBindings::bool_expr arg3, GameBindings::bool_expr arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "DrawInfos", args, 5) };
}
auto btSoftBodyHelpers::CalculateUV(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3, GameBindings::int_expr arg4) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "CalculateUV", args, 5) };
}
auto btSoftBodyHelpers::CreateRope(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::int_expr arg3, GameBindings::int_expr arg4) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "CreateRope", args, 5) };
}
auto btSoftBodyHelpers::Draw(GameBindings::Bullet::btSoftBody arg0, GameBindings::Bullet::btIDebugDraw arg1, GameBindings::int_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "Draw", args, 3) };
}
auto btSoftBodyHelpers::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftBodyHelpers::CreateFromConvexHull(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::int_expr arg2, GameBindings::bool_expr arg3) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "CreateFromConvexHull", args, 4) };
}
auto btSoftBodyHelpers::CreateFromTriMesh(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::float_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "CreateFromTriMesh", args, 5) };
}
auto btSoftBodyHelpers::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftBodyWorldInfo::get_m_sparsesdf() -> GameBindings::Bullet::btSparseSdf_3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_sparsesdf", args, 0) };
}
auto btSoftBodyWorldInfo::get_m_gravity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_gravity", args, 0) };
}
auto btSoftBodyWorldInfo::get_m_dispatcher() -> GameBindings::Bullet::btDispatcher
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_dispatcher", args, 0) };
}
auto btSoftBodyWorldInfo::ref_m_broadphase() -> GameBindings::Bullet::btBroadphaseInterface
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_broadphase", args, 0) };
}
auto btSoftBodyWorldInfo::get_m_broadphase() -> GameBindings::Bullet::btBroadphaseInterface
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_broadphase", args, 0) };
}
auto btSoftBodyWorldInfo::set_m_gravity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_gravity", args, 1) };
}
auto btSoftBodyWorldInfo::set_m_broadphase(GameBindings::Bullet::btBroadphaseInterface arg0) -> GameBindings::Bullet::btBroadphaseInterface
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_broadphase", args, 1) };
}
auto btSoftBodyWorldInfo::set_water_normal(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_water_normal", args, 1) };
}
auto btSoftBodyWorldInfo::ref_m_gravity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_gravity", args, 0) };
}
auto btSoftBodyWorldInfo::ref_water_offset() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_water_offset", args, 0) };
}
auto btSoftBodyWorldInfo::get_water_density() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_water_density", args, 0) };
}
auto btSoftBodyWorldInfo::ref_air_density() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_air_density", args, 0) };
}
auto btSoftBodyWorldInfo::get_water_offset() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_water_offset", args, 0) };
}
auto btSoftBodyWorldInfo::get_water_normal() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_water_normal", args, 0) };
}
auto btSoftBodyWorldInfo::ref_water_normal() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_water_normal", args, 0) };
}
auto btSoftBodyWorldInfo::ref_m_sparsesdf() -> GameBindings::Bullet::btSparseSdf_3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_sparsesdf", args, 0) };
}
auto btSoftBodyWorldInfo::tmp() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btSoftBodyWorldInfo::get_air_density() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_air_density", args, 0) };
}
auto btSoftBodyWorldInfo::ref_water_density() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_water_density", args, 0) };
}
auto btSoftBodyWorldInfo::set_m_sparsesdf(GameBindings::Bullet::btSparseSdf_3 arg0) -> GameBindings::Bullet::btSparseSdf_3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_sparsesdf", args, 1) };
}
auto btSoftBodyWorldInfo::set_air_density(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_air_density", args, 1) };
}
auto btSoftBodyWorldInfo::set_m_dispatcher(GameBindings::Bullet::btDispatcher arg0) -> GameBindings::Bullet::btDispatcher
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_dispatcher", args, 1) };
}
auto btSoftBodyWorldInfo::lm_new() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btSoftBodyWorldInfo::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftBodyWorldInfo::set_water_offset(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_water_offset", args, 1) };
}
auto btSoftBodyWorldInfo::ref_m_dispatcher() -> GameBindings::Bullet::btDispatcher
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_dispatcher", args, 0) };
}
auto btSoftBodyWorldInfo::set_water_density(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_water_density", args, 1) };
}
auto btSoftBodyWorldInfo::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftBody_Config::ref_m_dsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_dsequence", args, 0) };
}
auto btSoftBody_Config::get_m_psequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_psequence", args, 0) };
}
auto btSoftBody_Config::set_m_psequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_psequence", args, 1) };
}
auto btSoftBody_Config::ref_m_vsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_vsequence", args, 0) };
}
auto btSoftBody_Config::get_m_vsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_vsequence", args, 0) };
}
auto btSoftBody_Config::ref_collisions() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_collisions", args, 0) };
}
auto btSoftBody_Config::ref_citerations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_citerations", args, 0) };
}
auto btSoftBody_Config::set_citerations(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_citerations", args, 1) };
}
auto btSoftBody_Config::ref_diterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_diterations", args, 0) };
}
auto btSoftBody_Config::get_diterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_diterations", args, 0) };
}
auto btSoftBody_Config::set_diterations(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_diterations", args, 1) };
}
auto btSoftBody_Config::ref_piterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_piterations", args, 0) };
}
auto btSoftBody_Config::ref_viterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_viterations", args, 0) };
}
auto btSoftBody_Config::set_viterations(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_viterations", args, 1) };
}
auto btSoftBody_Config::ref_timescale() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_timescale", args, 0) };
}
auto btSoftBody_Config::get_timescale() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_timescale", args, 0) };
}
auto btSoftBody_Config::get_maxvolume() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_maxvolume", args, 0) };
}
auto btSoftBody_Config::set_maxvolume(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_maxvolume", args, 1) };
}
auto btSoftBody_Config::ref_kSK_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSK_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::set_kSR_SPLT_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSR_SPLT_CL", args, 1) };
}
auto btSoftBody_Config::get_kSSHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSSHR_CL", args, 0) };
}
auto btSoftBody_Config::get_piterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_piterations", args, 0) };
}
auto btSoftBody_Config::set_kSSHR_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSSHR_CL", args, 1) };
}
auto btSoftBody_Config::ref_kSKHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSKHR_CL", args, 0) };
}
auto btSoftBody_Config::ref_m_psequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_psequence", args, 0) };
}
auto btSoftBody_Config::get_kSKHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSKHR_CL", args, 0) };
}
auto btSoftBody_Config::ref_kSRHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSRHR_CL", args, 0) };
}
auto btSoftBody_Config::get_kSRHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSRHR_CL", args, 0) };
}
auto btSoftBody_Config::ref_kAHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kAHR", args, 0) };
}
auto btSoftBody_Config::get_kAHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kAHR", args, 0) };
}
auto btSoftBody_Config::set_kAHR(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kAHR", args, 1) };
}
auto btSoftBody_Config::set_kSK_SPLT_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSK_SPLT_CL", args, 1) };
}
auto btSoftBody_Config::set_kSHR(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSHR", args, 1) };
}
auto btSoftBody_Config::ref_kSR_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSR_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::set_kKHR(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kKHR", args, 1) };
}
auto btSoftBody_Config::ref_kMT() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kMT", args, 0) };
}
auto btSoftBody_Config::set_collisions(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_collisions", args, 1) };
}
auto btSoftBody_Config::get_kDF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kDF", args, 0) };
}
auto btSoftBody_Config::get_kSS_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSS_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::get_collisions() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_collisions", args, 0) };
}
auto btSoftBody_Config::set_kCHR(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kCHR", args, 1) };
}
auto btSoftBody_Config::set_m_dsequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_dsequence", args, 1) };
}
auto btSoftBody_Config::get_kSHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSHR", args, 0) };
}
auto btSoftBody_Config::set_kDF(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kDF", args, 1) };
}
auto btSoftBody_Config::ref_kVC() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kVC", args, 0) };
}
auto btSoftBody_Config::get_kSR_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSR_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::ref_kPR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kPR", args, 0) };
}
auto btSoftBody_Config::get_kVC() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kVC", args, 0) };
}
auto btSoftBody_Config::get_kPR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kPR", args, 0) };
}
auto btSoftBody_Config::get_kCHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kCHR", args, 0) };
}
auto btSoftBody_Config::get_citerations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_citerations", args, 0) };
}
auto btSoftBody_Config::get_kMT() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kMT", args, 0) };
}
auto btSoftBody_Config::ref_kSHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSHR", args, 0) };
}
auto btSoftBody_Config::set_kPR(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kPR", args, 1) };
}
auto btSoftBody_Config::ref_kDG() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kDG", args, 0) };
}
auto btSoftBody_Config::ref_maxvolume() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_maxvolume", args, 0) };
}
auto btSoftBody_Config::set_kVC(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kVC", args, 1) };
}
auto btSoftBody_Config::get_kLF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kLF", args, 0) };
}
auto btSoftBody_Config::set_kSRHR_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSRHR_CL", args, 1) };
}
auto btSoftBody_Config::set_kDP(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kDP", args, 1) };
}
auto btSoftBody_Config::ref_kDP() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kDP", args, 0) };
}
auto btSoftBody_Config::get_kSK_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kSK_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::get_kKHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kKHR", args, 0) };
}
auto btSoftBody_Config::get_m_dsequence() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::ePSolver::_> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_dsequence", args, 0) };
}
auto btSoftBody_Config::ref_kLF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kLF", args, 0) };
}
auto btSoftBody_Config::get_kDG() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kDG", args, 0) };
}
auto btSoftBody_Config::set_m_vsequence(MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::eVSolver::_> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_vsequence", args, 1) };
}
auto btSoftBody_Config::set_timescale(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_timescale", args, 1) };
}
auto btSoftBody_Config::ref_kVCF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kVCF", args, 0) };
}
auto btSoftBody_Config::ref_kKHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kKHR", args, 0) };
}
auto btSoftBody_Config::get_kDP() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kDP", args, 0) };
}
auto btSoftBody_Config::get_kVCF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_kVCF", args, 0) };
}
auto btSoftBody_Config::ref_kDF() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kDF", args, 0) };
}
auto btSoftBody_Config::ref_kSSHR_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSSHR_CL", args, 0) };
}
auto btSoftBody_Config::set_kMT(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kMT", args, 1) };
}
auto btSoftBody_Config::ref_kSS_SPLT_CL() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kSS_SPLT_CL", args, 0) };
}
auto btSoftBody_Config::set_kDG(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kDG", args, 1) };
}
auto btSoftBody_Config::ref_aeromodel() -> MissingType /* C++ btSoftBody::eAeroModel::_& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_aeromodel", args, 0) };
}
auto btSoftBody_Config::set_kVCF(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kVCF", args, 1) };
}
auto btSoftBody_Config::set_kSKHR_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSKHR_CL", args, 1) };
}
auto btSoftBody_Config::get_aeromodel() -> MissingType /* C++ btSoftBody::eAeroModel::_ */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_aeromodel", args, 0) };
}
auto btSoftBody_Config::set_aeromodel(MissingType /* C++ btSoftBody::eAeroModel::_ const& (end) */  arg0) -> MissingType /* C++ btSoftBody::eAeroModel::_ */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_aeromodel", args, 1) };
}
auto btSoftBody_Config::set_kSS_SPLT_CL(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kSS_SPLT_CL", args, 1) };
}
auto btSoftBody_Config::ref_kCHR() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_kCHR", args, 0) };
}
auto btSoftBody_Config::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftBody_Config::set_piterations(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_piterations", args, 1) };
}
auto btSoftBody_Config::get_viterations() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_viterations", args, 0) };
}
auto btSoftBody_Config::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btSoftBody_Config::set_kLF(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_kLF", args, 1) };
}

auto btConstraintSolver::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConstraintSolver::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto PHY_ScalarType::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto PHY_ScalarType::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto PHY_ScalarType::operator ==(GameBindings::Bullet::PHY_ScalarType arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto PHY_ScalarType::operator !=(GameBindings::Bullet::PHY_ScalarType arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto PHY_ScalarType::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto PHY_ScalarType::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btBvhTriangleMeshShape::usesQuantizedAabbCompression() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "usesQuantizedAabbCompression", args, 0) };
}
auto btBvhTriangleMeshShape::buildOptimizedBvh() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "buildOptimizedBvh", args, 0) };
}
auto btBvhTriangleMeshShape::setOptimizedBvh(MissingType /* C++ btOptimizedBvh* (end) */  arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setOptimizedBvh", args, 2) };
}
auto btBvhTriangleMeshShape::getOptimizedBvh() -> MissingType /* C++ btOptimizedBvh* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOptimizedBvh", args, 0) };
}
auto btBvhTriangleMeshShape::refitTree(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "refitTree", args, 2) };
}
auto btBvhTriangleMeshShape::performRaycast(MissingType /* C++ btTriangleCallback* (end) */  arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "performRaycast", args, 3) };
}
auto btBvhTriangleMeshShape::getOwnsBvh() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOwnsBvh", args, 0) };
}
auto btBvhTriangleMeshShape::performConvexcast(MissingType /* C++ btTriangleCallback* (end) */  arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "performConvexcast", args, 5) };
}
auto btBvhTriangleMeshShape::tmp(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btBvhTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btBvhTriangleMeshShape::tmp(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btBvhTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btBvhTriangleMeshShape::partialRefitTree(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "partialRefitTree", args, 2) };
}
auto btBvhTriangleMeshShape::lm_new(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btBvhTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btBvhTriangleMeshShape::lm_new(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btBvhTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btBvhTriangleMeshShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btBvhTriangleMeshShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSequentialImpulseConstraintSolver::tmp() -> GameBindings::Bullet::btSequentialImpulseConstraintSolver
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btSequentialImpulseConstraintSolver::lm_new() -> GameBindings::Bullet::btSequentialImpulseConstraintSolver
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btSequentialImpulseConstraintSolver::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSequentialImpulseConstraintSolver::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btDefaultMotionState::tmp(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Bullet::btDefaultMotionState
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btDefaultMotionState::lm_new(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Bullet::btDefaultMotionState
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btDefaultMotionState::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDefaultMotionState::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btHeightfieldTerrainShape::setUseDiamondSubdivision(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUseDiamondSubdivision", args, 1) };
}
auto btHeightfieldTerrainShape::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::void_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::int_expr arg6, GameBindings::Bullet::PHY_ScalarType arg7, GameBindings::bool_expr arg8) -> GameBindings::Bullet::btHeightfieldTerrainShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "tmp", args, 9) };
}
auto btHeightfieldTerrainShape::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::void_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::int_expr arg6, GameBindings::Bullet::PHY_ScalarType arg7, GameBindings::bool_expr arg8) -> GameBindings::Bullet::btHeightfieldTerrainShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "new", args, 9) };
}
auto btHeightfieldTerrainShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btHeightfieldTerrainShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftRigidDynamicsWorld::getSoftBodyArray_nc() -> MissingType /* C++ btAlignedObjectArray<btSoftBody*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftBodyArray_nc", args, 0) };
}
auto btSoftRigidDynamicsWorld::getWorldInfo_c() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWorldInfo_c", args, 0) };
}
auto btSoftRigidDynamicsWorld::rayTestSingle(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1, GameBindings::Bullet::btCollisionObject arg2, GameBindings::Bullet::btCollisionShape arg3, GameBindings::Bullet::btTransform arg4, GameBindings::Bullet::btCollisionWorld_RayResultCallback arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "rayTestSingle", args, 6) };
}
auto btSoftRigidDynamicsWorld::setDrawFlags(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDrawFlags", args, 1) };
}
auto btSoftRigidDynamicsWorld::getDrawFlags() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDrawFlags", args, 0) };
}
auto btSoftRigidDynamicsWorld::addSoftBody(GameBindings::Bullet::btSoftBody arg0, GameBindings::short_expr arg1, GameBindings::short_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "addSoftBody", args, 3) };
}
auto btSoftRigidDynamicsWorld::getWorldInfo_nc() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWorldInfo_nc", args, 0) };
}
auto btSoftRigidDynamicsWorld::tmp(GameBindings::Bullet::btDispatcher arg0, GameBindings::Bullet::btBroadphaseInterface arg1, GameBindings::Bullet::btConstraintSolver arg2, GameBindings::Bullet::btCollisionConfiguration arg3) -> GameBindings::Bullet::btSoftRigidDynamicsWorld
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btSoftRigidDynamicsWorld::removeSoftBody(GameBindings::Bullet::btSoftBody arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeSoftBody", args, 1) };
}
auto btSoftRigidDynamicsWorld::lm_new(GameBindings::Bullet::btDispatcher arg0, GameBindings::Bullet::btBroadphaseInterface arg1, GameBindings::Bullet::btConstraintSolver arg2, GameBindings::Bullet::btCollisionConfiguration arg3) -> GameBindings::Bullet::btSoftRigidDynamicsWorld
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btSoftRigidDynamicsWorld::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftRigidDynamicsWorld::getSoftBodyArray_c() -> MissingType /* C++ btAlignedObjectArray<btSoftBody*> const& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftBodyArray_c", args, 0) };
}
auto btSoftRigidDynamicsWorld::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld_ContactResultCallback::needsCollision(MissingType /* C++ btBroadphaseProxy* (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "needsCollision", args, 1) };
}
auto btCollisionWorld_ContactResultCallback::get_m_collisionFilterMask() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionFilterMask", args, 0) };
}
auto btCollisionWorld_ContactResultCallback::get_m_collisionFilterGroup() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionFilterGroup", args, 0) };
}
auto btCollisionWorld_ContactResultCallback::addSingleResult(GameBindings::Bullet::btManifoldPoint arg0, MissingType /* C++ btCollisionObjectWrapper const* (end) */  arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3, MissingType /* C++ btCollisionObjectWrapper const* (end) */  arg4, GameBindings::int_expr arg5, GameBindings::int_expr arg6) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addSingleResult", args, 7) };
}
auto btCollisionWorld_ContactResultCallback::set_m_collisionFilterMask(GameBindings::short_expr arg0) -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionFilterMask", args, 1) };
}
auto btCollisionWorld_ContactResultCallback::ref_m_collisionFilterGroup() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionFilterGroup", args, 0) };
}
auto btCollisionWorld_ContactResultCallback::set_m_collisionFilterGroup(GameBindings::short_expr arg0) -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionFilterGroup", args, 1) };
}
auto btCollisionWorld_ContactResultCallback::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld_ContactResultCallback::ref_m_collisionFilterMask() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionFilterMask", args, 0) };
}
auto btCollisionWorld_ContactResultCallback::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedClosestRayResultCallback::test_equals(GameBindings::Bullet::btCollisionObject arg0, GameBindings::Bullet::btCollisionObject arg1) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "test_equals", args, 2) };
}
auto ScriptedClosestRayResultCallback::baseAddSingleResult(GameBindings::Bullet::btCollisionWorld_LocalRayResult arg0, GameBindings::bool_expr arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "baseAddSingleResult", args, 2) };
}
auto ScriptedClosestRayResultCallback::tmp(GameBindings::LangBlockExpr arg0) -> GameBindings::Bullet::ScriptedClosestRayResultCallback
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto ScriptedClosestRayResultCallback::lm_new(GameBindings::LangBlockExpr arg0) -> GameBindings::Bullet::ScriptedClosestRayResultCallback
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto ScriptedClosestRayResultCallback::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedClosestRayResultCallback::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld_ClosestRayResultCallback::set_m_hitPointWorld(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_hitPointWorld", args, 1) };
}
auto btCollisionWorld_ClosestRayResultCallback::ref_m_hitPointWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_hitPointWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::get_m_hitNormalWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_hitNormalWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::get_m_hitPointWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_hitPointWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::set_m_hitNormalWorld(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_hitNormalWorld", args, 1) };
}
auto btCollisionWorld_ClosestRayResultCallback::ref_m_hitNormalWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_hitNormalWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::ref_m_rayToWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_rayToWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::set_m_rayToWorld(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_rayToWorld", args, 1) };
}
auto btCollisionWorld_ClosestRayResultCallback::ref_m_rayFromWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_rayFromWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::get_m_rayFromWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_rayFromWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::set_m_rayFromWorld(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_rayFromWorld", args, 1) };
}
auto btCollisionWorld_ClosestRayResultCallback::get_m_rayToWorld() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_rayToWorld", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld_ClosestRayResultCallback::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto DebugDrawModes::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto DebugDrawModes::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld_RayResultCallback::ref_m_flags() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_flags", args, 0) };
}
auto btCollisionWorld_RayResultCallback::get_m_flags() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_flags", args, 0) };
}
auto btCollisionWorld_RayResultCallback::ref_m_collisionFilterMask() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionFilterMask", args, 0) };
}
auto btCollisionWorld_RayResultCallback::set_m_flags(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_flags", args, 1) };
}
auto btCollisionWorld_RayResultCallback::get_m_collisionFilterMask() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionFilterMask", args, 0) };
}
auto btCollisionWorld_RayResultCallback::get_m_collisionFilterGroup() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionFilterGroup", args, 0) };
}
auto btCollisionWorld_RayResultCallback::ref_m_collisionObject() -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionObject", args, 0) };
}
auto btCollisionWorld_RayResultCallback::set_m_closestHitFraction(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_closestHitFraction", args, 1) };
}
auto btCollisionWorld_RayResultCallback::set_m_collisionObject(GameBindings::Bullet::btCollisionObject arg0) -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionObject", args, 1) };
}
auto btCollisionWorld_RayResultCallback::needsCollision(MissingType /* C++ btBroadphaseProxy* (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "needsCollision", args, 1) };
}
auto btCollisionWorld_RayResultCallback::hasHit() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "hasHit", args, 0) };
}
auto btCollisionWorld_RayResultCallback::get_m_closestHitFraction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_closestHitFraction", args, 0) };
}
auto btCollisionWorld_RayResultCallback::set_m_collisionFilterGroup(GameBindings::short_expr arg0) -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionFilterGroup", args, 1) };
}
auto btCollisionWorld_RayResultCallback::ref_m_collisionFilterGroup() -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionFilterGroup", args, 0) };
}
auto btCollisionWorld_RayResultCallback::set_m_collisionFilterMask(GameBindings::short_expr arg0) -> GameBindings::short_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionFilterMask", args, 1) };
}
auto btCollisionWorld_RayResultCallback::addSingleResult(GameBindings::Bullet::btCollisionWorld_LocalRayResult arg0, GameBindings::bool_expr arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addSingleResult", args, 2) };
}
auto btCollisionWorld_RayResultCallback::ref_m_closestHitFraction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_closestHitFraction", args, 0) };
}
auto btCollisionWorld_RayResultCallback::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld_RayResultCallback::get_m_collisionObject() -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionObject", args, 0) };
}
auto btCollisionWorld_RayResultCallback::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftBody::ref_m_bounds(MissingType /* C++ unsigned long long (end) */  arg0) -> MissingType /* C++ btVector3 []& */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "ref_m_bounds", args, 1) };
}
auto btSoftBody::get_m_bounds(MissingType /* C++ unsigned long long (end) */  arg0) -> MissingType /* C++ btVector3 [] */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_m_bounds", args, 1) };
}
auto btSoftBody::set_m_bounds(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "set_m_bounds", args, 2) };
}
auto btSoftBody::ref_m_userIndexMapping() -> MissingType /* C++ btAlignedObjectArray<int>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_userIndexMapping", args, 0) };
}
auto btSoftBody::get_m_userIndexMapping() -> MissingType /* C++ btAlignedObjectArray<int> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_userIndexMapping", args, 0) };
}
auto btSoftBody::get_m_initialWorldTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_initialWorldTransform", args, 0) };
}
auto btSoftBody::set_m_initialWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_initialWorldTransform", args, 1) };
}
auto btSoftBody::ref_m_clusterConnectivity() -> MissingType /* C++ btAlignedObjectArray<bool>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_clusterConnectivity", args, 0) };
}
auto btSoftBody::get_m_clusterConnectivity() -> MissingType /* C++ btAlignedObjectArray<bool> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_clusterConnectivity", args, 0) };
}
auto btSoftBody::set_m_clusterConnectivity(MissingType /* C++ btAlignedObjectArray<bool> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<bool> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_clusterConnectivity", args, 1) };
}
auto btSoftBody::ref_m_bUpdateRtCst() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_bUpdateRtCst", args, 0) };
}
auto btSoftBody::set_m_bUpdateRtCst(GameBindings::bool_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_bUpdateRtCst", args, 1) };
}
auto btSoftBody::ref_m_timeacc() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_timeacc", args, 0) };
}
auto btSoftBody::get_m_timeacc() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_timeacc", args, 0) };
}
auto btSoftBody::set_m_materials(MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_materials", args, 1) };
}
auto btSoftBody::ref_m_joints() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_joints", args, 0) };
}
auto btSoftBody::set_m_joints(MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_joints", args, 1) };
}
auto btSoftBody::ref_m_rcontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_rcontacts", args, 0) };
}
auto btSoftBody::get_m_clusters() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_clusters", args, 0) };
}
auto btSoftBody::ref_m_anchors() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_anchors", args, 0) };
}
auto btSoftBody::set_m_anchors(MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_anchors", args, 1) };
}
auto btSoftBody::ref_m_scontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_scontacts", args, 0) };
}
auto btSoftBody::set_m_tetras(MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_tetras", args, 1) };
}
auto btSoftBody::get_m_faces() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_faces", args, 0) };
}
auto btSoftBody::get_m_nodes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_nodes", args, 0) };
}
auto btSoftBody::get_m_notes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_notes", args, 0) };
}
auto btSoftBody::set_m_notes(MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_notes", args, 1) };
}
auto btSoftBody::set_m_scontacts(MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_scontacts", args, 1) };
}
auto btSoftBody::set_m_timeacc(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_timeacc", args, 1) };
}
auto btSoftBody::set_m_worldInfo(GameBindings::Bullet::btSoftBodyWorldInfo arg0) -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_worldInfo", args, 1) };
}
auto btSoftBody::set_m_nodes(MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_nodes", args, 1) };
}
auto btSoftBody::set_m_clusters(MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_clusters", args, 1) };
}
auto btSoftBody::ref_m_tag() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_tag", args, 0) };
}
auto btSoftBody::get_m_materials() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_materials", args, 0) };
}
auto btSoftBody::ref_m_worldInfo() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_worldInfo", args, 0) };
}
auto btSoftBody::get_m_tag() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_tag", args, 0) };
}
auto btSoftBody::get_m_scontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::SContact> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_scontacts", args, 0) };
}
auto btSoftBody::get_m_rcontacts() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_rcontacts", args, 0) };
}
auto btSoftBody::ref_m_pose() -> MissingType /* C++ btSoftBody::Pose& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_pose", args, 0) };
}
auto btSoftBody::get_m_bUpdateRtCst() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_bUpdateRtCst", args, 0) };
}
auto btSoftBody::ref_m_nodes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Node>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_nodes", args, 0) };
}
auto btSoftBody::ref_m_clusters() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Cluster*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_clusters", args, 0) };
}
auto btSoftBody::ref_m_sst() -> MissingType /* C++ btSoftBody::SolverState& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_sst", args, 0) };
}
auto btSoftBody::get_m_sst() -> MissingType /* C++ btSoftBody::SolverState */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_sst", args, 0) };
}
auto btSoftBody::get_m_tetras() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_tetras", args, 0) };
}
auto btSoftBody::set_m_tag(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_tag", args, 1) };
}
auto btSoftBody::set_m_rcontacts(MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::RContact> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_rcontacts", args, 1) };
}
auto btSoftBody::set_m_sst(MissingType /* C++ btSoftBody::SolverState const& (end) */  arg0) -> MissingType /* C++ btSoftBody::SolverState */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_sst", args, 1) };
}
auto btSoftBody::set_m_cfg(GameBindings::Bullet::btSoftBody_Config arg0) -> GameBindings::Bullet::btSoftBody_Config
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_cfg", args, 1) };
}
auto btSoftBody::set_m_links(MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_links", args, 1) };
}
auto btSoftBody::rotate(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "rotate", args, 1) };
}
auto btSoftBody::get_m_cfg() -> GameBindings::Bullet::btSoftBody_Config
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_cfg", args, 0) };
}
auto btSoftBody::get_m_collisionDisabledObjects() -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionDisabledObjects", args, 0) };
}
auto btSoftBody::ref_m_links() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_links", args, 0) };
}
auto btSoftBody::transform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "transform", args, 1) };
}
auto btSoftBody::ref_m_notes() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Note>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_notes", args, 0) };
}
auto btSoftBody::tmp(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::int_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btSoftBody::ref_m_collisionDisabledObjects() -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionDisabledObjects", args, 0) };
}
auto btSoftBody::translate(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "translate", args, 1) };
}
auto btSoftBody::set_m_pose(MissingType /* C++ btSoftBody::Pose const& (end) */  arg0) -> MissingType /* C++ btSoftBody::Pose */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_pose", args, 1) };
}
auto btSoftBody::ref_m_cfg() -> GameBindings::Bullet::btSoftBody_Config
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_cfg", args, 0) };
}
auto btSoftBody::ref_m_tetras() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Tetra>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_tetras", args, 0) };
}
auto btSoftBody::lm_new(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::int_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btSoftBody::ref_m_faces() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_faces", args, 0) };
}
auto btSoftBody::set_m_userIndexMapping(MissingType /* C++ btAlignedObjectArray<int> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<int> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_userIndexMapping", args, 1) };
}
auto btSoftBody::set_m_collisionDisabledObjects(MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btCollisionObject const*> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionDisabledObjects", args, 1) };
}
auto btSoftBody::get_m_worldInfo() -> GameBindings::Bullet::btSoftBodyWorldInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_worldInfo", args, 0) };
}
auto btSoftBody::ref_m_materials() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Material*>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_materials", args, 0) };
}
auto btSoftBody::get_m_anchors() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Anchor> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_anchors", args, 0) };
}
auto btSoftBody::ref_m_initialWorldTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_initialWorldTransform", args, 0) };
}
auto btSoftBody::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftBody::get_m_links() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Link> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_links", args, 0) };
}
auto btSoftBody::get_m_joints() -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Joint*> */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_joints", args, 0) };
}
auto btSoftBody::get_m_pose() -> MissingType /* C++ btSoftBody::Pose */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_pose", args, 0) };
}
auto btSoftBody::set_m_faces(MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> const& (end) */  arg0) -> MissingType /* C++ btAlignedObjectArray<btSoftBody::Face> */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_faces", args, 1) };
}
auto btSoftBody::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btDynamicsWorld::setWorldUserInfo(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setWorldUserInfo", args, 1) };
}
auto btDynamicsWorld::setConstraintSolver(GameBindings::Bullet::btConstraintSolver arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setConstraintSolver", args, 1) };
}
auto btDynamicsWorld::removeVehicle(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeVehicle", args, 1) };
}
auto btDynamicsWorld::removeRigidBody(GameBindings::Bullet::btRigidBody arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeRigidBody", args, 1) };
}
auto btDynamicsWorld::synchronizeMotionStates() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "synchronizeMotionStates", args, 0) };
}
auto btDynamicsWorld::getWorldType() -> MissingType /* C++ btDynamicsWorldType */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWorldType", args, 0) };
}
auto btDynamicsWorld::getSolverInfo() -> MissingType /* C++ btContactSolverInfo& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolverInfo", args, 0) };
}
auto btDynamicsWorld::setInternalTickCallback(MissingType /* C++ void (btDynamicsWorld*, float)* (end) */  arg0, GameBindings::void_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setInternalTickCallback", args, 3) };
}
auto btDynamicsWorld::getNumConstraints() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumConstraints", args, 0) };
}
auto btDynamicsWorld::removeCharacter(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeCharacter", args, 1) };
}
auto btDynamicsWorld::getConstraintSolver() -> GameBindings::Bullet::btConstraintSolver
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getConstraintSolver", args, 0) };
}
auto btDynamicsWorld::clearForces() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clearForces", args, 0) };
}
auto btDynamicsWorld::getGravity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getGravity", args, 0) };
}
auto btDynamicsWorld::removeAction(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeAction", args, 1) };
}
auto btDynamicsWorld::addAction(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addAction", args, 1) };
}
auto btDynamicsWorld::addVehicle(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addVehicle", args, 1) };
}
auto btDynamicsWorld::setGravity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setGravity", args, 1) };
}
auto btDynamicsWorld::debugDrawWorld() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "debugDrawWorld", args, 0) };
}
auto btDynamicsWorld::addCharacter(MissingType /* C++ btActionInterface* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addCharacter", args, 1) };
}
auto btDynamicsWorld::removeConstraint(GameBindings::Bullet::btTypedConstraint arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeConstraint", args, 1) };
}
auto btDynamicsWorld::addRigidBody(GameBindings::Bullet::btRigidBody arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addRigidBody", args, 1) };
}
auto btDynamicsWorld::addRigidBody(GameBindings::Bullet::btRigidBody arg0, GameBindings::short_expr arg1, GameBindings::short_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "addRigidBody", args, 3) };
}
auto btDynamicsWorld::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDynamicsWorld::stepSimulation(GameBindings::float_expr arg0, GameBindings::int_expr arg1, GameBindings::float_expr arg2) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "stepSimulation", args, 3) };
}
auto btDynamicsWorld::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btDynamicsWorld::addConstraint(GameBindings::Bullet::btTypedConstraint arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addConstraint", args, 2) };
}

auto btCompoundShape::getChildTransform_c(GameBindings::int_expr arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getChildTransform_c", args, 1) };
}
auto btCompoundShape::getChildTransform_nc(GameBindings::int_expr arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getChildTransform_nc", args, 1) };
}
auto btCompoundShape::updateChildTransform(GameBindings::int_expr arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "updateChildTransform", args, 3) };
}
auto btCompoundShape::removeChildShapeByIndex(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeChildShapeByIndex", args, 1) };
}
auto btCompoundShape::removeChildShape(GameBindings::Bullet::btCollisionShape arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeChildShape", args, 1) };
}
auto btCompoundShape::getUpdateRevision() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUpdateRevision", args, 0) };
}
auto btCompoundShape::getNumChildShapes() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumChildShapes", args, 0) };
}
auto btCompoundShape::getDynamicAabbTree_nc() -> MissingType /* C++ btDbvt* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDynamicAabbTree_nc", args, 0) };
}
auto btCompoundShape::getChildList() -> MissingType /* C++ btCompoundShapeChild* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getChildList", args, 0) };
}
auto btCompoundShape::addChildShape(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btCollisionShape arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addChildShape", args, 2) };
}
auto btCompoundShape::getDynamicAabbTree_c() -> MissingType /* C++ btDbvt const* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDynamicAabbTree_c", args, 0) };
}
auto btCompoundShape::getChildShape_nc(GameBindings::int_expr arg0) -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getChildShape_nc", args, 1) };
}
auto btCompoundShape::tmp(GameBindings::bool_expr arg0) -> GameBindings::Bullet::btCompoundShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btCompoundShape::getChildShape_c(GameBindings::int_expr arg0) -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getChildShape_c", args, 1) };
}
auto btCompoundShape::recalculateLocalAabb() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "recalculateLocalAabb", args, 0) };
}
auto btCompoundShape::lm_new(GameBindings::bool_expr arg0) -> GameBindings::Bullet::btCompoundShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btCompoundShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCompoundShape::calculatePrincipalAxisTransform(GameBindings::float_expr arg0, GameBindings::Bullet::btTransform arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "calculatePrincipalAxisTransform", args, 3) };
}
auto btCompoundShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btDiscreteDynamicsWorld::tmp(GameBindings::Bullet::btDispatcher arg0, GameBindings::Bullet::btBroadphaseInterface arg1, GameBindings::Bullet::btConstraintSolver arg2, GameBindings::Bullet::btCollisionConfiguration arg3) -> GameBindings::Bullet::btDiscreteDynamicsWorld
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btDiscreteDynamicsWorld::lm_new(GameBindings::Bullet::btDispatcher arg0, GameBindings::Bullet::btBroadphaseInterface arg1, GameBindings::Bullet::btConstraintSolver arg2, GameBindings::Bullet::btCollisionConfiguration arg3) -> GameBindings::Bullet::btDiscreteDynamicsWorld
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btDiscreteDynamicsWorld::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDiscreteDynamicsWorld::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld::getDebugDrawer() -> GameBindings::Bullet::btIDebugDraw
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDebugDrawer", args, 0) };
}
auto btCollisionWorld::setDebugDrawer(GameBindings::Bullet::btIDebugDraw arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDebugDrawer", args, 1) };
}
auto btCollisionWorld::contactTest(GameBindings::Bullet::btCollisionObject arg0, GameBindings::Bullet::btCollisionWorld_ContactResultCallback arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "contactTest", args, 2) };
}
auto btCollisionWorld::rayTest(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btCollisionWorld_RayResultCallback arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "rayTest", args, 3) };
}
auto btCollisionWorld::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btConeShapeZ::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShapeZ
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btConeShapeZ::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShapeZ
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btConeShapeZ::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConeShapeZ::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedWorldManager::setOnTick(GameBindings::Bullet::btDynamicsWorld arg0, GameBindings::LangBlockExpr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setOnTick", args, 2) };
}
auto ScriptedWorldManager::tmp() -> GameBindings::Bullet::ScriptedWorldManager
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ScriptedWorldManager::lm_new() -> GameBindings::Bullet::ScriptedWorldManager
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ScriptedWorldManager::setOnPreTick(GameBindings::Bullet::btDynamicsWorld arg0, GameBindings::LangBlockExpr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setOnPreTick", args, 2) };
}
auto ScriptedWorldManager::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedWorldManager::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btMatrix3x3::transposeTimes(GameBindings::Bullet::btMatrix3x3 arg0) -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "transposeTimes", args, 1) };
}
auto btMatrix3x3::transpose() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "transpose", args, 0) };
}
auto btMatrix3x3::tdotx(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tdotx", args, 1) };
}
auto btMatrix3x3::setIdentity() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "setIdentity", args, 0) };
}
auto btMatrix3x3::setValue(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::float_expr arg6, GameBindings::float_expr arg7, GameBindings::float_expr arg8) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "setValue", args, 9) };
}
auto btMatrix3x3::setEulerZYX(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setEulerZYX", args, 3) };
}
auto btMatrix3x3::setFromOpenGLSubMatrix(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFromOpenGLSubMatrix", args, 1) };
}
auto btMatrix3x3::serialize(MissingType /* C++ btMatrix3x3FloatData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serialize", args, 1) };
}
auto btMatrix3x3::scaled(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "scaled", args, 1) };
}
auto btMatrix3x3::serializeFloat(MissingType /* C++ btMatrix3x3FloatData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serializeFloat", args, 1) };
}
auto btMatrix3x3::inverse() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "inverse", args, 0) };
}
auto btMatrix3x3::getRow(GameBindings::int_expr arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getRow", args, 1) };
}
auto btMatrix3x3::tdoty(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tdoty", args, 1) };
}
auto btMatrix3x3::getRotation(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getRotation", args, 1) };
}
auto btMatrix3x3::getEulerZYX(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "getEulerZYX", args, 4) };
}
auto btMatrix3x3::tdotz(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tdotz", args, 1) };
}
auto btMatrix3x3::getEulerYPR(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getEulerYPR", args, 3) };
}
auto btMatrix3x3::deSerialize(MissingType /* C++ btMatrix3x3FloatData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerialize", args, 1) };
}
auto btMatrix3x3::getOpenGLSubMatrix(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getOpenGLSubMatrix", args, 1) };
}
auto btMatrix3x3::getColumn(GameBindings::int_expr arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getColumn", args, 1) };
}
auto btMatrix3x3::adjoint() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "adjoint", args, 0) };
}
auto btMatrix3x3::deSerializeDouble(MissingType /* C++ btMatrix3x3DoubleData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerializeDouble", args, 1) };
}
auto btMatrix3x3::absolute() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "absolute", args, 0) };
}
auto btMatrix3x3::getIdentityMatrix() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIdentityMatrix", args, 0) };
}
auto btMatrix3x3::diagonalize(GameBindings::Bullet::btMatrix3x3 arg0, GameBindings::float_expr arg1, GameBindings::int_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "diagonalize", args, 3) };
}
auto btMatrix3x3::timesTranspose(GameBindings::Bullet::btMatrix3x3 arg0) -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "timesTranspose", args, 1) };
}
auto btMatrix3x3::tmp() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btMatrix3x3::lm_new() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btMatrix3x3::determinant() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "determinant", args, 0) };
}
auto btMatrix3x3::setEulerYPR(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setEulerYPR", args, 3) };
}
auto btMatrix3x3::cofac(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "cofac", args, 4) };
}
auto btMatrix3x3::deSerializeFloat(MissingType /* C++ btMatrix3x3FloatData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerializeFloat", args, 1) };
}
auto btMatrix3x3::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btMatrix3x3::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btConeShapeX::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShapeX
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btConeShapeX::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShapeX
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btConeShapeX::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConeShapeX::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btConeShape::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btConeShape::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btConeShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btConeShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConeShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btTriangleIndexVertexArray::getIndexedMeshArray_nc() -> MissingType /* C++ btAlignedObjectArray<btIndexedMesh>& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndexedMeshArray_nc", args, 0) };
}
auto btTriangleIndexVertexArray::addIndexedMesh(GameBindings::Bullet::btIndexedMesh arg0, GameBindings::Bullet::PHY_ScalarType arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addIndexedMesh", args, 2) };
}
auto btTriangleIndexVertexArray::getIndexedMeshArray_c() -> MissingType /* C++ btAlignedObjectArray<btIndexedMesh> const& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndexedMeshArray_c", args, 0) };
}
auto btTriangleIndexVertexArray::tmp() -> GameBindings::Bullet::btTriangleIndexVertexArray
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btTriangleIndexVertexArray::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3, GameBindings::float_expr arg4, GameBindings::int_expr arg5) -> GameBindings::Bullet::btTriangleIndexVertexArray
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "tmp", args, 6) };
}
auto btTriangleIndexVertexArray::lm_new() -> GameBindings::Bullet::btTriangleIndexVertexArray
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btTriangleIndexVertexArray::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3, GameBindings::float_expr arg4, GameBindings::int_expr arg5) -> GameBindings::Bullet::btTriangleIndexVertexArray
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "new", args, 6) };
}
auto btTriangleIndexVertexArray::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btTriangleIndexVertexArray::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCapsuleShape::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btCapsuleShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btCapsuleShape::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btCapsuleShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btCapsuleShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCapsuleShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCylinderShapeZ::tmp(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShapeZ
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btCylinderShapeZ::lm_new(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShapeZ
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btCylinderShapeZ::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCylinderShapeZ::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btBoxShape::tmp(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btBoxShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btBoxShape::lm_new(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btBoxShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btBoxShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btBoxShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btGhostObject::getOverlappingObject_nc(GameBindings::int_expr arg0) -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getOverlappingObject_nc", args, 1) };
}
auto btGhostObject::tmp() -> GameBindings::Bullet::btGhostObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btGhostObject::convexSweepTest(MissingType /* C++ btConvexShape const* (end) */  arg0, GameBindings::Bullet::btTransform arg1, GameBindings::Bullet::btTransform arg2, MissingType /* C++ btCollisionWorld::ConvexResultCallback& (end) */  arg3, GameBindings::float_expr arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "convexSweepTest", args, 5) };
}
auto btGhostObject::lm_new() -> GameBindings::Bullet::btGhostObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btGhostObject::getOverlappingObject_c(GameBindings::int_expr arg0) -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getOverlappingObject_c", args, 1) };
}
auto btGhostObject::rayTest(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btCollisionWorld_RayResultCallback arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "rayTest", args, 3) };
}
auto btGhostObject::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btGhostObject::getNumOverlappingObjects() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumOverlappingObjects", args, 0) };
}
auto btGhostObject::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSliderConstraint::getFrameOffsetB_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetB_nc", args, 0) };
}
auto btSliderConstraint::getFrameOffsetA_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetA_nc", args, 0) };
}
auto btSliderConstraint::setUpperLinLimit(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUpperLinLimit", args, 1) };
}
auto btSliderConstraint::setTargetLinMotorVelocity(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setTargetLinMotorVelocity", args, 1) };
}
auto btSliderConstraint::setTargetAngMotorVelocity(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setTargetAngMotorVelocity", args, 1) };
}
auto btSliderConstraint::setSoftnessOrthoLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessOrthoLin", args, 1) };
}
auto btSliderConstraint::setSoftnessLimLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessLimLin", args, 1) };
}
auto btSliderConstraint::setSoftnessLimAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessLimAng", args, 1) };
}
auto btSliderConstraint::setSoftnessOrthoAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessOrthoAng", args, 1) };
}
auto btSliderConstraint::setSoftnessDirAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessDirAng", args, 1) };
}
auto btSliderConstraint::setRestitutionDirLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionDirLin", args, 1) };
}
auto btSliderConstraint::setRestitutionDirAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionDirAng", args, 1) };
}
auto btSliderConstraint::setPoweredLinMotor(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPoweredLinMotor", args, 1) };
}
auto btSliderConstraint::getFrameOffsetA_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetA_c", args, 0) };
}
auto btSliderConstraint::setPoweredAngMotor(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPoweredAngMotor", args, 1) };
}
auto btSliderConstraint::setMaxLinMotorForce(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxLinMotorForce", args, 1) };
}
auto btSliderConstraint::setLowerAngLimit(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLowerAngLimit", args, 1) };
}
auto btSliderConstraint::setDampingOrthoLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingOrthoLin", args, 1) };
}
auto btSliderConstraint::setDampingLimAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingLimAng", args, 1) };
}
auto btSliderConstraint::setDampingDirAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingDirAng", args, 1) };
}
auto btSliderConstraint::getUseFrameOffset() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUseFrameOffset", args, 0) };
}
auto btSliderConstraint::getUpperAngLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUpperAngLimit", args, 0) };
}
auto btSliderConstraint::getSolveAngLimit() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolveAngLimit", args, 0) };
}
auto btSliderConstraint::getSoftnessOrthoAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessOrthoAng", args, 0) };
}
auto btSliderConstraint::getSoftnessLimAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessLimAng", args, 0) };
}
auto btSliderConstraint::setLowerLinLimit(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLowerLinLimit", args, 1) };
}
auto btSliderConstraint::getSoftnessDirLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessDirLin", args, 0) };
}
auto btSliderConstraint::setRestitutionLimAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionLimAng", args, 1) };
}
auto btSliderConstraint::getSoftnessDirAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessDirAng", args, 0) };
}
auto btSliderConstraint::getUpperLinLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUpperLinLimit", args, 0) };
}
auto btSliderConstraint::setSoftnessDirLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setSoftnessDirLin", args, 1) };
}
auto btSliderConstraint::getRigidBodyA() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyA", args, 0) };
}
auto btSliderConstraint::getSoftnessOrthoLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessOrthoLin", args, 0) };
}
auto btSliderConstraint::getRestitutionLimAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionLimAng", args, 0) };
}
auto btSliderConstraint::setUpperAngLimit(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUpperAngLimit", args, 1) };
}
auto btSliderConstraint::getRestitutionLimLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionLimLin", args, 0) };
}
auto btSliderConstraint::getRestitutionDirAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionDirAng", args, 0) };
}
auto btSliderConstraint::getPoweredAngMotor() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPoweredAngMotor", args, 0) };
}
auto btSliderConstraint::getMaxLinMotorForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaxLinMotorForce", args, 0) };
}
auto btSliderConstraint::getUseLinearReferenceFrameA() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUseLinearReferenceFrameA", args, 0) };
}
auto btSliderConstraint::getMaxAngMotorForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaxAngMotorForce", args, 0) };
}
auto btSliderConstraint::getRestitutionDirLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionDirLin", args, 0) };
}
auto btSliderConstraint::getLowerAngLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLowerAngLimit", args, 0) };
}
auto btSliderConstraint::getTargetAngMotorVelocity() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTargetAngMotorVelocity", args, 0) };
}
auto btSliderConstraint::setDampingOrthoAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingOrthoAng", args, 1) };
}
auto btSliderConstraint::setRestitutionOrthoLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionOrthoLin", args, 1) };
}
auto btSliderConstraint::getLinDepth() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinDepth", args, 0) };
}
auto btSliderConstraint::getDampingLimAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingLimAng", args, 0) };
}
auto btSliderConstraint::getPoweredLinMotor() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPoweredLinMotor", args, 0) };
}
auto btSliderConstraint::setMaxAngMotorForce(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaxAngMotorForce", args, 1) };
}
auto btSliderConstraint::getLinearPos() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinearPos", args, 0) };
}
auto btSliderConstraint::getDampingDirLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingDirLin", args, 0) };
}
auto btSliderConstraint::getCalculatedTransformB() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCalculatedTransformB", args, 0) };
}
auto btSliderConstraint::getFrameOffsetB_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetB_c", args, 0) };
}
auto btSliderConstraint::getCalculatedTransformA() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCalculatedTransformA", args, 0) };
}
auto btSliderConstraint::getDampingLimLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingLimLin", args, 0) };
}
auto btSliderConstraint::getLowerLinLimit() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLowerLinLimit", args, 0) };
}
auto btSliderConstraint::getSoftnessLimLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSoftnessLimLin", args, 0) };
}
auto btSliderConstraint::getAngDepth() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngDepth", args, 0) };
}
auto btSliderConstraint::getAncorInB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAncorInB", args, 0) };
}
auto btSliderConstraint::getTargetLinMotorVelocity() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTargetLinMotorVelocity", args, 0) };
}
auto btSliderConstraint::setDampingDirLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingDirLin", args, 1) };
}
auto btSliderConstraint::getSolveLinLimit() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSolveLinLimit", args, 0) };
}
auto btSliderConstraint::getAncorInA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAncorInA", args, 0) };
}
auto btSliderConstraint::calculateTransforms(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "calculateTransforms", args, 2) };
}
auto btSliderConstraint::setRestitutionLimLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionLimLin", args, 1) };
}
auto btSliderConstraint::setUseFrameOffset(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUseFrameOffset", args, 1) };
}
auto btSliderConstraint::getRestitutionOrthoAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionOrthoAng", args, 0) };
}
auto btSliderConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btSliderConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btSliderConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btSliderConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btSliderConstraint::getDampingOrthoLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingOrthoLin", args, 0) };
}
auto btSliderConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btSliderConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btSliderConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btSliderConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btSliderConstraint::setRestitutionOrthoAng(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRestitutionOrthoAng", args, 1) };
}
auto btSliderConstraint::getRigidBodyB() -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRigidBodyB", args, 0) };
}
auto btSliderConstraint::getDampingDirAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingDirAng", args, 0) };
}
auto btSliderConstraint::getRestitutionOrthoLin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRestitutionOrthoLin", args, 0) };
}
auto btSliderConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSliderConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btSliderConstraint::getDampingOrthoAng() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDampingOrthoAng", args, 0) };
}
auto btSliderConstraint::setDampingLimLin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDampingLimLin", args, 1) };
}

auto btRigidBodyConstructionInfo::ref_m_additionalAngularDampingFactor() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_additionalAngularDampingFactor", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_additionalAngularDampingThresholdSqr() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_additionalAngularDampingThresholdSqr", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_additionalAngularDampingFactor(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_additionalAngularDampingFactor", args, 1) };
}
auto btRigidBodyConstructionInfo::set_m_additionalAngularDampingThresholdSqr(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_additionalAngularDampingThresholdSqr", args, 1) };
}
auto btRigidBodyConstructionInfo::get_m_additionalLinearDampingThresholdSqr() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_additionalLinearDampingThresholdSqr", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_additionalLinearDampingThresholdSqr(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_additionalLinearDampingThresholdSqr", args, 1) };
}
auto btRigidBodyConstructionInfo::ref_m_additionalDampingFactor() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_additionalDampingFactor", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_additionalDampingFactor(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_additionalDampingFactor", args, 1) };
}
auto btRigidBodyConstructionInfo::get_m_additionalDamping() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_additionalDamping", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_additionalDamping(GameBindings::bool_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_additionalDamping", args, 1) };
}
auto btRigidBodyConstructionInfo::get_m_additionalDampingFactor() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_additionalDampingFactor", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_angularSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_angularSleepingThreshold", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_angularSleepingThreshold(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_angularSleepingThreshold", args, 1) };
}
auto btRigidBodyConstructionInfo::set_m_linearSleepingThreshold(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_linearSleepingThreshold", args, 1) };
}
auto btRigidBodyConstructionInfo::ref_m_restitution() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_restitution", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_angularSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_angularSleepingThreshold", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_linearSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_linearSleepingThreshold", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_restitution() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_restitution", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_additionalAngularDampingFactor() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_additionalAngularDampingFactor", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_friction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_friction", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_angularDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_angularDamping", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_linearDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_linearDamping", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_angularDamping(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_angularDamping", args, 1) };
}
auto btRigidBodyConstructionInfo::set_m_linearDamping(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_linearDamping", args, 1) };
}
auto btRigidBodyConstructionInfo::get_m_linearSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_linearSleepingThreshold", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_localInertia() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_localInertia", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_localInertia(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_localInertia", args, 1) };
}
auto btRigidBodyConstructionInfo::ref_m_startWorldTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_startWorldTransform", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_additionalDamping() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_additionalDamping", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_startWorldTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_startWorldTransform", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_motionState(GameBindings::Bullet::btMotionState arg0) -> GameBindings::Bullet::btMotionState
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_motionState", args, 1) };
}
auto btRigidBodyConstructionInfo::get_m_motionState() -> GameBindings::Bullet::btMotionState
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_motionState", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_localInertia() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_localInertia", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_mass() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_mass", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_additionalAngularDampingThresholdSqr() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_additionalAngularDampingThresholdSqr", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_mass() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_mass", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_collisionShape() -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionShape", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_mass(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_mass", args, 1) };
}
auto btRigidBodyConstructionInfo::ref_m_motionState() -> GameBindings::Bullet::btMotionState
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_motionState", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_startWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_startWorldTransform", args, 1) };
}
auto btRigidBodyConstructionInfo::tmp(GameBindings::float_expr arg0, GameBindings::Bullet::btMotionState arg1, GameBindings::Bullet::btCollisionShape arg2, GameBindings::Bullet::btVector3 arg3) -> GameBindings::Bullet::btRigidBodyConstructionInfo
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btRigidBodyConstructionInfo::set_m_restitution(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_restitution", args, 1) };
}
auto btRigidBodyConstructionInfo::ref_m_collisionShape() -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionShape", args, 0) };
}
auto btRigidBodyConstructionInfo::set_m_collisionShape(GameBindings::Bullet::btCollisionShape arg0) -> GameBindings::Bullet::btCollisionShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionShape", args, 1) };
}
auto btRigidBodyConstructionInfo::set_m_friction(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_friction", args, 1) };
}
auto btRigidBodyConstructionInfo::lm_new(GameBindings::float_expr arg0, GameBindings::Bullet::btMotionState arg1, GameBindings::Bullet::btCollisionShape arg2, GameBindings::Bullet::btVector3 arg3) -> GameBindings::Bullet::btRigidBodyConstructionInfo
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btRigidBodyConstructionInfo::ref_m_additionalLinearDampingThresholdSqr() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_additionalLinearDampingThresholdSqr", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_friction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_friction", args, 0) };
}
auto btRigidBodyConstructionInfo::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btRigidBodyConstructionInfo::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btRigidBodyConstructionInfo::get_m_angularDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_angularDamping", args, 0) };
}
auto btRigidBodyConstructionInfo::ref_m_linearDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_linearDamping", args, 0) };
}

auto btDefaultCollisionConstructionInfo::get_m_useEpaPenetrationAlgorithm() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_useEpaPenetrationAlgorithm", args, 0) };
}
auto btDefaultCollisionConstructionInfo::set_m_useEpaPenetrationAlgorithm(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_useEpaPenetrationAlgorithm", args, 1) };
}
auto btDefaultCollisionConstructionInfo::get_m_defaultStackAllocatorSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_defaultStackAllocatorSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::set_m_defaultStackAllocatorSize(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_defaultStackAllocatorSize", args, 1) };
}
auto btDefaultCollisionConstructionInfo::ref_m_useEpaPenetrationAlgorithm() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_useEpaPenetrationAlgorithm", args, 0) };
}
auto btDefaultCollisionConstructionInfo::ref_m_defaultMaxCollisionAlgorithmPoolSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_defaultMaxCollisionAlgorithmPoolSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::set_m_defaultMaxCollisionAlgorithmPoolSize(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_defaultMaxCollisionAlgorithmPoolSize", args, 1) };
}
auto btDefaultCollisionConstructionInfo::set_m_customCollisionAlgorithmMaxElementSize(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_customCollisionAlgorithmMaxElementSize", args, 1) };
}
auto btDefaultCollisionConstructionInfo::get_m_defaultMaxPersistentManifoldPoolSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_defaultMaxPersistentManifoldPoolSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::ref_m_customCollisionAlgorithmMaxElementSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_customCollisionAlgorithmMaxElementSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::ref_m_defaultMaxPersistentManifoldPoolSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_defaultMaxPersistentManifoldPoolSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::get_m_defaultMaxCollisionAlgorithmPoolSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_defaultMaxCollisionAlgorithmPoolSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::get_m_stackAlloc() -> MissingType /* C++ btStackAlloc* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_stackAlloc", args, 0) };
}
auto btDefaultCollisionConstructionInfo::set_m_stackAlloc(MissingType /* C++ btStackAlloc* const& (end) */  arg0) -> MissingType /* C++ btStackAlloc* */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_stackAlloc", args, 1) };
}
auto btDefaultCollisionConstructionInfo::ref_m_defaultStackAllocatorSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_defaultStackAllocatorSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::ref_m_stackAlloc() -> MissingType /* C++ btStackAlloc*& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_stackAlloc", args, 0) };
}
auto btDefaultCollisionConstructionInfo::set_m_defaultMaxPersistentManifoldPoolSize(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_defaultMaxPersistentManifoldPoolSize", args, 1) };
}
auto btDefaultCollisionConstructionInfo::tmp() -> GameBindings::Bullet::btDefaultCollisionConstructionInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btDefaultCollisionConstructionInfo::lm_new() -> GameBindings::Bullet::btDefaultCollisionConstructionInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btDefaultCollisionConstructionInfo::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDefaultCollisionConstructionInfo::get_m_customCollisionAlgorithmMaxElementSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_customCollisionAlgorithmMaxElementSize", args, 0) };
}
auto btDefaultCollisionConstructionInfo::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSoftBodyRigidBodyCollisionConfiguration::tmp() -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btSoftBodyRigidBodyCollisionConfiguration::tmp(GameBindings::Bullet::btDefaultCollisionConstructionInfo arg0) -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btSoftBodyRigidBodyCollisionConfiguration::lm_new() -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btSoftBodyRigidBodyCollisionConfiguration::lm_new(GameBindings::Bullet::btDefaultCollisionConstructionInfo arg0) -> GameBindings::Bullet::btSoftBodyRigidBodyCollisionConfiguration
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btSoftBodyRigidBodyCollisionConfiguration::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSoftBodyRigidBodyCollisionConfiguration::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btDefaultCollisionConfiguration::tmp() -> GameBindings::Bullet::btDefaultCollisionConfiguration
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btDefaultCollisionConfiguration::tmp(GameBindings::Bullet::btDefaultCollisionConstructionInfo arg0) -> GameBindings::Bullet::btDefaultCollisionConfiguration
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btDefaultCollisionConfiguration::lm_new() -> GameBindings::Bullet::btDefaultCollisionConfiguration
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btDefaultCollisionConfiguration::lm_new(GameBindings::Bullet::btDefaultCollisionConstructionInfo arg0) -> GameBindings::Bullet::btDefaultCollisionConfiguration
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btDefaultCollisionConfiguration::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btDefaultCollisionConfiguration::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btBroadphaseInterface::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btBroadphaseInterface::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld_LocalShapeInfo::ref_m_triangleIndex() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_triangleIndex", args, 0) };
}
auto btCollisionWorld_LocalShapeInfo::ref_m_shapePart() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_shapePart", args, 0) };
}
auto btCollisionWorld_LocalShapeInfo::get_m_triangleIndex() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_triangleIndex", args, 0) };
}
auto btCollisionWorld_LocalShapeInfo::set_m_shapePart(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_shapePart", args, 1) };
}
auto btCollisionWorld_LocalShapeInfo::get_m_shapePart() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_shapePart", args, 0) };
}
auto btCollisionWorld_LocalShapeInfo::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld_LocalShapeInfo::set_m_triangleIndex(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_triangleIndex", args, 1) };
}
auto btCollisionWorld_LocalShapeInfo::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btConcaveShape::processAllTriangles(MissingType /* C++ btTriangleCallback* (end) */  arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "processAllTriangles", args, 3) };
}
auto btConcaveShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btConcaveShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btGeneric6DofSpringConstraint::setEquilibriumPoint() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "setEquilibriumPoint", args, 0) };
}
auto btGeneric6DofSpringConstraint::setEquilibriumPoint(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setEquilibriumPoint", args, 1) };
}
auto btGeneric6DofSpringConstraint::setDamping(GameBindings::int_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setDamping", args, 2) };
}
auto btGeneric6DofSpringConstraint::enableSpring(GameBindings::int_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "enableSpring", args, 2) };
}
auto btGeneric6DofSpringConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btGeneric6DofSpringConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btGeneric6DofSpringConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btGeneric6DofSpringConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btGeneric6DofSpringConstraint::setStiffness(GameBindings::int_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setStiffness", args, 2) };
}
auto btGeneric6DofSpringConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btGeneric6DofSpringConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto CollisionFilterGroups::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto CollisionFilterGroups::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionShape::setUserPointer(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUserPointer", args, 1) };
}
auto btCollisionShape::serialize(GameBindings::void_expr arg0, MissingType /* C++ btSerializer* (end) */  arg1) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "serialize", args, 2) };
}
auto btCollisionShape::isSoftBody() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isSoftBody", args, 0) };
}
auto btCollisionShape::isPolyhedral() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isPolyhedral", args, 0) };
}
auto btCollisionShape::isInfinite() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isInfinite", args, 0) };
}
auto btCollisionShape::isConvex2d() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isConvex2d", args, 0) };
}
auto btCollisionShape::setLocalScaling(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLocalScaling", args, 1) };
}
auto btCollisionShape::isConvex() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isConvex", args, 0) };
}
auto btCollisionShape::isConcave() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isConcave", args, 0) };
}
auto btCollisionShape::getName() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getName", args, 0) };
}
auto btCollisionShape::getLocalScaling() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLocalScaling", args, 0) };
}
auto btCollisionShape::getBoundingSphere(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getBoundingSphere", args, 2) };
}
auto btCollisionShape::getShapeType() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getShapeType", args, 0) };
}
auto btCollisionShape::getAngularMotionDisc() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularMotionDisc", args, 0) };
}
auto btCollisionShape::getAabb(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getAabb", args, 3) };
}
auto btCollisionShape::getMargin() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMargin", args, 0) };
}
auto btCollisionShape::calculateTemporalAabb(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::Bullet::btVector3 arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "calculateTemporalAabb", args, 6) };
}
auto btCollisionShape::setMargin(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMargin", args, 1) };
}
auto btCollisionShape::calculateSerializeBufferSize() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calculateSerializeBufferSize", args, 0) };
}
auto btCollisionShape::calculateLocalInertia(GameBindings::float_expr arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "calculateLocalInertia", args, 2) };
}
auto btCollisionShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionShape::getUserPointer() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUserPointer", args, 0) };
}
auto btCollisionShape::isCompound() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isCompound", args, 0) };
}
auto btCollisionShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btCollisionShape::getContactBreakingThreshold(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getContactBreakingThreshold", args, 1) };
}

auto btPoint2PointConstraint::updateRHS(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "updateRHS", args, 1) };
}
auto btPoint2PointConstraint::setPivotB(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPivotB", args, 1) };
}
auto btPoint2PointConstraint::getPivotInB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPivotInB", args, 0) };
}
auto btPoint2PointConstraint::getPivotInA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPivotInA", args, 0) };
}
auto btPoint2PointConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::Bullet::btPoint2PointConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btPoint2PointConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3) -> GameBindings::Bullet::btPoint2PointConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btPoint2PointConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::Bullet::btPoint2PointConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btPoint2PointConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3) -> GameBindings::Bullet::btPoint2PointConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btPoint2PointConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btPoint2PointConstraint::setPivotA(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPivotA", args, 1) };
}
auto btPoint2PointConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btRigidBody::wantsSleeping() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "wantsSleeping", args, 0) };
}
auto btRigidBody::updateInertiaTensor() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "updateInertiaTensor", args, 0) };
}
auto btRigidBody::translate(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "translate", args, 1) };
}
auto btRigidBody::setSleepingThresholds(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setSleepingThresholds", args, 2) };
}
auto btRigidBody::updateDeactivation(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "updateDeactivation", args, 1) };
}
auto btRigidBody::setLinearVelocity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLinearVelocity", args, 1) };
}
auto btRigidBody::setInvInertiaDiagLocal(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInvInertiaDiagLocal", args, 1) };
}
auto btRigidBody::setLinearFactor(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLinearFactor", args, 1) };
}
auto btRigidBody::setGravity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setGravity", args, 1) };
}
auto btRigidBody::proceedToTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "proceedToTransform", args, 1) };
}
auto btRigidBody::isInWorld() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isInWorld", args, 0) };
}
auto btRigidBody::getVelocityInLocalPoint(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getVelocityInLocalPoint", args, 1) };
}
auto btRigidBody::getTotalTorque() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTotalTorque", args, 0) };
}
auto btRigidBody::getTotalForce() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTotalForce", args, 0) };
}
auto btRigidBody::getOrientation() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOrientation", args, 0) };
}
auto btRigidBody::getLinearVelocity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinearVelocity", args, 0) };
}
auto btRigidBody::getLinearSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinearSleepingThreshold", args, 0) };
}
auto btRigidBody::getLinearFactor() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinearFactor", args, 0) };
}
auto btRigidBody::getLinearDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLinearDamping", args, 0) };
}
auto btRigidBody::setMassProps(GameBindings::float_expr arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMassProps", args, 2) };
}
auto btRigidBody::getInvMass() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInvMass", args, 0) };
}
auto btRigidBody::getNumConstraintRefs() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNumConstraintRefs", args, 0) };
}
auto btRigidBody::setDamping(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setDamping", args, 2) };
}
auto btRigidBody::getInvInertiaTensorWorld() -> GameBindings::Bullet::btMatrix3x3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInvInertiaTensorWorld", args, 0) };
}
auto btRigidBody::removeConstraintRef(GameBindings::Bullet::btTypedConstraint arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeConstraintRef", args, 1) };
}
auto btRigidBody::getInvInertiaDiagLocal() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getInvInertiaDiagLocal", args, 0) };
}
auto btRigidBody::getGravity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getGravity", args, 0) };
}
auto btRigidBody::saveKinematicState(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "saveKinematicState", args, 1) };
}
auto btRigidBody::getCenterOfMassTransform() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCenterOfMassTransform", args, 0) };
}
auto btRigidBody::getCenterOfMassPosition() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCenterOfMassPosition", args, 0) };
}
auto btRigidBody::setAngularVelocity(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularVelocity", args, 1) };
}
auto btRigidBody::getAngularVelocity() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularVelocity", args, 0) };
}
auto btRigidBody::predictIntegratedTransform(GameBindings::float_expr arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "predictIntegratedTransform", args, 2) };
}
auto btRigidBody::getAngularDamping() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularDamping", args, 0) };
}
auto btRigidBody::computeImpulseDenominator(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "computeImpulseDenominator", args, 2) };
}
auto btRigidBody::checkCollideWithOverride(GameBindings::Bullet::btCollisionObject arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "checkCollideWithOverride", args, 1) };
}
auto btRigidBody::getAngularFactor() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularFactor", args, 0) };
}
auto btRigidBody::getAabb(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getAabb", args, 2) };
}
auto btRigidBody::applyImpulse(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "applyImpulse", args, 2) };
}
auto btRigidBody::setCenterOfMassTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setCenterOfMassTransform", args, 1) };
}
auto btRigidBody::applyGravity() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "applyGravity", args, 0) };
}
auto btRigidBody::applyForce(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "applyForce", args, 2) };
}
auto btRigidBody::applyDamping(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "applyDamping", args, 1) };
}
auto btRigidBody::setFlags(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFlags", args, 1) };
}
auto btRigidBody::applyTorque(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "applyTorque", args, 1) };
}
auto btRigidBody::getConstraintRef(GameBindings::int_expr arg0) -> GameBindings::Bullet::btTypedConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getConstraintRef", args, 1) };
}
auto btRigidBody::applyCentralForce(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "applyCentralForce", args, 1) };
}
auto btRigidBody::setMotionState(GameBindings::Bullet::btMotionState arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMotionState", args, 1) };
}
auto btRigidBody::setAngularFactorScalar(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularFactorScalar", args, 1) };
}
auto btRigidBody::getMotionState_nc() -> GameBindings::Bullet::btMotionState
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMotionState_nc", args, 0) };
}
auto btRigidBody::getFlags() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFlags", args, 0) };
}
auto btRigidBody::clearForces() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clearForces", args, 0) };
}
auto btRigidBody::getMotionState_c() -> GameBindings::Bullet::btMotionState
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMotionState_c", args, 0) };
}
auto btRigidBody::getBroadphaseProxy_nc() -> MissingType /* C++ btBroadphaseProxy* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBroadphaseProxy_nc", args, 0) };
}
auto btRigidBody::applyCentralImpulse(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "applyCentralImpulse", args, 1) };
}
auto btRigidBody::tmp(GameBindings::Bullet::btRigidBodyConstructionInfo arg0) -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btRigidBody::getAngularSleepingThreshold() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngularSleepingThreshold", args, 0) };
}
auto btRigidBody::setAngularFactor(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularFactor", args, 1) };
}
auto btRigidBody::lm_new(GameBindings::Bullet::btRigidBodyConstructionInfo arg0) -> GameBindings::Bullet::btRigidBody
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btRigidBody::applyTorqueImpulse(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "applyTorqueImpulse", args, 1) };
}
auto btRigidBody::getBroadphaseProxy_c() -> MissingType /* C++ btBroadphaseProxy const* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBroadphaseProxy_c", args, 0) };
}
auto btRigidBody::setNewBroadphaseProxy(MissingType /* C++ btBroadphaseProxy* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setNewBroadphaseProxy", args, 1) };
}
auto btRigidBody::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btRigidBody::addConstraintRef(GameBindings::Bullet::btTypedConstraint arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addConstraintRef", args, 1) };
}
auto btRigidBody::computeAngularImpulseDenominator(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "computeAngularImpulseDenominator", args, 1) };
}
auto btRigidBody::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btSphereShape::tmp(GameBindings::float_expr arg0) -> GameBindings::Bullet::btSphereShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btSphereShape::lm_new(GameBindings::float_expr arg0) -> GameBindings::Bullet::btSphereShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btSphereShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btSphereShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btManifoldPoint::ref_m_userPersistentData() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_userPersistentData", args, 0) };
}
auto btManifoldPoint::get_m_userPersistentData() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_userPersistentData", args, 0) };
}
auto btManifoldPoint::set_m_userPersistentData(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_userPersistentData", args, 1) };
}
auto btManifoldPoint::ref_m_positionWorldOnB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_positionWorldOnB", args, 0) };
}
auto btManifoldPoint::get_m_positionWorldOnB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_positionWorldOnB", args, 0) };
}
auto btManifoldPoint::set_m_positionWorldOnB(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_positionWorldOnB", args, 1) };
}
auto btManifoldPoint::ref_m_positionWorldOnA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_positionWorldOnA", args, 0) };
}
auto btManifoldPoint::set_m_positionWorldOnA(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_positionWorldOnA", args, 1) };
}
auto btManifoldPoint::get_m_partId1() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_partId1", args, 0) };
}
auto btManifoldPoint::ref_m_partId0() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_partId0", args, 0) };
}
auto btManifoldPoint::get_m_partId0() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_partId0", args, 0) };
}
auto btManifoldPoint::ref_m_partId1() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_partId1", args, 0) };
}
auto btManifoldPoint::set_m_partId0(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_partId0", args, 1) };
}
auto btManifoldPoint::set_m_normalWorldOnB(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_normalWorldOnB", args, 1) };
}
auto btManifoldPoint::get_m_localPointB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_localPointB", args, 0) };
}
auto btManifoldPoint::set_m_localPointB(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_localPointB", args, 1) };
}
auto btManifoldPoint::get_m_positionWorldOnA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_positionWorldOnA", args, 0) };
}
auto btManifoldPoint::set_m_partId1(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_partId1", args, 1) };
}
auto btManifoldPoint::ref_m_localPointA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_localPointA", args, 0) };
}
auto btManifoldPoint::get_m_localPointA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_localPointA", args, 0) };
}
auto btManifoldPoint::set_m_localPointA(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_localPointA", args, 1) };
}
auto btManifoldPoint::ref_m_lifeTime() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_lifeTime", args, 0) };
}
auto btManifoldPoint::set_m_lifeTime(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_lifeTime", args, 1) };
}
auto btManifoldPoint::ref_m_lateralFrictionInitialized() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_lateralFrictionInitialized", args, 0) };
}
auto btManifoldPoint::set_m_lateralFrictionInitialized(GameBindings::bool_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_lateralFrictionInitialized", args, 1) };
}
auto btManifoldPoint::get_m_lateralFrictionDir2() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_lateralFrictionDir2", args, 0) };
}
auto btManifoldPoint::set_m_lateralFrictionDir2(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_lateralFrictionDir2", args, 1) };
}
auto btManifoldPoint::set_m_lateralFrictionDir1(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_lateralFrictionDir1", args, 1) };
}
auto btManifoldPoint::set_m_index1(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_index1", args, 1) };
}
auto btManifoldPoint::ref_m_index0() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_index0", args, 0) };
}
auto btManifoldPoint::get_m_index0() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_index0", args, 0) };
}
auto btManifoldPoint::set_m_index0(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_index0", args, 1) };
}
auto btManifoldPoint::get_m_distance1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_distance1", args, 0) };
}
auto btManifoldPoint::ref_m_contactMotion2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_contactMotion2", args, 0) };
}
auto btManifoldPoint::set_m_contactMotion2(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_contactMotion2", args, 1) };
}
auto btManifoldPoint::ref_m_contactMotion1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_contactMotion1", args, 0) };
}
auto btManifoldPoint::set_m_distance1(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_distance1", args, 1) };
}
auto btManifoldPoint::get_m_contactMotion1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_contactMotion1", args, 0) };
}
auto btManifoldPoint::ref_m_contactCFM2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_contactCFM2", args, 0) };
}
auto btManifoldPoint::set_m_contactCFM2(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_contactCFM2", args, 1) };
}
auto btManifoldPoint::get_m_contactCFM1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_contactCFM1", args, 0) };
}
auto btManifoldPoint::get_m_combinedRestitution() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_combinedRestitution", args, 0) };
}
auto btManifoldPoint::ref_m_index1() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_index1", args, 0) };
}
auto btManifoldPoint::ref_m_combinedFriction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_combinedFriction", args, 0) };
}
auto btManifoldPoint::set_m_combinedFriction(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_combinedFriction", args, 1) };
}
auto btManifoldPoint::set_m_contactMotion1(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_contactMotion1", args, 1) };
}
auto btManifoldPoint::get_m_appliedImpulseLateral2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_appliedImpulseLateral2", args, 0) };
}
auto btManifoldPoint::set_m_combinedRestitution(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_combinedRestitution", args, 1) };
}
auto btManifoldPoint::get_m_lifeTime() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_lifeTime", args, 0) };
}
auto btManifoldPoint::ref_m_normalWorldOnB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_normalWorldOnB", args, 0) };
}
auto btManifoldPoint::set_m_appliedImpulseLateral1(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_appliedImpulseLateral1", args, 1) };
}
auto btManifoldPoint::get_m_combinedFriction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_combinedFriction", args, 0) };
}
auto btManifoldPoint::ref_m_appliedImpulseLateral1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_appliedImpulseLateral1", args, 0) };
}
auto btManifoldPoint::ref_m_contactCFM1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_contactCFM1", args, 0) };
}
auto btManifoldPoint::ref_m_appliedImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_appliedImpulse", args, 0) };
}
auto btManifoldPoint::get_m_appliedImpulse() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_appliedImpulse", args, 0) };
}
auto btManifoldPoint::get_m_index1() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_index1", args, 0) };
}
auto btManifoldPoint::setDistance(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDistance", args, 1) };
}
auto btManifoldPoint::getPositionWorldOnB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPositionWorldOnB", args, 0) };
}
auto btManifoldPoint::ref_m_localPointB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_localPointB", args, 0) };
}
auto btManifoldPoint::ref_m_combinedRestitution() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_combinedRestitution", args, 0) };
}
auto btManifoldPoint::getPositionWorldOnA() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPositionWorldOnA", args, 0) };
}
auto btManifoldPoint::set_m_appliedImpulseLateral2(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_appliedImpulseLateral2", args, 1) };
}
auto btManifoldPoint::get_m_lateralFrictionInitialized() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_lateralFrictionInitialized", args, 0) };
}
auto btManifoldPoint::ref_m_lateralFrictionDir1() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_lateralFrictionDir1", args, 0) };
}
auto btManifoldPoint::getDistance() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDistance", args, 0) };
}
auto btManifoldPoint::get_m_contactMotion2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_contactMotion2", args, 0) };
}
auto btManifoldPoint::set_m_contactCFM1(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_contactCFM1", args, 1) };
}
auto btManifoldPoint::tmp() -> GameBindings::Bullet::btManifoldPoint
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btManifoldPoint::tmp(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btManifoldPoint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btManifoldPoint::get_m_lateralFrictionDir1() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_lateralFrictionDir1", args, 0) };
}
auto btManifoldPoint::get_m_appliedImpulseLateral1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_appliedImpulseLateral1", args, 0) };
}
auto btManifoldPoint::get_m_contactCFM2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_contactCFM2", args, 0) };
}
auto btManifoldPoint::lm_new() -> GameBindings::Bullet::btManifoldPoint
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btManifoldPoint::lm_new(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btManifoldPoint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btManifoldPoint::set_m_appliedImpulse(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_appliedImpulse", args, 1) };
}
auto btManifoldPoint::get_m_normalWorldOnB() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_normalWorldOnB", args, 0) };
}
auto btManifoldPoint::ref_m_appliedImpulseLateral2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_appliedImpulseLateral2", args, 0) };
}
auto btManifoldPoint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btManifoldPoint::ref_m_distance1() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_distance1", args, 0) };
}
auto btManifoldPoint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto btManifoldPoint::ref_m_lateralFrictionDir2() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_lateralFrictionDir2", args, 0) };
}
auto btManifoldPoint::getLifeTime() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLifeTime", args, 0) };
}

auto btMotionState::setWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setWorldTransform", args, 1) };
}
auto btMotionState::getWorldTransform(GameBindings::Bullet::btTransform arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getWorldTransform", args, 1) };
}
auto btMotionState::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btMotionState::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCylinderShape::tmp(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btCylinderShape::lm_new(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShape
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btCylinderShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCylinderShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionConfiguration::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionConfiguration::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btVector3::operator +=(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+=", args, 1) };
}
auto btVector3::z() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "z", args, 0) };
}
auto btVector3::y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "y", args, 0) };
}
auto btVector3::x() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "x", args, 0) };
}
auto btVector3::w() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "w", args, 0) };
}
auto btVector3::triple(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "triple", args, 2) };
}
auto btVector3::setY(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setY", args, 1) };
}
auto btVector3::setX(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setX", args, 1) };
}
auto btVector3::setValue(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setValue", args, 3) };
}
auto btVector3::setInterpolate3(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setInterpolate3", args, 3) };
}
auto btVector3::serializeFloat(MissingType /* C++ btVector3FloatData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serializeFloat", args, 1) };
}
auto btVector3::rotate(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotate", args, 2) };
}
auto btVector3::normalized() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "normalized", args, 0) };
}
auto btVector3::normalize() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "normalize", args, 0) };
}
auto btVector3::setMin(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMin", args, 1) };
}
auto btVector3::lerp(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "lerp", args, 2) };
}
auto btVector3::minAxis() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "minAxis", args, 0) };
}
auto btVector3::length() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "length", args, 0) };
}
auto btVector3::isZero() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isZero", args, 0) };
}
auto btVector3::getY() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getY", args, 0) };
}
auto btVector3::setZero() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "setZero", args, 0) };
}
auto btVector3::getX() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getX", args, 0) };
}
auto btVector3::setZ(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setZ", args, 1) };
}
auto btVector3::getSkewSymmetricMatrix(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getSkewSymmetricMatrix", args, 3) };
}
auto btVector3::dot(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "dot", args, 1) };
}
auto btVector3::distance(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "distance", args, 1) };
}
auto btVector3::maxAxis() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "maxAxis", args, 0) };
}
auto btVector3::deSerializeDouble(MissingType /* C++ btVector3DoubleData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerializeDouble", args, 1) };
}
auto btVector3::setMax(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMax", args, 1) };
}
auto btVector3::cross(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "cross", args, 1) };
}
auto btVector3::serializeDouble(MissingType /* C++ btVector3DoubleData& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "serializeDouble", args, 1) };
}
auto btVector3::furthestAxis() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "furthestAxis", args, 0) };
}
auto btVector3::closestAxis() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "closestAxis", args, 0) };
}
auto btVector3::setW(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setW", args, 1) };
}
auto btVector3::angle(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "angle", args, 1) };
}
auto btVector3::deSerialize(MissingType /* C++ btVector3FloatData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerialize", args, 1) };
}
auto btVector3::distance2(GameBindings::Bullet::btVector3 arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "distance2", args, 1) };
}
auto btVector3::absolute() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "absolute", args, 0) };
}
auto btVector3::length2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "length2", args, 0) };
}
auto btVector3::tmp() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btVector3::tmp(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btVector3::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btVector3::fuzzyZero() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "fuzzyZero", args, 0) };
}
auto btVector3::operator -=(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-=", args, 1) };
}
auto btVector3::lm_new() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btVector3::lm_new(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btVector3::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btVector3::deSerializeFloat(MissingType /* C++ btVector3FloatData const& (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "deSerializeFloat", args, 1) };
}
auto btVector3::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btVector3::getZ() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getZ", args, 0) };
}
auto btVector3::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btGeneric6DofConstraint::getFrameOffsetB_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetB_nc", args, 0) };
}
auto btGeneric6DofConstraint::updateRHS(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "updateRHS", args, 1) };
}
auto btGeneric6DofConstraint::calculateTransforms() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calculateTransforms", args, 0) };
}
auto btGeneric6DofConstraint::calculateTransforms(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "calculateTransforms", args, 2) };
}
auto btGeneric6DofConstraint::setUseFrameOffset(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUseFrameOffset", args, 1) };
}
auto btGeneric6DofConstraint::setLinearLowerLimit(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLinearLowerLimit", args, 1) };
}
auto btGeneric6DofConstraint::setLimit(GameBindings::int_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setLimit", args, 3) };
}
auto btGeneric6DofConstraint::setAngularUpperLimit(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularUpperLimit", args, 1) };
}
auto btGeneric6DofConstraint::getFrameOffsetA_nc() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetA_nc", args, 0) };
}
auto btGeneric6DofConstraint::getUseFrameOffset() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUseFrameOffset", args, 0) };
}
auto btGeneric6DofConstraint::getFrameOffsetA_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetA_c", args, 0) };
}
auto btGeneric6DofConstraint::getRotationalLimitMotor(GameBindings::int_expr arg0) -> GameBindings::Bullet::btRotationalLimitMotor
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getRotationalLimitMotor", args, 1) };
}
auto btGeneric6DofConstraint::setAngularLowerLimit(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAngularLowerLimit", args, 1) };
}
auto btGeneric6DofConstraint::getRelativePivotPosition(GameBindings::int_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getRelativePivotPosition", args, 1) };
}
auto btGeneric6DofConstraint::getCalculatedTransformB() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCalculatedTransformB", args, 0) };
}
auto btGeneric6DofConstraint::getAxis(GameBindings::int_expr arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getAxis", args, 1) };
}
auto btGeneric6DofConstraint::setLinearUpperLimit(GameBindings::Bullet::btVector3 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLinearUpperLimit", args, 1) };
}
auto btGeneric6DofConstraint::isLimited(GameBindings::int_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isLimited", args, 1) };
}
auto btGeneric6DofConstraint::get_limit_motor_info2(GameBindings::Bullet::btRotationalLimitMotor arg0, GameBindings::Bullet::btTransform arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::Bullet::btVector3 arg4, GameBindings::Bullet::btVector3 arg5, GameBindings::Bullet::btVector3 arg6, MissingType /* C++ btTypedConstraint::btConstraintInfo2* (end) */  arg7, GameBindings::int_expr arg8, GameBindings::Bullet::btVector3 arg9, GameBindings::int_expr arg10, GameBindings::int_expr arg11) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr, arg10.expr, arg11.expr }; 
    return { ::LM::call(expr, "get_limit_motor_info2", args, 12) };
}
auto btGeneric6DofConstraint::getFrameOffsetB_c() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFrameOffsetB_c", args, 0) };
}
auto btGeneric6DofConstraint::getCalculatedTransformA() -> GameBindings::Bullet::btTransform
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCalculatedTransformA", args, 0) };
}
auto btGeneric6DofConstraint::calcAnchorPos() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "calcAnchorPos", args, 0) };
}
auto btGeneric6DofConstraint::getAngle(GameBindings::int_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getAngle", args, 1) };
}
auto btGeneric6DofConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btGeneric6DofConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btGeneric6DofConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btGeneric6DofConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btGeneric6DofConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btTransform arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btGeneric6DofConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btGeneric6DofConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::Bullet::btTransform arg2, GameBindings::Bullet::btTransform arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btGeneric6DofConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btGeneric6DofConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btGeneric6DofConstraint::getTranslationalLimitMotor() -> MissingType /* C++ btTranslationalLimitMotor* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTranslationalLimitMotor", args, 0) };
}
auto btGeneric6DofConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCollisionWorld_LocalRayResult::ref_m_hitFraction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_hitFraction", args, 0) };
}
auto btCollisionWorld_LocalRayResult::get_m_hitFraction() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_hitFraction", args, 0) };
}
auto btCollisionWorld_LocalRayResult::ref_m_hitNormalLocal() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_hitNormalLocal", args, 0) };
}
auto btCollisionWorld_LocalRayResult::get_m_hitNormalLocal() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_hitNormalLocal", args, 0) };
}
auto btCollisionWorld_LocalRayResult::set_m_hitNormalLocal(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_hitNormalLocal", args, 1) };
}
auto btCollisionWorld_LocalRayResult::ref_m_localShapeInfo() -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_localShapeInfo", args, 0) };
}
auto btCollisionWorld_LocalRayResult::get_m_localShapeInfo() -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_localShapeInfo", args, 0) };
}
auto btCollisionWorld_LocalRayResult::set_m_hitFraction(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_hitFraction", args, 1) };
}
auto btCollisionWorld_LocalRayResult::set_m_localShapeInfo(GameBindings::Bullet::btCollisionWorld_LocalShapeInfo arg0) -> GameBindings::Bullet::btCollisionWorld_LocalShapeInfo
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_localShapeInfo", args, 1) };
}
auto btCollisionWorld_LocalRayResult::ref_m_collisionObject() -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_m_collisionObject", args, 0) };
}
auto btCollisionWorld_LocalRayResult::set_m_collisionObject(GameBindings::Bullet::btCollisionObject arg0) -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_m_collisionObject", args, 1) };
}
auto btCollisionWorld_LocalRayResult::get_m_collisionObject() -> GameBindings::Bullet::btCollisionObject
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_m_collisionObject", args, 0) };
}
auto btCollisionWorld_LocalRayResult::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCollisionWorld_LocalRayResult::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btStaticPlaneShape::tmp(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btStaticPlaneShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btStaticPlaneShape::lm_new(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btStaticPlaneShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btStaticPlaneShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btStaticPlaneShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btQuaternion::setRotation(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setRotation", args, 2) };
}
auto btQuaternion::setEulerZYX(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setEulerZYX", args, 3) };
}
auto btQuaternion::normalized() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "normalized", args, 0) };
}
auto btQuaternion::normalize() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "normalize", args, 0) };
}
auto btQuaternion::length() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "length", args, 0) };
}
auto btQuaternion::getW() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getW", args, 0) };
}
auto btQuaternion::length2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "length2", args, 0) };
}
auto btQuaternion::inverse() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "inverse", args, 0) };
}
auto btQuaternion::getAngle() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAngle", args, 0) };
}
auto btQuaternion::dot(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "dot", args, 1) };
}
auto btQuaternion::getAxis() -> GameBindings::Bullet::btVector3
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAxis", args, 0) };
}
auto btQuaternion::setEuler(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setEuler", args, 3) };
}
auto btQuaternion::angle(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "angle", args, 1) };
}
auto btQuaternion::nearest(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "nearest", args, 1) };
}
auto btQuaternion::slerp(GameBindings::Bullet::btQuaternion arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "slerp", args, 2) };
}
auto btQuaternion::farthest(GameBindings::Bullet::btQuaternion arg0) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "farthest", args, 1) };
}
auto btQuaternion::getIdentityQuaternion() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIdentityQuaternion", args, 0) };
}
auto btQuaternion::tmp() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto btQuaternion::tmp(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto btQuaternion::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btQuaternion::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto btQuaternion::lm_new() -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto btQuaternion::lm_new(GameBindings::Bullet::btVector3 arg0, GameBindings::float_expr arg1) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto btQuaternion::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btQuaternion::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::Bullet::btQuaternion
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto btQuaternion::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btQuaternion::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btMultimaterialTriangleMeshShape::getMaterialProperties(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> MissingType /* C++ btMaterial const* */ 
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getMaterialProperties", args, 2) };
}
auto btMultimaterialTriangleMeshShape::tmp(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto btMultimaterialTriangleMeshShape::tmp(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "tmp", args, 5) };
}
auto btMultimaterialTriangleMeshShape::lm_new(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto btMultimaterialTriangleMeshShape::lm_new(GameBindings::Bullet::btStridingMeshInterface arg0, GameBindings::bool_expr arg1, GameBindings::Bullet::btVector3 arg2, GameBindings::Bullet::btVector3 arg3, GameBindings::bool_expr arg4) -> GameBindings::Bullet::btMultimaterialTriangleMeshShape
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "new", args, 5) };
}
auto btMultimaterialTriangleMeshShape::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btMultimaterialTriangleMeshShape::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto btCylinderShapeX::tmp(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShapeX
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto btCylinderShapeX::lm_new(GameBindings::Bullet::btVector3 arg0) -> GameBindings::Bullet::btCylinderShapeX
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto btCylinderShapeX::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto btCylinderShapeX::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
