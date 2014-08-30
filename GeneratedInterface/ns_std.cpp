#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_std.hpp"

namespace GameBindings
{
	namespace std
	{

auto vector_of_string::at_nc(GameBindings::uint_expr arg0) -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto vector_of_string::at_c(GameBindings::uint_expr arg0) -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto vector_of_string::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto vector_of_string::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_string::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_ushort::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_ushort::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_short::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_short::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_float_iterator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_float_iterator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_double::at_put(GameBindings::uint_expr arg0, GameBindings::double_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "at_put", args, 2) };
}
auto vector_of_double::begin_nc() -> GameBindings::std::vector_of_double_iterator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_nc", args, 0) };
}
auto vector_of_double::at_nc(GameBindings::uint_expr arg0) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto vector_of_double::push_back(GameBindings::double_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_back", args, 1) };
}
auto vector_of_double::at_c(GameBindings::uint_expr arg0) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto vector_of_double::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto vector_of_double::tmp() -> GameBindings::std::vector_of_double
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto vector_of_double::tmp(GameBindings::uint_expr arg0) -> GameBindings::std::vector_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto vector_of_double::lm_new() -> GameBindings::std::vector_of_double
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto vector_of_double::lm_new(GameBindings::uint_expr arg0) -> GameBindings::std::vector_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto vector_of_double::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_double::begin_c() -> MissingType /* C++ __gnu_cxx::__normal_iterator<double const*, std::vector<double, std::allocator<double> > > */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_c", args, 0) };
}
auto vector_of_double::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_int::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_int::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_uint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_uint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_float::at_put(GameBindings::uint_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "at_put", args, 2) };
}
auto vector_of_float::begin_nc() -> GameBindings::std::vector_of_float_iterator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_nc", args, 0) };
}
auto vector_of_float::at_nc(GameBindings::uint_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto vector_of_float::push_back(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_back", args, 1) };
}
auto vector_of_float::at_c(GameBindings::uint_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto vector_of_float::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto vector_of_float::tmp() -> GameBindings::std::vector_of_float
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto vector_of_float::tmp(GameBindings::uint_expr arg0) -> GameBindings::std::vector_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto vector_of_float::lm_new() -> GameBindings::std::vector_of_float
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto vector_of_float::lm_new(GameBindings::uint_expr arg0) -> GameBindings::std::vector_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto vector_of_float::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_float::begin_c() -> MissingType /* C++ __gnu_cxx::__normal_iterator<float const*, std::vector<float, std::allocator<float> > > */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_c", args, 0) };
}
auto vector_of_float::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_double_iterator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_double_iterator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
