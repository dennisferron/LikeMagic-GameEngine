#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_LM.hpp"
#include "ns_global.hpp"

namespace GameBindings
{

auto ScriptUtil::is_nan(GameBindings::float_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "is_nan", args, 1) };
}
auto ScriptUtil::get_float_const_ref(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_float_const_ref", args, 1) };
}
auto ScriptUtil::get_random_float_array(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "get_random_float_array", args, 4) };
}
auto ScriptUtil::get_random_float(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "get_random_float", args, 2) };
}
auto ScriptUtil::get_string(GameBindings::string_expr arg0) -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_string", args, 1) };
}
auto ScriptUtil::get_int(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_int", args, 1) };
}
auto ScriptUtil::get_double(GameBindings::double_expr arg0) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_double", args, 1) };
}
auto ScriptUtil::get_void_ptr(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_void_ptr", args, 1) };
}
auto ScriptUtil::get_true() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_true", args, 0) };
}
auto ScriptUtil::get_test_ptr(GameBindings::string_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_test_ptr", args, 1) };
}
auto ScriptUtil::get_null_ptr() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_null_ptr", args, 0) };
}
auto ScriptUtil::get_false() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_false", args, 0) };
}
auto ScriptUtil::ptr_addr_to_str(GameBindings::void_expr arg0) -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "ptr_addr_to_str", args, 1) };
}
auto ScriptUtil::get_uintp_field() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_uintp_field", args, 0) };
}
auto ScriptUtil::print_float_array(GameBindings::float_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "print_float_array", args, 3) };
}
auto ScriptUtil::get_float(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_float", args, 1) };
}
auto ScriptUtil::set_uintp_field(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_uintp_field", args, 1) };
}
auto ScriptUtil::ref_ucharp_field() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_ucharp_field", args, 0) };
}
auto ScriptUtil::ref_voidp_field() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_voidp_field", args, 0) };
}
auto ScriptUtil::set_intp_field(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_intp_field", args, 1) };
}
auto ScriptUtil::get_voidp_field() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_voidp_field", args, 0) };
}
auto ScriptUtil::set_voidp_field(GameBindings::void_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_voidp_field", args, 1) };
}
auto ScriptUtil::ref_uintp_field() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_uintp_field", args, 0) };
}
auto ScriptUtil::get_ucharp_field() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ucharp_field", args, 0) };
}
auto ScriptUtil::tmp() -> GameBindings::ScriptUtil
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ScriptUtil::ref_charp_field() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_charp_field", args, 0) };
}
auto ScriptUtil::set_ucharp_field(GameBindings::uchar_expr arg0) -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ucharp_field", args, 1) };
}
auto ScriptUtil::lm_new() -> GameBindings::ScriptUtil
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ScriptUtil::get_charp_field() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_charp_field", args, 0) };
}
auto ScriptUtil::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptUtil::get_intp_field() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_intp_field", args, 0) };
}
auto ScriptUtil::set_charp_field(GameBindings::char_expr arg0) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_charp_field", args, 1) };
}
auto ScriptUtil::ref_intp_field() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_intp_field", args, 0) };
}
auto ScriptUtil::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto NativeArray_of_double::at_c(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto NativeArray_of_double::at_put(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::double_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "at_put", args, 2) };
}
auto NativeArray_of_double::begin_nc() -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_nc", args, 0) };
}
auto NativeArray_of_double::size() -> MissingType /* C++ unsigned long long */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto NativeArray_of_double::begin_c() -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_c", args, 0) };
}
auto NativeArray_of_double::tmp(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::NativeArray_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto NativeArray_of_double::tmp(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::double_expr arg1) -> GameBindings::NativeArray_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto NativeArray_of_double::at_nc(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto NativeArray_of_double::lm_new(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::NativeArray_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto NativeArray_of_double::lm_new(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::double_expr arg1) -> GameBindings::NativeArray_of_double
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto NativeArray_of_double::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto NativeArray_of_double::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto NativeArray_of_float::at_c(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_c", args, 1) };
}
auto NativeArray_of_float::at_put(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "at_put", args, 2) };
}
auto NativeArray_of_float::begin_nc() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_nc", args, 0) };
}
auto NativeArray_of_float::size() -> MissingType /* C++ unsigned long long */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto NativeArray_of_float::begin_c() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_c", args, 0) };
}
auto NativeArray_of_float::tmp(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::NativeArray_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto NativeArray_of_float::tmp(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::float_expr arg1) -> GameBindings::NativeArray_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto NativeArray_of_float::at_nc(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "at_nc", args, 1) };
}
auto NativeArray_of_float::lm_new(MissingType /* C++ unsigned long long (end) */  arg0) -> GameBindings::NativeArray_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto NativeArray_of_float::lm_new(MissingType /* C++ unsigned long long (end) */  arg0, GameBindings::float_expr arg1) -> GameBindings::NativeArray_of_float
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto NativeArray_of_float::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto NativeArray_of_float::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto float_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto float_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto double_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto double_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto Delegate::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto Delegate::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto char_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto char_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ushort_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ushort_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto long_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto long_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto wchar_t_expr::wchar_to_string() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "wchar_to_string", args, 0) };
}
auto wchar_t_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto wchar_t_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto short_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto short_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto int_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto int_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto uchar_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto uchar_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto uint_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto uint_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto void_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto void_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto bool_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto bool_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto string_expr::c_str() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "c_str", args, 0) };
}
auto string_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto string_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto TypeSystem::global_namespace() -> GameBindings::LM::TypeMirror
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "global_namespace", args, 0) };
}
auto TypeSystem::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto TypeSystem::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ulong::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ulong::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto wstring_expr::c_str() -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "c_str", args, 0) };
}
auto wstring_expr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto wstring_expr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}



}
