#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace desteer
	{
		namespace controller
		{

struct SimpleSteeringController
{
    ::LM::ExprPtr expr;
    auto SetObstacles(GameBindings::desteer::EntityGroup) -> GameBindings::void_expr;
    auto SetArriveTarget(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto SetSeekTarget(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto SetBehaviorFlag(GameBindings::desteer::controller::EBEHAVIOR_FLAG, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto SetPursuitTarget(GameBindings::desteer::entity::IMobileEntity) -> GameBindings::void_expr;
    auto tmp(GameBindings::desteer::entity::IMobileEntity) -> GameBindings::desteer::controller::SimpleSteeringController;
    auto SetHideTarget(GameBindings::desteer::entity::IMobileEntity) -> GameBindings::void_expr;
    auto lm_new(GameBindings::desteer::entity::IMobileEntity) -> GameBindings::desteer::controller::SimpleSteeringController;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EBEHAVIOR_FLAG
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::desteer::controller::EBEHAVIOR_FLAG) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::desteer::controller::EBEHAVIOR_FLAG) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ISteeringController
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto Calculate() -> GameBindings::irr::core::vector3df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
