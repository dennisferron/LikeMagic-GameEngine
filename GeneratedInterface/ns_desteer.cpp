#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_desteer_entity.hpp"
#include "ns_desteer.hpp"

namespace GameBindings
{
	namespace desteer
	{

auto MobIterator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto MobIterator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EntityIterator::operator_increment(GameBindings::int_expr arg0) -> GameBindings::desteer::EntityIterator
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "++", args, 1) };
}
auto EntityIterator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EntityIterator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EntityGroup::at_nc(GameBindings::uint_expr arg0) -> GameBindings::desteer::entity::IBaseEntity
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto EntityGroup::at_c(GameBindings::uint_expr arg0) -> GameBindings::desteer::entity::IBaseEntity
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto EntityGroup::push_back(GameBindings::desteer::entity::IBaseEntity arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_back", args, 1) };
}
auto EntityGroup::clear() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clear", args, 0) };
}
auto EntityGroup::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto EntityGroup::tmp() -> GameBindings::desteer::EntityGroup
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto EntityGroup::lm_new() -> GameBindings::desteer::EntityGroup
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto EntityGroup::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EntityGroup::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto MobGroup::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto MobGroup::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto BehaviorIterator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto BehaviorIterator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto BehaviorGroup::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto BehaviorGroup::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
