#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_desteer_entity.hpp"
#include "ns_irr_core.hpp"
#include "ns_desteer_controller.hpp"
#include "ns_desteer.hpp"
#include "ns_global.hpp"

namespace GameBindings
{
	namespace desteer
	{
		namespace controller
		{

auto EBEHAVIOR_FLAG::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto EBEHAVIOR_FLAG::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto EBEHAVIOR_FLAG::operator ==(GameBindings::desteer::controller::EBEHAVIOR_FLAG arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto EBEHAVIOR_FLAG::operator !=(GameBindings::desteer::controller::EBEHAVIOR_FLAG arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto EBEHAVIOR_FLAG::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EBEHAVIOR_FLAG::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ISteeringController::Calculate() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "Calculate", args, 0) };
}
auto ISteeringController::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISteeringController::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SimpleSteeringController::SetHideTarget(GameBindings::desteer::entity::IMobileEntity arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetHideTarget", args, 1) };
}
auto SimpleSteeringController::SetBehaviorFlag(GameBindings::desteer::controller::EBEHAVIOR_FLAG arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "SetBehaviorFlag", args, 2) };
}
auto SimpleSteeringController::tmp(GameBindings::desteer::entity::IMobileEntity arg0) -> GameBindings::desteer::controller::SimpleSteeringController
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto SimpleSteeringController::lm_new(GameBindings::desteer::entity::IMobileEntity arg0) -> GameBindings::desteer::controller::SimpleSteeringController
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto SimpleSteeringController::SetPursuitTarget(GameBindings::desteer::entity::IMobileEntity arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetPursuitTarget", args, 1) };
}
auto SimpleSteeringController::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SimpleSteeringController::SetObstacles(GameBindings::desteer::EntityGroup arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetObstacles", args, 1) };
}
auto SimpleSteeringController::SetArriveTarget(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetArriveTarget", args, 1) };
}
auto SimpleSteeringController::SetSeekTarget(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "SetSeekTarget", args, 1) };
}
auto SimpleSteeringController::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
