#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace TPS
	{

struct ThinPlateQuilt
{
    ::LM::ExprPtr expr;
    auto getBendingEnergy() -> GameBindings::double_expr;
    auto clearControlPoints() -> GameBindings::void_expr;
    auto addRegularization(GameBindings::double_expr) -> GameBindings::void_expr;
    auto getRegularization() -> GameBindings::double_expr;
    auto numControlPoints() -> GameBindings::uint_expr;
    auto heightAt(GameBindings::double_expr, GameBindings::double_expr) -> GameBindings::double_expr;
    auto removeControlPoint(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr, GameBindings::TPS::Vec, GameBindings::TPS::Vec) -> GameBindings::TPS::ThinPlateQuilt;
    auto getControlPoint(GameBindings::uint_expr) -> GameBindings::TPS::ControlPointPtr;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr, GameBindings::TPS::Vec, GameBindings::TPS::Vec) -> GameBindings::TPS::ThinPlateQuilt;
    auto lm_delete() -> GameBindings::void_expr;
    auto refresh() -> GameBindings::void_expr;
    auto addControlPoint(GameBindings::TPS::Vec) -> GameBindings::TPS::ControlPointPtr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ControlPoint
{
    ::LM::ExprPtr expr;
    auto ref_pos() -> GameBindings::TPS::Vec;
    auto get_pos() -> GameBindings::TPS::Vec;
    auto tmp(GameBindings::TPS::Vec) -> GameBindings::TPS::ControlPoint;
    auto lm_new(GameBindings::TPS::Vec) -> GameBindings::TPS::ControlPoint;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_pos(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct Vec
{
    ::LM::ExprPtr expr;
    auto operator ==(GameBindings::TPS::Vec) -> GameBindings::bool_expr;
    auto operator /=(GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto operator *=(GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto operator +(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto operator +=(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto ref_z() -> GameBindings::float_expr;
    auto ref_x() -> GameBindings::float_expr;
    auto get_z() -> GameBindings::float_expr;
    auto operator /(GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto set_z(GameBindings::float_expr) -> GameBindings::float_expr;
    auto operator -=(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto len() -> GameBindings::float_expr;
    auto get_y() -> GameBindings::float_expr;
    auto ref_y() -> GameBindings::float_expr;
    auto operator *(GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto lm_delete() -> GameBindings::void_expr;
    auto lm_new() -> GameBindings::TPS::Vec;
    auto lm_new(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto set_y(GameBindings::float_expr) -> GameBindings::float_expr;
    auto tmp() -> GameBindings::TPS::Vec;
    auto tmp(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::TPS::Vec;
    auto norm() -> GameBindings::float_expr;
    auto get_x() -> GameBindings::float_expr;
    auto operator -() -> GameBindings::TPS::Vec;
    auto operator -(GameBindings::TPS::Vec) -> GameBindings::TPS::Vec;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto set_x(GameBindings::float_expr) -> GameBindings::float_expr;
};struct ControlPointPtr
{
    ::LM::ExprPtr expr;
    auto get() -> GameBindings::TPS::ControlPoint;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ThinPlateSpline
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
