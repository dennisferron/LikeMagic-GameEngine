#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_irr_core.hpp"
#include "ns_irr_scene.hpp"
#include "ns_global.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace core
		{

auto ListOfAnim::getLast_nc() -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLast_nc", args, 0) };
}
auto ListOfAnim::getLast_c() -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLast_c", args, 0) };
}
auto ListOfAnim::begin_nc() -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_nc", args, 0) };
}
auto ListOfAnim::push_back(GameBindings::irr::scene::ISceneNodeAnimator arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_back", args, 1) };
}
auto ListOfAnim::push_front(GameBindings::irr::scene::ISceneNodeAnimator arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_front", args, 1) };
}
auto ListOfAnim::insert_before(GameBindings::irr::core::ListOfAnimIter arg0, GameBindings::irr::scene::ISceneNodeAnimator arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "insert_before", args, 2) };
}
auto ListOfAnim::insert_after(GameBindings::irr::core::ListOfAnimIter arg0, GameBindings::irr::scene::ISceneNodeAnimator arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "insert_after", args, 2) };
}
auto ListOfAnim::getSize() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSize", args, 0) };
}
auto ListOfAnim::end_nc() -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "end_nc", args, 0) };
}
auto ListOfAnim::end_c() -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "end_c", args, 0) };
}
auto ListOfAnim::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto ListOfAnim::begin_c() -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "begin_c", args, 0) };
}
auto ListOfAnim::erase(GameBindings::irr::core::ListOfAnimIter arg0) -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "erase", args, 1) };
}
auto ListOfAnim::swap(GameBindings::irr::core::ListOfAnim arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "swap", args, 1) };
}
auto ListOfAnim::empty() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "empty", args, 0) };
}
auto ListOfAnim::clear() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clear", args, 0) };
}
auto ListOfAnim::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ListOfAnim::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto recti::tmpWithXYXY(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::core::recti
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmpWithXYXY", args, 4) };
}
auto recti::newWithXYXY(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::core::recti
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "newWithXYXY", args, 4) };
}
auto recti::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::core::recti
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto recti::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::core::recti
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto recti::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto recti::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto matrix4::transformVectOfFloats(GameBindings::float_expr arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "transformVectOfFloats", args, 2) };
}
auto matrix4::transformVect(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "transformVect", args, 1) };
}
auto matrix4::transformVect(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "transformVect", args, 2) };
}
auto matrix4::tmp() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto matrix4::tmp(MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */  arg0) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto matrix4::tmp(GameBindings::irr::core::matrix4 arg0, MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */  arg1) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto matrix4::lm_new() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto matrix4::lm_new(MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */  arg0) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto matrix4::lm_new(GameBindings::irr::core::matrix4 arg0, MissingType /* C++ irr::core::CMatrix4<float>::eConstructor (end) */  arg1) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto matrix4::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto matrix4::getRotationDegrees() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRotationDegrees", args, 0) };
}
auto matrix4::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto irrFsStr::tmpFromCStr(GameBindings::char_expr arg0) -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmpFromCStr", args, 1) };
}
auto irrFsStr::newFromCStr(GameBindings::char_expr arg0) -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "newFromCStr", args, 1) };
}
auto irrFsStr::tmp() -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto irrFsStr::tmp(GameBindings::char_expr arg0) -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto irrFsStr::lm_new() -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto irrFsStr::lm_new(GameBindings::char_expr arg0) -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto irrFsStr::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto irrFsStr::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto stringw::tmp() -> GameBindings::irr::core::stringw
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto stringw::tmp(GameBindings::wchar_t_expr arg0) -> GameBindings::irr::core::stringw
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto stringw::lm_new() -> GameBindings::irr::core::stringw
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto stringw::lm_new(GameBindings::wchar_t_expr arg0) -> GameBindings::irr::core::stringw
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto stringw::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto stringw::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto aabbox3df::isPointTotalInside(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isPointTotalInside", args, 1) };
}
auto aabbox3df::isPointInside(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isPointInside", args, 1) };
}
auto aabbox3df::isEmpty() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isEmpty", args, 0) };
}
auto aabbox3df::getVolume() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVolume", args, 0) };
}
auto aabbox3df::getExtent() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getExtent", args, 0) };
}
auto aabbox3df::repair() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "repair", args, 0) };
}
auto aabbox3df::getEdges(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getEdges", args, 1) };
}
auto aabbox3df::getArea() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getArea", args, 0) };
}
auto aabbox3df::getInterpolated(GameBindings::irr::core::aabbox3df arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getInterpolated", args, 2) };
}
auto aabbox3df::addInternalBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addInternalBox", args, 1) };
}
auto aabbox3df::operator ==(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto aabbox3df::ref_MinEdge() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MinEdge", args, 0) };
}
auto aabbox3df::set_MaxEdge(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MaxEdge", args, 1) };
}
auto aabbox3df::tmpWithMinMaxXYZ(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "tmpWithMinMaxXYZ", args, 6) };
}
auto aabbox3df::tmpWithMinMax(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpWithMinMax", args, 2) };
}
auto aabbox3df::tmpWithOnePoint(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmpWithOnePoint", args, 1) };
}
auto aabbox3df::set_MinEdge(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MinEdge", args, 1) };
}
auto aabbox3df::newWithOnePoint(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "newWithOnePoint", args, 1) };
}
auto aabbox3df::classifyPlaneRelation(GameBindings::irr::core::plane3df arg0) -> GameBindings::irr::core::EIntersectionRelation3D
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "classifyPlaneRelation", args, 1) };
}
auto aabbox3df::get_MaxEdge() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MaxEdge", args, 0) };
}
auto aabbox3df::intersectsWithBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "intersectsWithBox", args, 1) };
}
auto aabbox3df::tmp() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto aabbox3df::tmp(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto aabbox3df::tmp(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto aabbox3df::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "tmp", args, 6) };
}
auto aabbox3df::isFullInside(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isFullInside", args, 1) };
}
auto aabbox3df::lm_new() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto aabbox3df::lm_new(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto aabbox3df::lm_new(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto aabbox3df::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "new", args, 6) };
}
auto aabbox3df::newWithMinMaxXYZ(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "newWithMinMaxXYZ", args, 6) };
}
auto aabbox3df::operator !=(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto aabbox3df::ref_MaxEdge() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MaxEdge", args, 0) };
}
auto aabbox3df::getCenter() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCenter", args, 0) };
}
auto aabbox3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto aabbox3df::newWithMinMax(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newWithMinMax", args, 2) };
}
auto aabbox3df::get_MinEdge() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MinEdge", args, 0) };
}
auto aabbox3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto EIntersectionRelation3D::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto EIntersectionRelation3D::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto plane3df::setPlaneFromNormalAndDistance(GameBindings::irr::core::vector3df arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPlaneFromNormalAndDistance", args, 2) };
}
auto plane3df::setPlaneFromPoints(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setPlaneFromPoints", args, 3) };
}
auto plane3df::operator ==(GameBindings::irr::core::plane3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto plane3df::operator !=(GameBindings::irr::core::plane3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto plane3df::isFrontFacing(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isFrontFacing", args, 1) };
}
auto plane3df::getMemberPoint() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMemberPoint", args, 0) };
}
auto plane3df::setPlaneFromPointAndNormal(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setPlaneFromPointAndNormal", args, 2) };
}
auto plane3df::getKnownIntersectionWithLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getKnownIntersectionWithLine", args, 2) };
}
auto plane3df::getIntersectionWithPlane(GameBindings::irr::core::plane3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithPlane", args, 3) };
}
auto plane3df::getIntersectionWithLimitedLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithLimitedLine", args, 3) };
}
auto plane3df::getDistanceTo(GameBindings::irr::core::vector3df arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getDistanceTo", args, 1) };
}
auto plane3df::existsIntersection(GameBindings::irr::core::plane3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "existsIntersection", args, 1) };
}
auto plane3df::ref_Normal() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Normal", args, 0) };
}
auto plane3df::set_Normal(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Normal", args, 1) };
}
auto plane3df::ref_D() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_D", args, 0) };
}
auto plane3df::get_D() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_D", args, 0) };
}
auto plane3df::tmpFromPxPyPzNxNyNz(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "tmpFromPxPyPzNxNyNz", args, 6) };
}
auto plane3df::newFromPointAndNormal(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newFromPointAndNormal", args, 2) };
}
auto plane3df::newFromPxPyPzNxNyNz(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "newFromPxPyPzNxNyNz", args, 6) };
}
auto plane3df::recalculateD(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "recalculateD", args, 1) };
}
auto plane3df::set_D(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_D", args, 1) };
}
auto plane3df::newFromPoints(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "newFromPoints", args, 3) };
}
auto plane3df::newFromNormalAndDistance(GameBindings::irr::core::vector3df arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newFromNormalAndDistance", args, 2) };
}
auto plane3df::getIntersectionWithLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithLine", args, 3) };
}
auto plane3df::tmpFromNormalAndDistance(GameBindings::irr::core::vector3df arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpFromNormalAndDistance", args, 2) };
}
auto plane3df::tmpFromPoints(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmpFromPoints", args, 3) };
}
auto plane3df::get_Normal() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Normal", args, 0) };
}
auto plane3df::classifyPointRelation(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::EIntersectionRelation3D
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "classifyPointRelation", args, 1) };
}
auto plane3df::tmp() -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto plane3df::tmpFromPointAndNormal(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpFromPointAndNormal", args, 2) };
}
auto plane3df::getIntersectionWithPlanes(GameBindings::irr::core::plane3df arg0, GameBindings::irr::core::plane3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithPlanes", args, 3) };
}
auto plane3df::lm_new() -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto plane3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto plane3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ListOfAnimConstIter::operator +(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+", args, 1) };
}
auto ListOfAnimConstIter::operator_increment(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "++", args, 1) };
}
auto ListOfAnimConstIter::operator -(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-", args, 1) };
}
auto ListOfAnimConstIter::operator_decrement(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimConstIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "--", args, 1) };
}
auto ListOfAnimConstIter::operator *() -> GameBindings::irr::scene::ISceneNodeAnimator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "*", args, 0) };
}
auto ListOfAnimConstIter::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ListOfAnimConstIter::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ListOfAnimIter::operator +(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+", args, 1) };
}
auto ListOfAnimIter::operator_increment(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "++", args, 1) };
}
auto ListOfAnimIter::operator -(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-", args, 1) };
}
auto ListOfAnimIter::operator_decrement(GameBindings::int_expr arg0) -> GameBindings::irr::core::ListOfAnimIter
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "--", args, 1) };
}
auto ListOfAnimIter::operator *() -> GameBindings::irr::scene::ISceneNodeAnimator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "*", args, 0) };
}
auto ListOfAnimIter::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ListOfAnimIter::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto triangle3df::operator ==(GameBindings::irr::core::triangle3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto triangle3df::set(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "set", args, 3) };
}
auto triangle3df::isTotalOutsideBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isTotalOutsideBox", args, 1) };
}
auto triangle3df::isPointInsideFast(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isPointInsideFast", args, 1) };
}
auto triangle3df::isPointInside(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isPointInside", args, 1) };
}
auto triangle3df::getIntersectionWithLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithLine", args, 3) };
}
auto triangle3df::getIntersectionOfPlaneWithLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionOfPlaneWithLine", args, 3) };
}
auto triangle3df::closestPointOnTriangle(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "closestPointOnTriangle", args, 1) };
}
auto triangle3df::isTotalInsideBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isTotalInsideBox", args, 1) };
}
auto triangle3df::ref_pointC() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_pointC", args, 0) };
}
auto triangle3df::get_pointC() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_pointC", args, 0) };
}
auto triangle3df::ref_pointB() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_pointB", args, 0) };
}
auto triangle3df::getPlane() -> GameBindings::irr::core::plane3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPlane", args, 0) };
}
auto triangle3df::get_pointB() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_pointB", args, 0) };
}
auto triangle3df::set_pointB(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_pointB", args, 1) };
}
auto triangle3df::getIntersectionWithLimitedLine(GameBindings::irr::core::line3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getIntersectionWithLimitedLine", args, 2) };
}
auto triangle3df::ref_pointA() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_pointA", args, 0) };
}
auto triangle3df::get_pointA() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_pointA", args, 0) };
}
auto triangle3df::tmp() -> GameBindings::irr::core::triangle3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto triangle3df::tmp(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::irr::core::triangle3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto triangle3df::getNormal() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNormal", args, 0) };
}
auto triangle3df::getArea() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getArea", args, 0) };
}
auto triangle3df::lm_new() -> GameBindings::irr::core::triangle3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto triangle3df::lm_new(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2) -> GameBindings::irr::core::triangle3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto triangle3df::operator !=(GameBindings::irr::core::triangle3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto triangle3df::set_pointC(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_pointC", args, 1) };
}
auto triangle3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto triangle3df::isFrontFacing(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isFrontFacing", args, 1) };
}
auto triangle3df::set_pointA(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_pointA", args, 1) };
}
auto triangle3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto line3df::operator +=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::line3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+=", args, 1) };
}
auto line3df::operator +(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::line3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+", args, 1) };
}
auto line3df::getMiddle() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMiddle", args, 0) };
}
auto line3df::getLengthSQ() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLengthSQ", args, 0) };
}
auto line3df::getVector() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVector", args, 0) };
}
auto line3df::getLength() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLength", args, 0) };
}
auto line3df::operator -=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::line3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-=", args, 1) };
}
auto line3df::getIntersectionWithSphere(GameBindings::irr::core::vector3df arg0, GameBindings::float_expr arg1, GameBindings::double_expr arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getIntersectionWithSphere", args, 3) };
}
auto line3df::ref_end() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_end", args, 0) };
}
auto line3df::operator ==(GameBindings::irr::core::line3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto line3df::getClosestPoint(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getClosestPoint", args, 1) };
}
auto line3df::set_end(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_end", args, 1) };
}
auto line3df::get_end() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_end", args, 0) };
}
auto line3df::operator -(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::line3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-", args, 1) };
}
auto line3df::ref_start() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_start", args, 0) };
}
auto line3df::get_start() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_start", args, 0) };
}
auto line3df::operator !=(GameBindings::irr::core::line3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto line3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto line3df::isPointBetweenStartAndEnd(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "isPointBetweenStartAndEnd", args, 1) };
}
auto line3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto line3df::set_start(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_start", args, 1) };
}

