#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_irr_video.hpp"
#include "ns_irr_gui.hpp"
#include "ns_irr_core.hpp"
#include "ns_irr_scene.hpp"
#include "ns_global.hpp"
#include "ns_irr_custom.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace custom
		{

auto IEventReceiver::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IEventReceiver::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedSceneNode::getExampleVertices() -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getExampleVertices", args, 0) };
}
auto ScriptedSceneNode::setOnGetMaterialCount(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnGetMaterialCount", args, 1) };
}
auto ScriptedSceneNode::setOnGetBoundingBox(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnGetBoundingBox", args, 1) };
}
auto ScriptedSceneNode::setOnRender(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnRender", args, 1) };
}
auto ScriptedSceneNode::setOnRegisterSceneNode(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnRegisterSceneNode", args, 1) };
}
auto ScriptedSceneNode::getExampleIndices() -> GameBindings::ushort_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getExampleIndices", args, 0) };
}
auto ScriptedSceneNode::tmp(GameBindings::irr::scene::ISceneNode arg0, GameBindings::irr::scene::ISceneManager arg1, GameBindings::int_expr arg2) -> GameBindings::irr::custom::ScriptedSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto ScriptedSceneNode::setOnGetMaterial(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnGetMaterial", args, 1) };
}
auto ScriptedSceneNode::lm_new(GameBindings::irr::scene::ISceneNode arg0, GameBindings::irr::scene::ISceneManager arg1, GameBindings::int_expr arg2) -> GameBindings::irr::custom::ScriptedSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto ScriptedSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto OrientationHelperSceneNode::rotateZToDirectionCameraVector(GameBindings::irr::scene::ICameraSceneNode arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotateZToDirectionCameraVector", args, 2) };
}
auto OrientationHelperSceneNode::rotateZToDirectionCamera(GameBindings::irr::scene::ICameraSceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "rotateZToDirectionCamera", args, 1) };
}
auto OrientationHelperSceneNode::rotateZToDirectionVectorVector(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotateZToDirectionVectorVector", args, 2) };
}
auto OrientationHelperSceneNode::tmp(GameBindings::float_expr arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::irr::scene::ISceneManager arg2, GameBindings::int_expr arg3) -> GameBindings::irr::custom::OrientationHelperSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto OrientationHelperSceneNode::lm_new(GameBindings::float_expr arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::irr::scene::ISceneManager arg2, GameBindings::int_expr arg3) -> GameBindings::irr::custom::OrientationHelperSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto OrientationHelperSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto OrientationHelperSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedEventReceiver::OnEvent(GameBindings::irr::gui::SEvent arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "OnEvent", args, 1) };
}
auto ScriptedEventReceiver::isKeyDown(GameBindings::irr::gui::EKEY_CODE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isKeyDown", args, 1) };
}
auto ScriptedEventReceiver::setOnEvent(GameBindings::LangBlockExpr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setOnEvent", args, 1) };
}
auto ScriptedEventReceiver::tmp(GameBindings::LangBlockExpr arg0) -> GameBindings::irr::custom::ScriptedEventReceiver
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto ScriptedEventReceiver::lm_new(GameBindings::LangBlockExpr arg0) -> GameBindings::irr::custom::ScriptedEventReceiver
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto ScriptedEventReceiver::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedEventReceiver::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
