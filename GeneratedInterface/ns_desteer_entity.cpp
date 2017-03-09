#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_desteer_entity.hpp"
#include "ns_irr_core.hpp"
#include "ns_desteer_controller.hpp"
#include "ns_global.hpp"

namespace GameBindings
{
	namespace desteer
	{
		namespace entity
		{

auto IEntitySpace::transformLocalVectToWorld(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "transformLocalVectToWorld", args, 1) };
}
auto IEntitySpace::transformWorldVectToLocal(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "transformWorldVectToLocal", args, 1) };
}
auto IEntitySpace::SetForwardVector(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetForwardVector", args, 1) };
}
auto IEntitySpace::ForwardVector() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ForwardVector", args, 0) };
}
auto IEntitySpace::SetSideVector(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetSideVector", args, 1) };
}
auto IEntitySpace::SideVector() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "SideVector", args, 0) };
}
auto IEntitySpace::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IEntitySpace::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IBaseEntity::SetPosition(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetPosition", args, 1) };
}
auto IBaseEntity::Position() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Position", args, 0) };
}
auto IBaseEntity::Radius() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Radius", args, 0) };
}
auto IBaseEntity::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IBaseEntity::Update(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "Update", args, 1) };
}
auto IBaseEntity::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedBaseEntity::ref_OnUpdate() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnUpdate", args, 0) };
}
auto ScriptedBaseEntity::get_OnUpdate() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnUpdate", args, 0) };
}
auto ScriptedBaseEntity::ref_OnRadius() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnRadius", args, 0) };
}
auto ScriptedBaseEntity::set_OnRadius(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnRadius", args, 1) };
}
auto ScriptedBaseEntity::ref_OnSetPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetPosition", args, 0) };
}
auto ScriptedBaseEntity::set_OnUpdate(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnUpdate", args, 1) };
}
auto ScriptedBaseEntity::get_OnSetPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetPosition", args, 0) };
}
auto ScriptedBaseEntity::set_OnSetPosition(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetPosition", args, 1) };
}
auto ScriptedBaseEntity::set_OnPosition(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnPosition", args, 1) };
}
auto ScriptedBaseEntity::get_OnRadius() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnRadius", args, 0) };
}
auto ScriptedBaseEntity::ref_OnPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnPosition", args, 0) };
}
auto ScriptedBaseEntity::tmp() -> GameBindings::desteer::entity::ScriptedBaseEntity
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ScriptedBaseEntity::get_OnPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnPosition", args, 0) };
}
auto ScriptedBaseEntity::lm_new() -> GameBindings::desteer::entity::ScriptedBaseEntity
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ScriptedBaseEntity::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedBaseEntity::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMobileEntity::SetMaxSpeed(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetMaxSpeed", args, 1) };
}
auto IMobileEntity::SetMaxForce(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetMaxForce", args, 1) };
}
auto IMobileEntity::Velocity() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Velocity", args, 0) };
}
auto IMobileEntity::SetMass(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetMass", args, 1) };
}
auto IMobileEntity::MaxSpeed() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "MaxSpeed", args, 0) };
}
auto IMobileEntity::MaxForce() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "MaxForce", args, 0) };
}
auto IMobileEntity::Mass() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Mass", args, 0) };
}
auto IMobileEntity::SetSteering(GameBindings::desteer::controller::ISteeringController arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetSteering", args, 1) };
}
auto IMobileEntity::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMobileEntity::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedEntitySpace::ref_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OntransformLocalVectToWorld", args, 0) };
}
auto ScriptedEntitySpace::get_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OntransformLocalVectToWorld", args, 0) };
}
auto ScriptedEntitySpace::ref_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OntransformWorldVectToLocal", args, 0) };
}
auto ScriptedEntitySpace::get_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OntransformWorldVectToLocal", args, 0) };
}
auto ScriptedEntitySpace::set_OntransformWorldVectToLocal(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OntransformWorldVectToLocal", args, 1) };
}
auto ScriptedEntitySpace::ref_OnSetForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetForwardVector", args, 0) };
}
auto ScriptedEntitySpace::ref_OnForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnForwardVector", args, 0) };
}
auto ScriptedEntitySpace::get_OnForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnForwardVector", args, 0) };
}
auto ScriptedEntitySpace::set_OnSetForwardVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetForwardVector", args, 1) };
}
auto ScriptedEntitySpace::get_OnSetForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetForwardVector", args, 0) };
}
auto ScriptedEntitySpace::set_OnForwardVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnForwardVector", args, 1) };
}
auto ScriptedEntitySpace::get_OnSetSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetSideVector", args, 0) };
}
auto ScriptedEntitySpace::set_OnSideVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSideVector", args, 1) };
}
auto ScriptedEntitySpace::tmp() -> GameBindings::desteer::entity::ScriptedEntitySpace
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ScriptedEntitySpace::ref_OnSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSideVector", args, 0) };
}
auto ScriptedEntitySpace::set_OntransformLocalVectToWorld(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OntransformLocalVectToWorld", args, 1) };
}
auto ScriptedEntitySpace::lm_new() -> GameBindings::desteer::entity::ScriptedEntitySpace
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ScriptedEntitySpace::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedEntitySpace::set_OnSetSideVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetSideVector", args, 1) };
}
auto ScriptedEntitySpace::ref_OnSetSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetSideVector", args, 0) };
}
auto ScriptedEntitySpace::get_OnSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSideVector", args, 0) };
}
auto ScriptedEntitySpace::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedMobileEntity::set_OnVelocity(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnVelocity", args, 1) };
}
auto ScriptedMobileEntity::ref_OnSetMaxSpeed() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetMaxSpeed", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetMaxSpeed() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetMaxSpeed", args, 0) };
}
auto ScriptedMobileEntity::get_OnVelocity() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnVelocity", args, 0) };
}
auto ScriptedMobileEntity::set_OnSetMaxSpeed(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetMaxSpeed", args, 1) };
}
auto ScriptedMobileEntity::set_OnMaxSpeed(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnMaxSpeed", args, 1) };
}
auto ScriptedMobileEntity::ref_OnSetMaxForce() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetMaxForce", args, 0) };
}
auto ScriptedMobileEntity::ref_OnMaxForce() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnMaxForce", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetMass() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetMass", args, 0) };
}
auto ScriptedMobileEntity::set_OnSetMass(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetMass", args, 1) };
}
auto ScriptedMobileEntity::ref_OnMass() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnMass", args, 0) };
}
auto ScriptedMobileEntity::ref_OnSetSteering() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetSteering", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetSteering() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetSteering", args, 0) };
}
auto ScriptedMobileEntity::set_OnSetSteering(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetSteering", args, 1) };
}
auto ScriptedMobileEntity::ref_OnVelocity() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnVelocity", args, 0) };
}
auto ScriptedMobileEntity::get_OnMaxSpeed() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnMaxSpeed", args, 0) };
}
auto ScriptedMobileEntity::ref_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OntransformLocalVectToWorld", args, 0) };
}
auto ScriptedMobileEntity::get_OntransformLocalVectToWorld() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OntransformLocalVectToWorld", args, 0) };
}
auto ScriptedMobileEntity::ref_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OntransformWorldVectToLocal", args, 0) };
}
auto ScriptedMobileEntity::set_OntransformWorldVectToLocal(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OntransformWorldVectToLocal", args, 1) };
}
auto ScriptedMobileEntity::ref_OnSetForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetForwardVector", args, 0) };
}
auto ScriptedMobileEntity::ref_OnForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnForwardVector", args, 0) };
}
auto ScriptedMobileEntity::get_OnForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnForwardVector", args, 0) };
}
auto ScriptedMobileEntity::set_OnSetForwardVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetForwardVector", args, 1) };
}
auto ScriptedMobileEntity::get_OnSetSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetSideVector", args, 0) };
}
auto ScriptedMobileEntity::get_OnSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSideVector", args, 0) };
}
auto ScriptedMobileEntity::set_OnSideVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSideVector", args, 1) };
}
auto ScriptedMobileEntity::get_OnMass() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnMass", args, 0) };
}
auto ScriptedMobileEntity::set_OnMass(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnMass", args, 1) };
}
auto ScriptedMobileEntity::get_OntransformWorldVectToLocal() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OntransformWorldVectToLocal", args, 0) };
}
auto ScriptedMobileEntity::get_OnMaxForce() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnMaxForce", args, 0) };
}
auto ScriptedMobileEntity::ref_OnUpdate() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnUpdate", args, 0) };
}
auto ScriptedMobileEntity::get_OnUpdate() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnUpdate", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetMaxForce() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetMaxForce", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetForwardVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetForwardVector", args, 0) };
}
auto ScriptedMobileEntity::ref_OnRadius() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnRadius", args, 0) };
}
auto ScriptedMobileEntity::ref_OnMaxSpeed() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnMaxSpeed", args, 0) };
}
auto ScriptedMobileEntity::set_OnForwardVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnForwardVector", args, 1) };
}
auto ScriptedMobileEntity::set_OnSetMaxForce(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetMaxForce", args, 1) };
}
auto ScriptedMobileEntity::set_OnRadius(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnRadius", args, 1) };
}
auto ScriptedMobileEntity::ref_OnSetPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetPosition", args, 0) };
}
auto ScriptedMobileEntity::get_OnSetPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnSetPosition", args, 0) };
}
auto ScriptedMobileEntity::set_OnUpdate(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnUpdate", args, 1) };
}
auto ScriptedMobileEntity::set_OnSetPosition(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetPosition", args, 1) };
}
auto ScriptedMobileEntity::set_OnPosition(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnPosition", args, 1) };
}
auto ScriptedMobileEntity::get_OnRadius() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnRadius", args, 0) };
}
auto ScriptedMobileEntity::tmp() -> GameBindings::desteer::entity::ScriptedMobileEntity
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ScriptedMobileEntity::ref_OnSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSideVector", args, 0) };
}
auto ScriptedMobileEntity::ref_OnSetMass() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetMass", args, 0) };
}
auto ScriptedMobileEntity::ref_OnPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnPosition", args, 0) };
}
auto ScriptedMobileEntity::get_OnPosition() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_OnPosition", args, 0) };
}
auto ScriptedMobileEntity::set_OnMaxForce(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnMaxForce", args, 1) };
}
auto ScriptedMobileEntity::set_OntransformLocalVectToWorld(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OntransformLocalVectToWorld", args, 1) };
}
auto ScriptedMobileEntity::lm_new() -> GameBindings::desteer::entity::ScriptedMobileEntity
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ScriptedMobileEntity::ref_OnSetSideVector() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_OnSetSideVector", args, 0) };
}
auto ScriptedMobileEntity::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedMobileEntity::set_OnSetSideVector(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_OnSetSideVector", args, 1) };
}
auto ScriptedMobileEntity::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
