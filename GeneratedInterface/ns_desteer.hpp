#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace desteer
	{

struct BehaviorIterator
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EntityGroup
{
    ::LM::ExprPtr expr;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::desteer::entity::IBaseEntity;
    auto push_back(GameBindings::desteer::entity::IBaseEntity) -> GameBindings::void_expr;
    auto clear() -> GameBindings::void_expr;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto tmp() -> GameBindings::desteer::EntityGroup;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::desteer::entity::IBaseEntity;
    auto lm_new() -> GameBindings::desteer::EntityGroup;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct MobGroup
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct MobIterator
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EntityIterator
{
    ::LM::ExprPtr expr;
    auto operator_increment(GameBindings::int_expr) -> GameBindings::desteer::EntityIterator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct BehaviorGroup
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
