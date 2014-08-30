#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_LM.hpp"

namespace GameBindings
{
	namespace LM
	{

auto TypeIndex::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto TypeIndex::description() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "description", args, 0) };
}
auto TypeIndex::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto Expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto Expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMarkable::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMarkable::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto MarkableObjGraph::number_of_children() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "number_of_children", args, 0) };
}
auto MarkableObjGraph::number_of_parents() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "number_of_parents", args, 0) };
}
auto MarkableObjGraph::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto MarkableObjGraph::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto TypeMirror::get_class_name() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_class_name", args, 0) };
}
auto TypeMirror::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto TypeMirror::get_instance_size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_instance_size", args, 0) };
}
auto TypeMirror::get_class_type() -> GameBindings::LM::TypeIndex
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_class_type", args, 0) };
}
auto TypeMirror::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto LangBlock::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto LangBlock::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto CallTarget::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto CallTarget::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
