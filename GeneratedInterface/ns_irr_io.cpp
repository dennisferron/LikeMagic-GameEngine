#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_irr_io.hpp"
#include "ns_irr_scene.hpp"
#include "ns_global.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace io
		{

auto ISceneUserDataSerializer::createUserData(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::irr::io::IAttributes
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createUserData", args, 1) };
}
auto ISceneUserDataSerializer::OnReadUserData(GameBindings::irr::scene::ISceneNode arg0, GameBindings::irr::io::IAttributes arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "OnReadUserData", args, 2) };
}
auto ISceneUserDataSerializer::OnCreateNode(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "OnCreateNode", args, 1) };
}
auto ISceneUserDataSerializer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISceneUserDataSerializer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IAttributes::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IAttributes::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptedDataSerializer::ref_on_createUserData() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_on_createUserData", args, 0) };
}
auto ScriptedDataSerializer::get_on_createUserData() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_on_createUserData", args, 0) };
}
auto ScriptedDataSerializer::set_on_createUserData(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_on_createUserData", args, 1) };
}
auto ScriptedDataSerializer::set_on_OnReadUserData(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_on_OnReadUserData", args, 1) };
}
auto ScriptedDataSerializer::ref_on_OnCreateNode() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_on_OnCreateNode", args, 0) };
}
auto ScriptedDataSerializer::get_on_OnCreateNode() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_on_OnCreateNode", args, 0) };
}
auto ScriptedDataSerializer::ref_on_OnReadUserData() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_on_OnReadUserData", args, 0) };
}
auto ScriptedDataSerializer::set_on_OnCreateNode(GameBindings::LangBlockExpr arg0) -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_on_OnCreateNode", args, 1) };
}
auto ScriptedDataSerializer::get_on_OnReadUserData() -> GameBindings::LangBlockExpr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_on_OnReadUserData", args, 0) };
}
auto ScriptedDataSerializer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptedDataSerializer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
