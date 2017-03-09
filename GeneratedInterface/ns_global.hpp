#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{

struct ScriptUtil
{
    ::LM::ExprPtr expr;
    auto is_nan(GameBindings::float_expr) -> GameBindings::bool_expr;
    auto get_float_const_ref(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_random_float_array(GameBindings::int_expr, GameBindings::int_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_random_float(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_string(GameBindings::string_expr) -> GameBindings::string_expr;
    auto get_int(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_double(GameBindings::double_expr) -> GameBindings::double_expr;
    auto get_void_ptr(GameBindings::void_expr) -> GameBindings::void_expr;
    auto get_true() -> GameBindings::bool_expr;
    auto get_test_ptr(GameBindings::string_expr) -> GameBindings::void_expr;
    auto get_null_ptr() -> GameBindings::void_expr;
    auto get_false() -> GameBindings::bool_expr;
    auto ptr_addr_to_str(GameBindings::void_expr) -> GameBindings::string_expr;
    auto get_uintp_field() -> GameBindings::uint_expr;
    auto print_float_array(GameBindings::float_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto get_float(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_uintp_field(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto ref_ucharp_field() -> GameBindings::uchar_expr;
    auto ref_voidp_field() -> GameBindings::void_expr;
    auto set_intp_field(GameBindings::int_expr) -> GameBindings::int_expr;
    auto get_voidp_field() -> GameBindings::void_expr;
    auto set_voidp_field(GameBindings::void_expr) -> GameBindings::void_expr;
    auto ref_uintp_field() -> GameBindings::uint_expr;
    auto get_ucharp_field() -> GameBindings::uchar_expr;
    auto tmp() -> GameBindings::ScriptUtil;
    auto ref_charp_field() -> GameBindings::char_expr;
    auto set_ucharp_field(GameBindings::uchar_expr) -> GameBindings::uchar_expr;
    auto lm_new() -> GameBindings::ScriptUtil;
    auto get_charp_field() -> GameBindings::char_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_intp_field() -> GameBindings::int_expr;
    auto set_charp_field(GameBindings::char_expr) -> GameBindings::char_expr;
    auto ref_intp_field() -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct NativeArray_of_double
{
    ::LM::ExprPtr expr;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::double_expr;
    auto at_put(MissingType /* C++ unsigned long long (end) */ , GameBindings::double_expr) -> GameBindings::void_expr;
    auto begin_nc() -> GameBindings::double_expr;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto begin_c() -> GameBindings::double_expr;
    auto tmp(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::NativeArray_of_double;
    auto tmp(MissingType /* C++ unsigned long long (end) */ , GameBindings::double_expr) -> GameBindings::NativeArray_of_double;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::double_expr;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::NativeArray_of_double;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ , GameBindings::double_expr) -> GameBindings::NativeArray_of_double;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct NativeArray_of_float
{
    ::LM::ExprPtr expr;
    auto at_c(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::float_expr;
    auto at_put(MissingType /* C++ unsigned long long (end) */ , GameBindings::float_expr) -> GameBindings::void_expr;
    auto begin_nc() -> GameBindings::float_expr;
    auto size() -> MissingType /* C++ unsigned long long */ ;
    auto begin_c() -> GameBindings::float_expr;
    auto tmp(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::NativeArray_of_float;
    auto tmp(MissingType /* C++ unsigned long long (end) */ , GameBindings::float_expr) -> GameBindings::NativeArray_of_float;
    auto at_nc(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::float_expr;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ ) -> GameBindings::NativeArray_of_float;
    auto lm_new(MissingType /* C++ unsigned long long (end) */ , GameBindings::float_expr) -> GameBindings::NativeArray_of_float;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct float_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct double_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct Delegate
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct char_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ushort_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct long_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct wchar_t_expr
{
    ::LM::ExprPtr expr;
    auto wchar_to_string() -> GameBindings::string_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct short_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct int_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct uchar_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct uint_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct void_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct bool_expr
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct string_expr
{
    ::LM::ExprPtr expr;
    auto c_str() -> GameBindings::char_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct TypeSystem
{
    ::LM::ExprPtr expr;
    auto global_namespace() -> GameBindings::LM::TypeMirror;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ulong
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct wstring_expr
{
    ::LM::ExprPtr expr;
    auto c_str() -> GameBindings::wchar_t_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct LangBlockExpr
{
    ::LM::ExprPtr expr;
};struct BottomPtr
{
    ::LM::ExprPtr expr;
};

}
