#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace std
	{

struct vector_of_float_iterator
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_double_iterator
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_int
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_float
{
    ::LM::ExprPtr expr;
    auto push_back(GameBindings::float_expr) -> GameBindings::void_expr;
    auto at_put(MissingType /* C++ unsigned long long (end) */ , GameBindings::float_expr) -> GameBindings::void_expr;
    auto begin_nc() -> GameBindings::std::vector_of_float_iterator;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::float_expr;
    auto begin_c() -> MissingType /* C++ __gnu_cxx::__normal_iterator<float const*, std::vector<float, std::allocator<float> > > */ ;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto tmp() -> GameBindings::std::vector_of_float;
    auto tmp(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::std::vector_of_float;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::float_expr;
    auto lm_new() -> GameBindings::std::vector_of_float;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::std::vector_of_float;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_short
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_ushort
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_double
{
    ::LM::ExprPtr expr;
    auto push_back(GameBindings::double_expr) -> GameBindings::void_expr;
    auto at_put(MissingType /* C++ unsigned long long (end) */ , GameBindings::double_expr) -> GameBindings::void_expr;
    auto begin_nc() -> GameBindings::std::vector_of_double_iterator;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::double_expr;
    auto begin_c() -> MissingType /* C++ __gnu_cxx::__normal_iterator<double const*, std::vector<double, std::allocator<double> > > */ ;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto tmp() -> GameBindings::std::vector_of_double;
    auto tmp(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::std::vector_of_double;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::double_expr;
    auto lm_new() -> GameBindings::std::vector_of_double;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::std::vector_of_double;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_string
{
    ::LM::ExprPtr expr;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::string_expr;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::string_expr;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_uint
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
