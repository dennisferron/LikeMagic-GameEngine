#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace core
		{

struct ListOfAnim
{
    ::LM::ExprPtr expr;
    auto getLast_nc() -> GameBindings::irr::core::ListOfAnimIter;
    auto getLast_c() -> GameBindings::irr::core::ListOfAnimConstIter;
    auto begin_nc() -> GameBindings::irr::core::ListOfAnimIter;
    auto push_back(GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto push_front(GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto insert_before(GameBindings::irr::core::ListOfAnimIter, GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto insert_after(GameBindings::irr::core::ListOfAnimIter, GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto getSize() -> GameBindings::uint_expr;
    auto end_nc() -> GameBindings::irr::core::ListOfAnimIter;
    auto end_c() -> GameBindings::irr::core::ListOfAnimConstIter;
    auto size() -> GameBindings::uint_expr;
    auto begin_c() -> GameBindings::irr::core::ListOfAnimConstIter;
    auto erase(GameBindings::irr::core::ListOfAnimIter) -> GameBindings::irr::core::ListOfAnimIter;
    auto swap(GameBindings::irr::core::ListOfAnim) -> GameBindings::void_expr;
    auto empty() -> GameBindings::bool_expr;
    auto clear() -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct recti
{
    ::LM::ExprPtr expr;
    auto tmpWithXYXY(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::recti;
    auto newWithXYXY(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::recti;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::recti;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::recti;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct matrix4
{
    ::LM::ExprPtr expr;
    auto transformVectOfFloats(GameBindings::float_expr, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto transformVect(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto transformVect(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto tmp() -> GameBindings::irr::core::matrix4;
    auto tmp(MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */ ) -> GameBindings::irr::core::matrix4;
    auto tmp(GameBindings::irr::core::matrix4, MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */ ) -> GameBindings::irr::core::matrix4;
    auto lm_new() -> GameBindings::irr::core::matrix4;
    auto lm_new(MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */ ) -> GameBindings::irr::core::matrix4;
    auto lm_new(GameBindings::irr::core::matrix4, MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */ ) -> GameBindings::irr::core::matrix4;
    auto lm_delete() -> GameBindings::void_expr;
    auto getRotationDegrees() -> GameBindings::irr::core::vector3df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct irrFsStr
{
    ::LM::ExprPtr expr;
    auto tmpFromCStr(GameBindings::char_expr) -> GameBindings::irr::core::irrFsStr;
    auto newFromCStr(GameBindings::char_expr) -> GameBindings::irr::core::irrFsStr;
    auto tmp() -> GameBindings::irr::core::irrFsStr;
    auto tmp(GameBindings::char_expr) -> GameBindings::irr::core::irrFsStr;
    auto lm_new() -> GameBindings::irr::core::irrFsStr;
    auto lm_new(GameBindings::char_expr) -> GameBindings::irr::core::irrFsStr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct stringw
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::irr::core::stringw;
    auto tmp(GameBindings::wchar_t_expr) -> GameBindings::irr::core::stringw;
    auto lm_new() -> GameBindings::irr::core::stringw;
    auto lm_new(GameBindings::wchar_t_expr) -> GameBindings::irr::core::stringw;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct aabbox3df
{
    ::LM::ExprPtr expr;
    auto isPointTotalInside(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto isPointInside(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto isEmpty() -> GameBindings::bool_expr;
    auto getVolume() -> GameBindings::float_expr;
    auto getExtent() -> GameBindings::irr::core::vector3df;
    auto repair() -> GameBindings::void_expr;
    auto getEdges(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto getArea() -> GameBindings::float_expr;
    auto getInterpolated(GameBindings::irr::core::aabbox3df, GameBindings::float_expr) -> GameBindings::irr::core::aabbox3df;
    auto addInternalBox(GameBindings::irr::core::aabbox3df) -> GameBindings::void_expr;
    auto operator ==(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto ref_MinEdge() -> GameBindings::irr::core::vector3df;
    auto set_MaxEdge(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto tmpWithMinMaxXYZ(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::aabbox3df;
    auto tmpWithMinMax(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto tmpWithOnePoint(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto set_MinEdge(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto newWithOnePoint(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto classifyPlaneRelation(GameBindings::irr::core::plane3df) -> GameBindings::irr::core::EIntersectionRelation3D;
    auto get_MaxEdge() -> GameBindings::irr::core::vector3df;
    auto intersectsWithBox(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto tmp() -> GameBindings::irr::core::aabbox3df;
    auto tmp(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto tmp(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::aabbox3df;
    auto isFullInside(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto lm_new() -> GameBindings::irr::core::aabbox3df;
    auto lm_new(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto lm_new(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::aabbox3df;
    auto newWithMinMaxXYZ(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::aabbox3df;
    auto operator !=(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto ref_MaxEdge() -> GameBindings::irr::core::vector3df;
    auto getCenter() -> GameBindings::irr::core::vector3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto newWithMinMax(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::aabbox3df;
    auto get_MinEdge() -> GameBindings::irr::core::vector3df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct EIntersectionRelation3D
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct plane3df
{
    ::LM::ExprPtr expr;
    auto setPlaneFromNormalAndDistance(GameBindings::irr::core::vector3df, GameBindings::float_expr) -> GameBindings::void_expr;
    auto setPlaneFromPoints(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto operator ==(GameBindings::irr::core::plane3df) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::core::plane3df) -> GameBindings::bool_expr;
    auto isFrontFacing(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto getMemberPoint() -> GameBindings::irr::core::vector3df;
    auto setPlaneFromPointAndNormal(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto getKnownIntersectionWithLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::float_expr;
    auto getIntersectionWithPlane(GameBindings::irr::core::plane3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto getIntersectionWithLimitedLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto getDistanceTo(GameBindings::irr::core::vector3df) -> GameBindings::float_expr;
    auto existsIntersection(GameBindings::irr::core::plane3df) -> GameBindings::bool_expr;
    auto ref_Normal() -> GameBindings::irr::core::vector3df;
    auto set_Normal(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto ref_D() -> GameBindings::float_expr;
    auto get_D() -> GameBindings::float_expr;
    auto tmpFromPxPyPzNxNyNz(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::plane3df;
    auto newFromPointAndNormal(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::plane3df;
    auto newFromPxPyPzNxNyNz(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::plane3df;
    auto recalculateD(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto set_D(GameBindings::float_expr) -> GameBindings::float_expr;
    auto newFromPoints(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::plane3df;
    auto newFromNormalAndDistance(GameBindings::irr::core::vector3df, GameBindings::float_expr) -> GameBindings::irr::core::plane3df;
    auto getIntersectionWithLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto tmpFromNormalAndDistance(GameBindings::irr::core::vector3df, GameBindings::float_expr) -> GameBindings::irr::core::plane3df;
    auto tmpFromPoints(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::plane3df;
    auto get_Normal() -> GameBindings::irr::core::vector3df;
    auto classifyPointRelation(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::EIntersectionRelation3D;
    auto tmp() -> GameBindings::irr::core::plane3df;
    auto tmpFromPointAndNormal(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::plane3df;
    auto getIntersectionWithPlanes(GameBindings::irr::core::plane3df, GameBindings::irr::core::plane3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto lm_new() -> GameBindings::irr::core::plane3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ListOfAnimConstIter
{
    ::LM::ExprPtr expr;
    auto operator +(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimConstIter;
    auto operator_increment(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimConstIter;
    auto operator -(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimConstIter;
    auto operator_decrement(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimConstIter;
    auto operator *() -> GameBindings::irr::scene::ISceneNodeAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ListOfAnimIter
{
    ::LM::ExprPtr expr;
    auto operator +(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimIter;
    auto operator_increment(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimIter;
    auto operator -(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimIter;
    auto operator_decrement(GameBindings::int_expr) -> GameBindings::irr::core::ListOfAnimIter;
    auto operator *() -> GameBindings::irr::scene::ISceneNodeAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct triangle3df
{
    ::LM::ExprPtr expr;
    auto operator ==(GameBindings::irr::core::triangle3df) -> GameBindings::bool_expr;
    auto set(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto isTotalOutsideBox(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto isPointInsideFast(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto isPointInside(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto getIntersectionWithLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto getIntersectionOfPlaneWithLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto closestPointOnTriangle(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto isTotalInsideBox(GameBindings::irr::core::aabbox3df) -> GameBindings::bool_expr;
    auto ref_pointC() -> GameBindings::irr::core::vector3df;
    auto get_pointC() -> GameBindings::irr::core::vector3df;
    auto ref_pointB() -> GameBindings::irr::core::vector3df;
    auto getPlane() -> GameBindings::irr::core::plane3df;
    auto get_pointB() -> GameBindings::irr::core::vector3df;
    auto set_pointB(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto getIntersectionWithLimitedLine(GameBindings::irr::core::line3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto ref_pointA() -> GameBindings::irr::core::vector3df;
    auto get_pointA() -> GameBindings::irr::core::vector3df;
    auto tmp() -> GameBindings::irr::core::triangle3df;
    auto tmp(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::triangle3df;
    auto getNormal() -> GameBindings::irr::core::vector3df;
    auto getArea() -> GameBindings::float_expr;
    auto lm_new() -> GameBindings::irr::core::triangle3df;
    auto lm_new(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::triangle3df;
    auto operator !=(GameBindings::irr::core::triangle3df) -> GameBindings::bool_expr;
    auto set_pointC(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto isFrontFacing(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto set_pointA(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct line3df
{
    ::LM::ExprPtr expr;
    auto operator +=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::line3df;
    auto operator +(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::line3df;
    auto getMiddle() -> GameBindings::irr::core::vector3df;
    auto getLengthSQ() -> GameBindings::float_expr;
    auto getVector() -> GameBindings::irr::core::vector3df;
    auto getLength() -> GameBindings::float_expr;
    auto operator -=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::line3df;
    auto getIntersectionWithSphere(GameBindings::irr::core::vector3df, GameBindings::float_expr, GameBindings::double_expr) -> GameBindings::bool_expr;
    auto ref_end() -> GameBindings::irr::core::vector3df;
    auto operator ==(GameBindings::irr::core::line3df) -> GameBindings::bool_expr;
    auto getClosestPoint(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto set_end(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto get_end() -> GameBindings::irr::core::vector3df;
    auto operator -(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::line3df;
    auto ref_start() -> GameBindings::irr::core::vector3df;
    auto get_start() -> GameBindings::irr::core::vector3df;
    auto operator !=(GameBindings::irr::core::line3df) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto isPointBetweenStartAndEnd(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto set_start(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
};struct rectf
{
    ::LM::ExprPtr expr;
    auto ref_LowerRightCorner() -> GameBindings::irr::core::vector2df;
    auto get_UpperLeftCorner() -> GameBindings::irr::core::vector2df;
    auto set_UpperLeftCorner(GameBindings::irr::core::vector2df) -> GameBindings::irr::core::vector2df;
    auto tmpPosSize(GameBindings::irr::core::vector2df, GameBindings::irr::core::dimension2df) -> GameBindings::irr::core::rectf;
    auto getWidth() -> GameBindings::float_expr;
    auto tmpWithXYXY(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::rectf;
    auto newWithXYXY(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::rectf;
    auto getHeight() -> GameBindings::float_expr;
    auto set_LowerRightCorner(GameBindings::irr::core::vector2df) -> GameBindings::irr::core::vector2df;
    auto newPosSize(GameBindings::irr::core::vector2df, GameBindings::irr::core::dimension2df) -> GameBindings::irr::core::rectf;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::rectf;
    auto ref_UpperLeftCorner() -> GameBindings::irr::core::vector2df;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::rectf;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_LowerRightCorner() -> GameBindings::irr::core::vector2df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector2df
{
    ::LM::ExprPtr expr;
    auto ref_Y() -> GameBindings::float_expr;
    auto get_Y() -> GameBindings::float_expr;
    auto set_Y(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_X() -> GameBindings::float_expr;
    auto tmpWithXY(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector2df;
    auto tmp() -> GameBindings::irr::core::vector2df;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector2df;
    auto set_X(GameBindings::float_expr) -> GameBindings::float_expr;
    auto lm_new() -> GameBindings::irr::core::vector2df;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector2df;
    auto newWithXY(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector2df;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_X() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector2di
{
    ::LM::ExprPtr expr;
    auto ref_Y() -> GameBindings::int_expr;
    auto get_Y() -> GameBindings::int_expr;
    auto set_Y(GameBindings::int_expr) -> GameBindings::int_expr;
    auto ref_X() -> GameBindings::int_expr;
    auto tmpWithXY(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::vector2di;
    auto tmp() -> GameBindings::irr::core::vector2di;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::vector2di;
    auto set_X(GameBindings::int_expr) -> GameBindings::int_expr;
    auto lm_new() -> GameBindings::irr::core::vector2di;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::vector2di;
    auto newWithXY(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::vector2di;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_X() -> GameBindings::int_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct dimension2df
{
    ::LM::ExprPtr expr;
    auto get_Height() -> GameBindings::float_expr;
    auto set_Height(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_Width() -> GameBindings::float_expr;
    auto set(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::dimension2df;
    auto ref_Height() -> GameBindings::float_expr;
    auto set_Width(GameBindings::float_expr) -> GameBindings::float_expr;
    auto tmp() -> GameBindings::irr::core::dimension2df;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::dimension2df;
    auto getArea() -> GameBindings::float_expr;
    auto lm_new() -> GameBindings::irr::core::dimension2df;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::dimension2df;
    auto get_Width() -> GameBindings::float_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ArrayOfVector3df
{
    ::LM::ExprPtr expr;
    auto operator ==(GameBindings::irr::core::ArrayOfVector3df) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::core::ArrayOfVector3df) -> GameBindings::bool_expr;
    auto getLast_c() -> GameBindings::irr::core::vector3df;
    auto binary_search(GameBindings::irr::core::vector3df, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::int_expr;
    auto size() -> GameBindings::uint_expr;
    auto set_sorted(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto squareBrackets(GameBindings::uint_expr) -> GameBindings::irr::core::vector3df;
    auto reallocate(GameBindings::uint_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto binary_search_c(GameBindings::irr::core::vector3df) -> GameBindings::int_expr;
    auto push_back(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto pointer() -> GameBindings::irr::core::vector3df;
    auto insert(GameBindings::irr::core::vector3df, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto set_pointer(GameBindings::irr::core::vector3df, GameBindings::uint_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto swap(GameBindings::irr::core::ArrayOfVector3df) -> GameBindings::void_expr;
    auto erase(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto erase(GameBindings::uint_expr, GameBindings::int_expr) -> GameBindings::void_expr;
    auto const_pointer() -> GameBindings::irr::core::vector3df;
    auto empty() -> GameBindings::bool_expr;
    auto clear() -> GameBindings::void_expr;
    auto allocated_size() -> GameBindings::uint_expr;
    auto tmpCopy(GameBindings::irr::core::ArrayOfVector3df) -> GameBindings::irr::core::ArrayOfVector3df;
    auto setAllocStrategy(MissingType /* C++ irr::core::eAllocStrategy (end) */ ) -> GameBindings::void_expr;
    auto newCopy(GameBindings::irr::core::ArrayOfVector3df) -> GameBindings::irr::core::ArrayOfVector3df;
    auto binary_search_nc(GameBindings::irr::core::vector3df) -> GameBindings::int_expr;
    auto sort() -> GameBindings::void_expr;
    auto linear_search(GameBindings::irr::core::vector3df) -> GameBindings::int_expr;
    auto tmpWithSize(GameBindings::uint_expr) -> GameBindings::irr::core::ArrayOfVector3df;
    auto push_front(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto linear_reverse_search(GameBindings::irr::core::vector3df) -> GameBindings::int_expr;
    auto tmp() -> GameBindings::irr::core::ArrayOfVector3df;
    auto set_free_when_destroyed(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto newWithSize(GameBindings::uint_expr) -> GameBindings::irr::core::ArrayOfVector3df;
    auto getLast_nc() -> GameBindings::irr::core::vector3df;
    auto lm_new() -> GameBindings::irr::core::ArrayOfVector3df;
    auto binary_search_multi(GameBindings::irr::core::vector3df, GameBindings::int_expr) -> GameBindings::int_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto set_used(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct dimension2du
{
    ::LM::ExprPtr expr;
    auto get_Height() -> GameBindings::uint_expr;
    auto set_Height(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto ref_Width() -> GameBindings::uint_expr;
    auto set(GameBindings::uint_expr, GameBindings::uint_expr) -> GameBindings::irr::core::dimension2du;
    auto ref_Height() -> GameBindings::uint_expr;
    auto set_Width(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto tmp() -> GameBindings::irr::core::dimension2du;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::dimension2du;
    auto getArea() -> GameBindings::uint_expr;
    auto lm_new() -> GameBindings::irr::core::dimension2du;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::core::dimension2du;
    auto get_Width() -> GameBindings::uint_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector3df
{
    ::LM::ExprPtr expr;
    auto set(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto set(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto operator +=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto operator *(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto operator -(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto operator +(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto operator >(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto operator <(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto operator !=(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto operator >=(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto setLength(GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto rotateXZBy(GameBindings::double_expr, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto normalize() -> GameBindings::irr::core::vector3df;
    auto interpolate(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::double_expr) -> GameBindings::irr::core::vector3df;
    auto getLengthSQ() -> GameBindings::float_expr;
    auto operator /(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto getInterpolated_quadratic(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::double_expr) -> GameBindings::irr::core::vector3df;
    auto rotateYZBy(GameBindings::double_expr, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto getInterpolated(GameBindings::irr::core::vector3df, GameBindings::double_expr) -> GameBindings::irr::core::vector3df;
    auto getHorizontalAngle() -> GameBindings::irr::core::vector3df;
    auto getDistanceFromSQ(GameBindings::irr::core::vector3df) -> GameBindings::float_expr;
    auto getDistanceFrom(GameBindings::irr::core::vector3df) -> GameBindings::float_expr;
    auto getAs4Values(GameBindings::float_expr) -> GameBindings::void_expr;
    auto rotateXYBy(GameBindings::double_expr, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto set_Y(GameBindings::float_expr) -> GameBindings::float_expr;
    auto ref_X() -> GameBindings::float_expr;
    auto ref_Y() -> GameBindings::float_expr;
    auto get_Y() -> GameBindings::float_expr;
    auto crossProduct(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto getLength() -> GameBindings::float_expr;
    auto invert() -> GameBindings::irr::core::vector3df;
    auto dotProduct(GameBindings::irr::core::vector3df) -> GameBindings::float_expr;
    auto tmpFromVector3df(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto get_Z() -> GameBindings::float_expr;
    auto newFromVector3df(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto ref_Z() -> GameBindings::float_expr;
    auto newWithXYZ(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto equals(GameBindings::irr::core::vector3df, GameBindings::float_expr) -> GameBindings::bool_expr;
    auto operator <=(GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto tmp() -> GameBindings::irr::core::vector3df;
    auto tmp(GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto tmp(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto getSphericalCoordinateAngles() -> GameBindings::irr::core::vector3df;
    auto set_Z(GameBindings::float_expr) -> GameBindings::float_expr;
    auto operator -=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto lm_new() -> GameBindings::irr::core::vector3df;
    auto lm_new(GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto lm_new(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto operator /=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto set_X(GameBindings::float_expr) -> GameBindings::float_expr;
    auto rotationToDirection(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto isBetweenPoints(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df) -> GameBindings::bool_expr;
    auto get_X() -> GameBindings::float_expr;
    auto tmpWithXYZ(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::core::vector3df;
    auto operator *=(GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_vector3df
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
