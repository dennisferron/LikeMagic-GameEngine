#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_TPS.hpp"

namespace GameBindings
{
	namespace TPS
	{

auto ThinPlateQuilt::getBendingEnergy() -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBendingEnergy", args, 0) };
}
auto ThinPlateQuilt::clearControlPoints() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clearControlPoints", args, 0) };
}
auto ThinPlateQuilt::addRegularization(GameBindings::double_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addRegularization", args, 1) };
}
auto ThinPlateQuilt::getRegularization() -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRegularization", args, 0) };
}
auto ThinPlateQuilt::numControlPoints() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "numControlPoints", args, 0) };
}
auto ThinPlateQuilt::heightAt(GameBindings::double_expr arg0, GameBindings::double_expr arg1) -> GameBindings::double_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "heightAt", args, 2) };
}
auto ThinPlateQuilt::removeControlPoint(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeControlPoint", args, 1) };
}
auto ThinPlateQuilt::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::TPS::Vec arg2, GameBindings::TPS::Vec arg3) -> GameBindings::TPS::ThinPlateQuilt
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto ThinPlateQuilt::getControlPoint(GameBindings::uint_expr arg0) -> GameBindings::TPS::ControlPointPtr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getControlPoint", args, 1) };
}
auto ThinPlateQuilt::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::TPS::Vec arg2, GameBindings::TPS::Vec arg3) -> GameBindings::TPS::ThinPlateQuilt
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto ThinPlateQuilt::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ThinPlateQuilt::refresh() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "refresh", args, 0) };
}
auto ThinPlateQuilt::addControlPoint(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::ControlPointPtr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addControlPoint", args, 1) };
}
auto ThinPlateQuilt::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ControlPoint::ref_pos() -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_pos", args, 0) };
}
auto ControlPoint::get_pos() -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_pos", args, 0) };
}
auto ControlPoint::tmp(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::ControlPoint
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto ControlPoint::lm_new(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::ControlPoint
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto ControlPoint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ControlPoint::set_pos(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_pos", args, 1) };
}
auto ControlPoint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto Vec::operator ==(GameBindings::TPS::Vec arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto Vec::operator /=(GameBindings::float_expr arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "/=", args, 1) };
}
auto Vec::operator *=(GameBindings::float_expr arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "*=", args, 1) };
}
auto Vec::operator +(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+", args, 1) };
}
auto Vec::operator +=(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+=", args, 1) };
}
auto Vec::ref_z() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_z", args, 0) };
}
auto Vec::ref_x() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_x", args, 0) };
}
auto Vec::get_z() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_z", args, 0) };
}
auto Vec::operator /(GameBindings::float_expr arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "/", args, 1) };
}
auto Vec::set_z(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_z", args, 1) };
}
auto Vec::operator -=(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-=", args, 1) };
}
auto Vec::len() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "len", args, 0) };
}
auto Vec::get_y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_y", args, 0) };
}
auto Vec::ref_y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_y", args, 0) };
}
auto Vec::operator *(GameBindings::float_expr arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "*", args, 1) };
}
auto Vec::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto Vec::lm_new() -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto Vec::lm_new(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto Vec::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto Vec::set_y(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_y", args, 1) };
}
auto Vec::tmp() -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto Vec::tmp(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto Vec::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto Vec::norm() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "norm", args, 0) };
}
auto Vec::get_x() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_x", args, 0) };
}
auto Vec::operator -() -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "-", args, 0) };
}
auto Vec::operator -(GameBindings::TPS::Vec arg0) -> GameBindings::TPS::Vec
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-", args, 1) };
}
auto Vec::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto Vec::set_x(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_x", args, 1) };
}

auto ControlPointPtr::get() -> GameBindings::TPS::ControlPoint
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get", args, 0) };
}
auto ControlPointPtr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ControlPointPtr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ThinPlateSpline::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ThinPlateSpline::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
