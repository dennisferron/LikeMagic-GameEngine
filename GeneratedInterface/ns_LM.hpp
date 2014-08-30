#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace LM
	{

struct TypeIndex
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto description() -> GameBindings::string_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct Expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IMarkable
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct MarkableObjGraph
{
    ::LM::ExprPtr expr;
    auto number_of_children() -> GameBindings::uint_expr;
    auto number_of_parents() -> GameBindings::uint_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct TypeMirror
{
    ::LM::ExprPtr expr;
    auto get_class_name() -> GameBindings::string_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_instance_size() -> GameBindings::uint_expr;
    auto get_class_type() -> GameBindings::LM::TypeIndex;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct LangBlock
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct CallTarget
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
