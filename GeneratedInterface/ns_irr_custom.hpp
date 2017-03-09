#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace custom
		{

struct IEventReceiver
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedSceneNode
{
    ::LM::ExprPtr expr;
    auto getExampleVertices() -> GameBindings::irr::video::S3DVertex;
    auto setOnGetMaterialCount(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto setOnGetBoundingBox(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto setOnRender(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto setOnRegisterSceneNode(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto getExampleIndices() -> GameBindings::ushort_expr;
    auto tmp(GameBindings::irr::scene::ISceneNode, GameBindings::irr::scene::ISceneManager, GameBindings::int_expr) -> GameBindings::irr::custom::ScriptedSceneNode;
    auto setOnGetMaterial(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto lm_new(GameBindings::irr::scene::ISceneNode, GameBindings::irr::scene::ISceneManager, GameBindings::int_expr) -> GameBindings::irr::custom::ScriptedSceneNode;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct OrientationHelperSceneNode
{
    ::LM::ExprPtr expr;
    auto rotateZToDirectionCameraVector(GameBindings::irr::scene::ICameraSceneNode, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto rotateZToDirectionCamera(GameBindings::irr::scene::ICameraSceneNode) -> GameBindings::void_expr;
    auto rotateZToDirectionVectorVector(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto tmp(GameBindings::float_expr, GameBindings::irr::scene::ISceneNode, GameBindings::irr::scene::ISceneManager, GameBindings::int_expr) -> GameBindings::irr::custom::OrientationHelperSceneNode;
    auto lm_new(GameBindings::float_expr, GameBindings::irr::scene::ISceneNode, GameBindings::irr::scene::ISceneManager, GameBindings::int_expr) -> GameBindings::irr::custom::OrientationHelperSceneNode;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptedEventReceiver
{
    ::LM::ExprPtr expr;
    auto OnEvent(GameBindings::irr::gui::SEvent) -> GameBindings::bool_expr;
    auto isKeyDown(GameBindings::irr::gui::EKEY_CODE) -> GameBindings::bool_expr;
    auto setOnEvent(GameBindings::LangBlockExpr) -> GameBindings::void_expr;
    auto tmp(GameBindings::LangBlockExpr) -> GameBindings::irr::custom::ScriptedEventReceiver;
    auto lm_new(GameBindings::LangBlockExpr) -> GameBindings::irr::custom::ScriptedEventReceiver;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