auto rectf::ref_LowerRightCorner() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_LowerRightCorner", args, 0) };
}
auto rectf::get_UpperLeftCorner() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_UpperLeftCorner", args, 0) };
}
auto rectf::set_UpperLeftCorner(GameBindings::irr::core::vector2df arg0) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_UpperLeftCorner", args, 1) };
}
auto rectf::tmpPosSize(GameBindings::irr::core::vector2df arg0, GameBindings::irr::core::dimension2df arg1) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpPosSize", args, 2) };
}
auto rectf::getWidth() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getWidth", args, 0) };
}
auto rectf::tmpWithXYXY(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmpWithXYXY", args, 4) };
}
auto rectf::newWithXYXY(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "newWithXYXY", args, 4) };
}
auto rectf::getHeight() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHeight", args, 0) };
}
auto rectf::set_LowerRightCorner(GameBindings::irr::core::vector2df arg0) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_LowerRightCorner", args, 1) };
}
auto rectf::newPosSize(GameBindings::irr::core::vector2df arg0, GameBindings::irr::core::dimension2df arg1) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newPosSize", args, 2) };
}
auto rectf::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto rectf::ref_UpperLeftCorner() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_UpperLeftCorner", args, 0) };
}
auto rectf::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::core::rectf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto rectf::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto rectf::get_LowerRightCorner() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_LowerRightCorner", args, 0) };
}
auto rectf::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector2df::ref_Y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Y", args, 0) };
}
auto vector2df::get_Y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Y", args, 0) };
}
auto vector2df::set_Y(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Y", args, 1) };
}
auto vector2df::ref_X() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_X", args, 0) };
}
auto vector2df::tmpWithXY(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpWithXY", args, 2) };
}
auto vector2df::tmp() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto vector2df::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto vector2df::set_X(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_X", args, 1) };
}
auto vector2df::lm_new() -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto vector2df::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto vector2df::newWithXY(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newWithXY", args, 2) };
}
auto vector2df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector2df::get_X() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_X", args, 0) };
}
auto vector2df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector2di::ref_Y() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Y", args, 0) };
}
auto vector2di::get_Y() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Y", args, 0) };
}
auto vector2di::set_Y(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Y", args, 1) };
}
auto vector2di::ref_X() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_X", args, 0) };
}
auto vector2di::tmpWithXY(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmpWithXY", args, 2) };
}
auto vector2di::tmp() -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto vector2di::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto vector2di::set_X(GameBindings::int_expr arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_X", args, 1) };
}
auto vector2di::lm_new() -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto vector2di::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto vector2di::newWithXY(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::vector2di
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "newWithXY", args, 2) };
}
auto vector2di::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector2di::get_X() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_X", args, 0) };
}
auto vector2di::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto dimension2df::get_Height() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Height", args, 0) };
}
auto dimension2df::set_Height(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Height", args, 1) };
}
auto dimension2df::ref_Width() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Width", args, 0) };
}
auto dimension2df::set(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::dimension2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "set", args, 2) };
}
auto dimension2df::ref_Height() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Height", args, 0) };
}
auto dimension2df::set_Width(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Width", args, 1) };
}
auto dimension2df::tmp() -> GameBindings::irr::core::dimension2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto dimension2df::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::dimension2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto dimension2df::getArea() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getArea", args, 0) };
}
auto dimension2df::lm_new() -> GameBindings::irr::core::dimension2df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto dimension2df::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::irr::core::dimension2df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto dimension2df::get_Width() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Width", args, 0) };
}
auto dimension2df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto dimension2df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ArrayOfVector3df::operator ==(GameBindings::irr::core::ArrayOfVector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto ArrayOfVector3df::operator !=(GameBindings::irr::core::ArrayOfVector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto ArrayOfVector3df::getLast_c() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLast_c", args, 0) };
}
auto ArrayOfVector3df::binary_search(GameBindings::irr::core::vector3df arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "binary_search", args, 3) };
}
auto ArrayOfVector3df::size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "size", args, 0) };
}
auto ArrayOfVector3df::set_sorted(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_sorted", args, 1) };
}
auto ArrayOfVector3df::squareBrackets(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "squareBrackets", args, 1) };
}
auto ArrayOfVector3df::reallocate(GameBindings::uint_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "reallocate", args, 2) };
}
auto ArrayOfVector3df::binary_search_c(GameBindings::irr::core::vector3df arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "binary_search_c", args, 1) };
}
auto ArrayOfVector3df::push_back(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_back", args, 1) };
}
auto ArrayOfVector3df::pointer() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "pointer", args, 0) };
}
auto ArrayOfVector3df::insert(GameBindings::irr::core::vector3df arg0, GameBindings::uint_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "insert", args, 2) };
}
auto ArrayOfVector3df::set_pointer(GameBindings::irr::core::vector3df arg0, GameBindings::uint_expr arg1, GameBindings::bool_expr arg2, GameBindings::bool_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "set_pointer", args, 4) };
}
auto ArrayOfVector3df::swap(GameBindings::irr::core::ArrayOfVector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "swap", args, 1) };
}
auto ArrayOfVector3df::erase(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "erase", args, 1) };
}
auto ArrayOfVector3df::erase(GameBindings::uint_expr arg0, GameBindings::int_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "erase", args, 2) };
}
auto ArrayOfVector3df::const_pointer() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "const_pointer", args, 0) };
}
auto ArrayOfVector3df::empty() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "empty", args, 0) };
}
auto ArrayOfVector3df::clear() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clear", args, 0) };
}
auto ArrayOfVector3df::allocated_size() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "allocated_size", args, 0) };
}
auto ArrayOfVector3df::tmpCopy(GameBindings::irr::core::ArrayOfVector3df arg0) -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmpCopy", args, 1) };
}
auto ArrayOfVector3df::setAllocStrategy(MissingType /* C++ irr::core::eAllocStrategy (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAllocStrategy", args, 1) };
}
auto ArrayOfVector3df::newCopy(GameBindings::irr::core::ArrayOfVector3df arg0) -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "newCopy", args, 1) };
}
auto ArrayOfVector3df::binary_search_nc(GameBindings::irr::core::vector3df arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "binary_search_nc", args, 1) };
}
auto ArrayOfVector3df::sort() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "sort", args, 0) };
}
auto ArrayOfVector3df::linear_search(GameBindings::irr::core::vector3df arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "linear_search", args, 1) };
}
auto ArrayOfVector3df::tmpWithSize(GameBindings::uint_expr arg0) -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmpWithSize", args, 1) };
}
auto ArrayOfVector3df::push_front(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "push_front", args, 1) };
}
auto ArrayOfVector3df::linear_reverse_search(GameBindings::irr::core::vector3df arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "linear_reverse_search", args, 1) };
}
auto ArrayOfVector3df::tmp() -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto ArrayOfVector3df::set_free_when_destroyed(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_free_when_destroyed", args, 1) };
}
auto ArrayOfVector3df::newWithSize(GameBindings::uint_expr arg0) -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "newWithSize", args, 1) };
}
auto ArrayOfVector3df::getLast_nc() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLast_nc", args, 0) };
}
auto ArrayOfVector3df::lm_new() -> GameBindings::irr::core::ArrayOfVector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto ArrayOfVector3df::binary_search_multi(GameBindings::irr::core::vector3df arg0, GameBindings::int_expr arg1) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "binary_search_multi", args, 2) };
}
auto ArrayOfVector3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ArrayOfVector3df::set_used(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_used", args, 1) };
}
auto ArrayOfVector3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto dimension2du::get_Height() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Height", args, 0) };
}
auto dimension2du::set_Height(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Height", args, 1) };
}
auto dimension2du::ref_Width() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Width", args, 0) };
}
auto dimension2du::set(GameBindings::uint_expr arg0, GameBindings::uint_expr arg1) -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "set", args, 2) };
}
auto dimension2du::ref_Height() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Height", args, 0) };
}
auto dimension2du::set_Width(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Width", args, 1) };
}
auto dimension2du::tmp() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto dimension2du::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto dimension2du::getArea() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getArea", args, 0) };
}
auto dimension2du::lm_new() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto dimension2du::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto dimension2du::get_Width() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Width", args, 0) };
}
auto dimension2du::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto dimension2du::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector3df::set(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set", args, 1) };
}
auto vector3df::set(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "set", args, 3) };
}
auto vector3df::operator +=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+=", args, 1) };
}
auto vector3df::operator *(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "*", args, 1) };
}
auto vector3df::operator -(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-", args, 1) };
}
auto vector3df::operator +(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "+", args, 1) };
}
auto vector3df::operator >(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, ">", args, 1) };
}
auto vector3df::operator <(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "<", args, 1) };
}
auto vector3df::operator !=(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto vector3df::operator ==(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto vector3df::operator >=(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, ">=", args, 1) };
}
auto vector3df::setLength(GameBindings::float_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setLength", args, 1) };
}
auto vector3df::rotateXZBy(GameBindings::double_expr arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotateXZBy", args, 2) };
}
auto vector3df::normalize() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "normalize", args, 0) };
}
auto vector3df::interpolate(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::double_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "interpolate", args, 3) };
}
auto vector3df::getLengthSQ() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLengthSQ", args, 0) };
}
auto vector3df::operator /(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "/", args, 1) };
}
auto vector3df::getInterpolated_quadratic(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::double_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getInterpolated_quadratic", args, 3) };
}
auto vector3df::rotateYZBy(GameBindings::double_expr arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotateYZBy", args, 2) };
}
auto vector3df::getInterpolated(GameBindings::irr::core::vector3df arg0, GameBindings::double_expr arg1) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getInterpolated", args, 2) };
}
auto vector3df::getHorizontalAngle() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHorizontalAngle", args, 0) };
}
auto vector3df::getDistanceFromSQ(GameBindings::irr::core::vector3df arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getDistanceFromSQ", args, 1) };
}
auto vector3df::getDistanceFrom(GameBindings::irr::core::vector3df arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getDistanceFrom", args, 1) };
}
auto vector3df::getAs4Values(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getAs4Values", args, 1) };
}
auto vector3df::rotateXYBy(GameBindings::double_expr arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "rotateXYBy", args, 2) };
}
auto vector3df::set_Y(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Y", args, 1) };
}
auto vector3df::ref_X() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_X", args, 0) };
}
auto vector3df::ref_Y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Y", args, 0) };
}
auto vector3df::get_Y() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Y", args, 0) };
}
auto vector3df::crossProduct(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "crossProduct", args, 1) };
}
auto vector3df::getLength() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getLength", args, 0) };
}
auto vector3df::invert() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "invert", args, 0) };
}
auto vector3df::dotProduct(GameBindings::irr::core::vector3df arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "dotProduct", args, 1) };
}
auto vector3df::tmpFromVector3df(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmpFromVector3df", args, 1) };
}
auto vector3df::get_Z() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Z", args, 0) };
}
auto vector3df::newFromVector3df(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "newFromVector3df", args, 1) };
}
auto vector3df::ref_Z() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Z", args, 0) };
}
auto vector3df::newWithXYZ(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "newWithXYZ", args, 3) };
}
auto vector3df::equals(GameBindings::irr::core::vector3df arg0, GameBindings::float_expr arg1) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "equals", args, 2) };
}
auto vector3df::operator <=(GameBindings::irr::core::vector3df arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "<=", args, 1) };
}
auto vector3df::tmp() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto vector3df::tmp(GameBindings::float_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto vector3df::tmp(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto vector3df::getSphericalCoordinateAngles() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSphericalCoordinateAngles", args, 0) };
}
auto vector3df::set_Z(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Z", args, 1) };
}
auto vector3df::operator -=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "-=", args, 1) };
}
auto vector3df::lm_new() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto vector3df::lm_new(GameBindings::float_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto vector3df::lm_new(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto vector3df::operator /=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "/=", args, 1) };
}
auto vector3df::set_X(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_X", args, 1) };
}
auto vector3df::rotationToDirection(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "rotationToDirection", args, 1) };
}
auto vector3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector3df::isBetweenPoints(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "isBetweenPoints", args, 2) };
}
auto vector3df::get_X() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_X", args, 0) };
}
auto vector3df::tmpWithXYZ(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmpWithXYZ", args, 3) };
}
auto vector3df::operator *=(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "*=", args, 1) };
}
auto vector3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_vector3df::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_vector3df::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
