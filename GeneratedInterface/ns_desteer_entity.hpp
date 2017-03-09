#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace desteer
	{
		namespace entity
		{

struct IEntitySpace
{
    ::LM::ExprPtr expr;
    auto transformLocalVectToWorld(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto transformWorldVectToLocal(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto SetForwardVector(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto ForwardVector() -> GameBindings::irr::core::vector3df;
    auto SetSideVector(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto SideVector() -> GameBindings::irr::core::vector3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IBaseEntity
{
    ::LM::ExprPtr expr;
    auto SetPosition(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto Position() -> GameBindings::irr::core::vector3df;
    auto Radius() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto Update(GameBindings::float_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedBaseEntity
{
    ::LM::ExprPtr expr;
    auto ref_OnUpdate() -> GameBindings::LangBlockExpr;
    auto get_OnUpdate() -> GameBindings::LangBlockExpr;
    auto ref_OnRadius() -> GameBindings::LangBlockExpr;
    auto set_OnRadius(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetPosition() -> GameBindings::LangBlockExpr;
    auto set_OnUpdate(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnSetPosition() -> GameBindings::LangBlockExpr;
    auto set_OnSetPosition(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnPosition(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnRadius() -> GameBindings::LangBlockExpr;
    auto ref_OnPosition() -> GameBindings::LangBlockExpr;
    auto tmp() -> GameBindings::desteer::entity::ScriptedBaseEntity;
    auto get_OnPosition() -> GameBindings::LangBlockExpr;
    auto lm_new() -> GameBindings::desteer::entity::ScriptedBaseEntity;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IMobileEntity
{
    ::LM::ExprPtr expr;
    auto SetMaxSpeed(GameBindings::float_expr) -> GameBindings::void_expr;
    auto SetMaxForce(GameBindings::float_expr) -> GameBindings::void_expr;
    auto Velocity() -> GameBindings::irr::core::vector3df;
    auto SetMass(GameBindings::float_expr) -> GameBindings::void_expr;
    auto MaxSpeed() -> GameBindings::float_expr;
    auto MaxForce() -> GameBindings::float_expr;
    auto Mass() -> GameBindings::float_expr;
    auto SetSteering(GameBindings::desteer::controller::ISteeringController) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedEntitySpace
{
    ::LM::ExprPtr expr;
    auto ref_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr;
    auto get_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr;
    auto ref_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr;
    auto get_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr;
    auto set_OntransformWorldVectToLocal(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetForwardVector() -> GameBindings::LangBlockExpr;
    auto ref_OnForwardVector() -> GameBindings::LangBlockExpr;
    auto get_OnForwardVector() -> GameBindings::LangBlockExpr;
    auto set_OnSetForwardVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnSetForwardVector() -> GameBindings::LangBlockExpr;
    auto set_OnForwardVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnSetSideVector() -> GameBindings::LangBlockExpr;
    auto set_OnSideVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto tmp() -> GameBindings::desteer::entity::ScriptedEntitySpace;
    auto ref_OnSideVector() -> GameBindings::LangBlockExpr;
    auto set_OntransformLocalVectToWorld(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto lm_new() -> GameBindings::desteer::entity::ScriptedEntitySpace;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_OnSetSideVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetSideVector() -> GameBindings::LangBlockExpr;
    auto get_OnSideVector() -> GameBindings::LangBlockExpr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedMobileEntity
{
    ::LM::ExprPtr expr;
    auto set_OnVelocity(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetMaxSpeed() -> GameBindings::LangBlockExpr;
    auto get_OnSetMaxSpeed() -> GameBindings::LangBlockExpr;
    auto get_OnVelocity() -> GameBindings::LangBlockExpr;
    auto set_OnSetMaxSpeed(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnMaxSpeed(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetMaxForce() -> GameBindings::LangBlockExpr;
    auto ref_OnMaxForce() -> GameBindings::LangBlockExpr;
    auto get_OnSetMass() -> GameBindings::LangBlockExpr;
    auto set_OnSetMass(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnMass() -> GameBindings::LangBlockExpr;
    auto ref_OnSetSteering() -> GameBindings::LangBlockExpr;
    auto get_OnSetSteering() -> GameBindings::LangBlockExpr;
    auto set_OnSetSteering(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnVelocity() -> GameBindings::LangBlockExpr;
    auto get_OnMaxSpeed() -> GameBindings::LangBlockExpr;
    auto ref_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr;
    auto get_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr;
    auto ref_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr;
    auto set_OntransformWorldVectToLocal(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetForwardVector() -> GameBindings::LangBlockExpr;
    auto ref_OnForwardVector() -> GameBindings::LangBlockExpr;
    auto get_OnForwardVector() -> GameBindings::LangBlockExpr;
    auto set_OnSetForwardVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnSetSideVector() -> GameBindings::LangBlockExpr;
    auto get_OnSideVector() -> GameBindings::LangBlockExpr;
    auto set_OnSideVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnMass() -> GameBindings::LangBlockExpr;
    auto set_OnMass(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr;
    auto get_OnMaxForce() -> GameBindings::LangBlockExpr;
    auto ref_OnUpdate() -> GameBindings::LangBlockExpr;
    auto get_OnUpdate() -> GameBindings::LangBlockExpr;
    auto get_OnSetMaxForce() -> GameBindings::LangBlockExpr;
    auto get_OnSetForwardVector() -> GameBindings::LangBlockExpr;
    auto ref_OnRadius() -> GameBindings::LangBlockExpr;
    auto ref_OnMaxSpeed() -> GameBindings::LangBlockExpr;
    auto set_OnForwardVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnSetMaxForce(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnRadius(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_OnSetPosition() -> GameBindings::LangBlockExpr;
    auto get_OnSetPosition() -> GameBindings::LangBlockExpr;
    auto set_OnUpdate(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnSetPosition(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OnPosition(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_OnRadius() -> GameBindings::LangBlockExpr;
    auto tmp() -> GameBindings::desteer::entity::ScriptedMobileEntity;
    auto ref_OnSideVector() -> GameBindings::LangBlockExpr;
    auto ref_OnSetMass() -> GameBindings::LangBlockExpr;
    auto ref_OnPosition() -> GameBindings::LangBlockExpr;
    auto get_OnPosition() -> GameBindings::LangBlockExpr;
    auto set_OnMaxForce(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto set_OntransformLocalVectToWorld(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto lm_new() -> GameBindings::desteer::entity::ScriptedMobileEntity;
    auto ref_OnSetSideVector() -> GameBindings::LangBlockExpr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_OnSetSideVector(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
