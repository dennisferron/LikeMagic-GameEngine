#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace io
		{

struct ISceneUserDataSerializer
{
    ::LM::ExprPtr expr;
    auto createUserData(GameBindings::irr::scene::ISceneNode) -> GameBindings::irr::io::IAttributes;
    auto OnReadUserData(GameBindings::irr::scene::ISceneNode, GameBindings::irr::io::IAttributes) -> GameBindings::void_expr;
    auto OnCreateNode(GameBindings::irr::scene::ISceneNode) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IAttributes
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedDataSerializer
{
    ::LM::ExprPtr expr;
    auto ref_on_createUserData() -> GameBindings::LangBlockExpr;
    auto get_on_createUserData() -> GameBindings::LangBlockExpr;
    auto set_on_createUserData(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto get_on_OnReadUserData() -> GameBindings::LangBlockExpr;
    auto set_on_OnReadUserData(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto ref_on_OnCreateNode() -> GameBindings::LangBlockExpr;
    auto get_on_OnCreateNode() -> GameBindings::LangBlockExpr;
    auto set_on_OnCreateNode(GameBindings::LangBlockExpr) -> GameBindings::LangBlockExpr;
    auto lm_delete() -> GameBindings::void_expr;
    auto ref_on_OnReadUserData() -> GameBindings::LangBlockExpr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
