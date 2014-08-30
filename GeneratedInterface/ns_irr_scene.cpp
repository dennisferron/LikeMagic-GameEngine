#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_irr_io.hpp"
#include "ns_global.hpp"
#include "ns_irr_core.hpp"
#include "ns_irr.hpp"
#include "ns_irr_scene.hpp"
#include "ns_irr_gui.hpp"
#include "ns_irr_video.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace scene
		{

auto SMesh::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SMesh::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IAnimatedMeshSceneNode::setAnimationSpeed(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAnimationSpeed", args, 1) };
}
auto IAnimatedMeshSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IAnimatedMeshSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ITriangleSelector::getTrianglesForBox(GameBindings::irr::core::triangle3df arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::irr::core::aabbox3df arg3, GameBindings::irr::core::matrix4 arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "getTrianglesForBox", args, 5) };
}
auto ITriangleSelector::getTrianglesForNode(GameBindings::irr::core::triangle3df arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::irr::core::matrix4 arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "getTrianglesForNode", args, 4) };
}
auto ITriangleSelector::getTriangleCount() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTriangleCount", args, 0) };
}
auto ITriangleSelector::getSceneNodeForTriangle(GameBindings::uint_expr arg0) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getSceneNodeForTriangle", args, 1) };
}
auto ITriangleSelector::getTrianglesForLine(GameBindings::irr::core::triangle3df arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::irr::core::line3df arg3, GameBindings::irr::core::matrix4 arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "getTrianglesForLine", args, 5) };
}
auto ITriangleSelector::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ITriangleSelector::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMeshManipulator::makePlanarTextureMapping(GameBindings::irr::scene::IMeshBuffer arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::uchar_expr arg3, GameBindings::irr::core::vector3df arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "makePlanarTextureMapping", args, 5) };
}
auto IMeshManipulator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMeshManipulator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ICameraSceneNode::setTarget(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setTarget", args, 1) };
}
auto ICameraSceneNode::setProjectionMatrix(GameBindings::irr::core::matrix4 arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setProjectionMatrix", args, 2) };
}
auto ICameraSceneNode::setViewMatrixAffector(GameBindings::irr::core::matrix4 arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setViewMatrixAffector", args, 1) };
}
auto ICameraSceneNode::setFOV(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFOV", args, 1) };
}
auto ICameraSceneNode::setFarValue(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setFarValue", args, 1) };
}
auto ICameraSceneNode::isOrthogonal() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isOrthogonal", args, 0) };
}
auto ICameraSceneNode::getViewFrustum() -> MissingType /* C++ irr::scene::SViewFrustum const* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getViewFrustum", args, 0) };
}
auto ICameraSceneNode::getViewMatrixAffector() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getViewMatrixAffector", args, 0) };
}
auto ICameraSceneNode::OnEvent(GameBindings::irr::gui::SEvent arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "OnEvent", args, 1) };
}
auto ICameraSceneNode::setUpVector(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setUpVector", args, 1) };
}
auto ICameraSceneNode::setNearValue(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setNearValue", args, 1) };
}
auto ICameraSceneNode::getUpVector() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getUpVector", args, 0) };
}
auto ICameraSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ICameraSceneNode::getTargetAndRotationBinding() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTargetAndRotationBinding", args, 0) };
}
auto ICameraSceneNode::getFarValue() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFarValue", args, 0) };
}
auto ICameraSceneNode::getNearValue() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getNearValue", args, 0) };
}
auto ICameraSceneNode::isInputReceiverEnabled() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isInputReceiverEnabled", args, 0) };
}
auto ICameraSceneNode::getProjectionMatrix() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getProjectionMatrix", args, 0) };
}
auto ICameraSceneNode::getAspectRatio() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAspectRatio", args, 0) };
}
auto ICameraSceneNode::bindTargetAndRotation(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "bindTargetAndRotation", args, 1) };
}
auto ICameraSceneNode::getViewMatrix() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getViewMatrix", args, 0) };
}
auto ICameraSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto ICameraSceneNode::getTarget() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTarget", args, 0) };
}
auto ICameraSceneNode::setInputReceiverEnabled(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setInputReceiverEnabled", args, 1) };
}
auto ICameraSceneNode::setAspectRatio(GameBindings::float_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAspectRatio", args, 1) };
}
auto ICameraSceneNode::getFOV() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFOV", args, 0) };
}

auto ITerrainSceneNode::scaleTexture(GameBindings::float_expr arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "scaleTexture", args, 2) };
}
auto ITerrainSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ITerrainSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ILightSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ILightSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMeshSceneNode::setReadOnlyMaterials(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setReadOnlyMaterials", args, 1) };
}
auto IMeshSceneNode::setMesh(GameBindings::irr::scene::IMesh arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMesh", args, 1) };
}
auto IMeshSceneNode::isReadOnlyMaterials() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isReadOnlyMaterials", args, 0) };
}
auto IMeshSceneNode::getMesh() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMesh", args, 0) };
}
auto IMeshSceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMeshSceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ISceneNode::getID() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getID", args, 0) };
}
auto ISceneNode::getRotation() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRotation", args, 0) };
}
auto ISceneNode::setTriangleSelector(GameBindings::irr::scene::ITriangleSelector arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setTriangleSelector", args, 1) };
}
auto ISceneNode::setVisible(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setVisible", args, 1) };
}
auto ISceneNode::OnAnimate(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "OnAnimate", args, 1) };
}
auto ISceneNode::setMaterialType(GameBindings::irr::video::E_MATERIAL_TYPE arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaterialType", args, 1) };
}
auto ISceneNode::setID(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setID", args, 1) };
}
auto ISceneNode::removeAnimators() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "removeAnimators", args, 0) };
}
auto ISceneNode::setScale(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setScale", args, 1) };
}
auto ISceneNode::isDebugDataVisible() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isDebugDataVisible", args, 0) };
}
auto ISceneNode::getName() -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getName", args, 0) };
}
auto ISceneNode::OnRegisterSceneNode() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "OnRegisterSceneNode", args, 0) };
}
auto ISceneNode::getAnimators() -> GameBindings::irr::core::ListOfAnim
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAnimators", args, 0) };
}
auto ISceneNode::getPosition() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getPosition", args, 0) };
}
auto ISceneNode::addAnimator(GameBindings::irr::scene::ISceneNodeAnimator arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addAnimator", args, 1) };
}
auto ISceneNode::remove() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "remove", args, 0) };
}
auto ISceneNode::getAbsoluteTransformation() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAbsoluteTransformation", args, 0) };
}
auto ISceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto ISceneNode::setParent(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setParent", args, 1) };
}
auto ISceneNode::getMaterialCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaterialCount", args, 0) };
}
auto ISceneNode::setPosition(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setPosition", args, 1) };
}
auto ISceneNode::getAbsolutePosition() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getAbsolutePosition", args, 0) };
}
auto ISceneNode::addChild(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addChild", args, 1) };
}
auto ISceneNode::getRelativeTransformation() -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRelativeTransformation", args, 0) };
}
auto ISceneNode::setRotation(GameBindings::irr::core::vector3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setRotation", args, 1) };
}
auto ISceneNode::setMaterialTexture(GameBindings::uint_expr arg0, GameBindings::irr::video::ITexture arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMaterialTexture", args, 2) };
}
auto ISceneNode::getMaterial(GameBindings::uint_expr arg0) -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMaterial", args, 1) };
}
auto ISceneNode::setDebugDataVisible(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDebugDataVisible", args, 1) };
}
auto ISceneNode::updateAbsolutePosition() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "updateAbsolutePosition", args, 0) };
}
auto ISceneNode::getBoundingBox() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBoundingBox", args, 0) };
}
auto ISceneNode::removeAnimator(GameBindings::irr::scene::ISceneNodeAnimator arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeAnimator", args, 1) };
}
auto ISceneNode::render() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "render", args, 0) };
}
auto ISceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISceneNode::getScale() -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getScale", args, 0) };
}
auto ISceneNode::setMaterialFlag(GameBindings::irr::video::E_MATERIAL_FLAG arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMaterialFlag", args, 2) };
}

auto IGeometryCreator::createVolumeLightMesh(GameBindings::uint_expr arg0, GameBindings::uint_expr arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::video::SColor arg3, GameBindings::float_expr arg4, GameBindings::irr::core::vector3df arg5) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "createVolumeLightMesh", args, 6) };
}
auto IGeometryCreator::createTerrainMesh(GameBindings::irr::video::IImage arg0, GameBindings::irr::video::IImage arg1, GameBindings::irr::core::dimension2df arg2, GameBindings::float_expr arg3, GameBindings::irr::video::IVideoDriver arg4, GameBindings::irr::core::dimension2du arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "createTerrainMesh", args, 7) };
}
auto IGeometryCreator::createSphereMesh(GameBindings::float_expr arg0, GameBindings::uint_expr arg1, GameBindings::uint_expr arg2) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "createSphereMesh", args, 3) };
}
auto IGeometryCreator::createHillPlaneMesh(GameBindings::irr::core::dimension2df arg0, GameBindings::irr::core::dimension2du arg1, GameBindings::irr::video::SMaterial arg2, GameBindings::float_expr arg3, GameBindings::irr::core::dimension2df arg4, GameBindings::irr::core::dimension2df arg5) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "createHillPlaneMesh", args, 6) };
}
auto IGeometryCreator::createCylinderMesh(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::uint_expr arg2, GameBindings::irr::video::SColor arg3, GameBindings::bool_expr arg4, GameBindings::float_expr arg5) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "createCylinderMesh", args, 6) };
}
auto IGeometryCreator::createCubeMesh(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createCubeMesh", args, 1) };
}
auto IGeometryCreator::createConeMesh(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::uint_expr arg2, GameBindings::irr::video::SColor arg3, GameBindings::irr::video::SColor arg4, GameBindings::float_expr arg5) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "createConeMesh", args, 6) };
}
auto IGeometryCreator::createArrowMesh(GameBindings::uint_expr arg0, GameBindings::uint_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::irr::video::SColor arg6, GameBindings::irr::video::SColor arg7) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr }; 
    return { ::LM::call(expr, "createArrowMesh", args, 8) };
}
auto IGeometryCreator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IGeometryCreator::createPlaneMesh(GameBindings::irr::core::dimension2df arg0, GameBindings::irr::core::dimension2du arg1, GameBindings::irr::video::SMaterial arg2, GameBindings::irr::core::dimension2df arg3) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "createPlaneMesh", args, 4) };
}
auto IGeometryCreator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IAnimatedMesh::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IAnimatedMesh::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMeshBuffer::getTCoords_nc(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTCoords_nc", args, 1) };
}
auto IMeshBuffer::getPosition_nc(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getPosition_nc", args, 1) };
}
auto IMeshBuffer::getNormal_nc(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getNormal_nc", args, 1) };
}
auto IMeshBuffer::getNormal_c(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getNormal_c", args, 1) };
}
auto IMeshBuffer::getMaterial_nc() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaterial_nc", args, 0) };
}
auto IMeshBuffer::getMaterial_c() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaterial_c", args, 0) };
}
auto IMeshBuffer::setBoundingBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setBoundingBox", args, 1) };
}
auto IMeshBuffer::getVertexCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVertexCount", args, 0) };
}
auto IMeshBuffer::append(GameBindings::irr::scene::IMeshBuffer arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "append", args, 1) };
}
auto IMeshBuffer::append(GameBindings::void_expr arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "append", args, 4) };
}
auto IMeshBuffer::getVertices_c() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVertices_c", args, 0) };
}
auto IMeshBuffer::recalculateBoundingBox() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "recalculateBoundingBox", args, 0) };
}
auto IMeshBuffer::getVertexType() -> GameBindings::irr::video::E_VERTEX_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVertexType", args, 0) };
}
auto IMeshBuffer::getIndices_nc() -> GameBindings::ushort_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndices_nc", args, 0) };
}
auto IMeshBuffer::getIndexType() -> MissingType /* C++ irr::video::E_INDEX_TYPE */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndexType", args, 0) };
}
auto IMeshBuffer::getIndexCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndexCount", args, 0) };
}
auto IMeshBuffer::getHardwareMappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHardwareMappingHint_Vertex", args, 0) };
}
auto IMeshBuffer::getHardwareMappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getHardwareMappingHint_Index", args, 0) };
}
auto IMeshBuffer::getTCoords_c(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector2df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTCoords_c", args, 1) };
}
auto IMeshBuffer::getPosition_c(GameBindings::uint_expr arg0) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getPosition_c", args, 1) };
}
auto IMeshBuffer::setHardwareMappingHint(GameBindings::irr::scene::E_HARDWARE_MAPPING arg0, GameBindings::irr::scene::E_BUFFER_TYPE arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setHardwareMappingHint", args, 2) };
}
auto IMeshBuffer::getBoundingBox() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBoundingBox", args, 0) };
}
auto IMeshBuffer::getIndices_c() -> GameBindings::ushort_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getIndices_c", args, 0) };
}
auto IMeshBuffer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMeshBuffer::getVertices_nc() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVertices_nc", args, 0) };
}
auto IMeshBuffer::setDirty(GameBindings::irr::scene::E_BUFFER_TYPE arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDirty", args, 1) };
}
auto IMeshBuffer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ISceneManager::addTerrainSceneNodeFromPath(GameBindings::irr::core::irrFsStr arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::int_expr arg2, GameBindings::irr::core::vector3df arg3, GameBindings::irr::core::vector3df arg4, GameBindings::irr::core::vector3df arg5, GameBindings::irr::video::SColor arg6, GameBindings::int_expr arg7, GameBindings::irr::scene::E_TERRAIN_PATCH_SIZE arg8, GameBindings::int_expr arg9, GameBindings::bool_expr arg10) -> GameBindings::irr::scene::ITerrainSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr, arg10.expr }; 
    return { ::LM::call(expr, "addTerrainSceneNodeFromPath", args, 11) };
}
auto ISceneManager::addTerrainSceneNodeFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */  arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::int_expr arg2, GameBindings::irr::core::vector3df arg3, GameBindings::irr::core::vector3df arg4, GameBindings::irr::core::vector3df arg5, GameBindings::irr::video::SColor arg6, GameBindings::int_expr arg7, GameBindings::irr::scene::E_TERRAIN_PATCH_SIZE arg8, GameBindings::int_expr arg9, GameBindings::bool_expr arg10) -> GameBindings::irr::scene::ITerrainSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr, arg10.expr }; 
    return { ::LM::call(expr, "addTerrainSceneNodeFromIReadFile", args, 11) };
}
auto ISceneManager::loadSceneFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */  arg0, GameBindings::irr::io::ISceneUserDataSerializer arg1, GameBindings::irr::scene::ISceneNode arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "loadSceneFromIReadFile", args, 3) };
}
auto ISceneManager::loadSceneFromPath(GameBindings::irr::core::irrFsStr arg0, GameBindings::irr::io::ISceneUserDataSerializer arg1, GameBindings::irr::scene::ISceneNode arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "loadSceneFromPath", args, 3) };
}
auto ISceneManager::createOctreeTriangleSelector(GameBindings::irr::scene::IMesh arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::int_expr arg2) -> GameBindings::irr::scene::ITriangleSelector
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "createOctreeTriangleSelector", args, 3) };
}
auto ISceneManager::getMeshFromPath(GameBindings::irr::core::irrFsStr arg0) -> GameBindings::irr::scene::IAnimatedMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMeshFromPath", args, 1) };
}
auto ISceneManager::getMeshFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */  arg0) -> GameBindings::irr::scene::IAnimatedMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMeshFromIReadFile", args, 1) };
}
auto ISceneManager::createTriangleSelector(GameBindings::irr::scene::IAnimatedMeshSceneNode arg0) -> GameBindings::irr::scene::ITriangleSelector
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createTriangleSelector", args, 1) };
}
auto ISceneManager::createTriangleSelector(GameBindings::irr::scene::IMesh arg0, GameBindings::irr::scene::ISceneNode arg1) -> GameBindings::irr::scene::ITriangleSelector
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createTriangleSelector", args, 2) };
}
auto ISceneManager::addSkyDomeSceneNode(GameBindings::irr::video::ITexture arg0, GameBindings::uint_expr arg1, GameBindings::uint_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::irr::scene::ISceneNode arg6, GameBindings::int_expr arg7) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr }; 
    return { ::LM::call(expr, "addSkyDomeSceneNode", args, 8) };
}
auto ISceneManager::saveSceneToPath(GameBindings::irr::core::irrFsStr arg0, GameBindings::irr::io::ISceneUserDataSerializer arg1, GameBindings::irr::scene::ISceneNode arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "saveSceneToPath", args, 3) };
}
auto ISceneManager::setAmbientLight(GameBindings::irr::video::SColorf arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAmbientLight", args, 1) };
}
auto ISceneManager::saveSceneToIReadFile(MissingType /* C++ irr::io::IWriteFile* (end) */  arg0, GameBindings::irr::io::ISceneUserDataSerializer arg1, GameBindings::irr::scene::ISceneNode arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "saveSceneToIReadFile", args, 3) };
}
auto ISceneManager::getGeometryCreator() -> GameBindings::irr::scene::IGeometryCreator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getGeometryCreator", args, 0) };
}
auto ISceneManager::getSceneCollisionManager() -> GameBindings::irr::scene::ISceneCollisionManager
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getSceneCollisionManager", args, 0) };
}
auto ISceneManager::addCameraSceneNodeFPS(GameBindings::irr::scene::ISceneNode arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::int_expr arg3, GameBindings::irr::SKeyMap arg4, GameBindings::int_expr arg5, GameBindings::bool_expr arg6, GameBindings::float_expr arg7, GameBindings::bool_expr arg8, GameBindings::bool_expr arg9) -> GameBindings::irr::scene::ICameraSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr }; 
    return { ::LM::call(expr, "addCameraSceneNodeFPS", args, 10) };
}
auto ISceneManager::addCameraSceneNodeMaya(GameBindings::irr::scene::ISceneNode arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::int_expr arg4, GameBindings::float_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::scene::ICameraSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addCameraSceneNodeMaya", args, 7) };
}
auto ISceneManager::drawAll() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "drawAll", args, 0) };
}
auto ISceneManager::createRotationAnimator(GameBindings::irr::core::vector3df arg0) -> GameBindings::irr::scene::ISceneNodeAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createRotationAnimator", args, 1) };
}
auto ISceneManager::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto ISceneManager::addMeshSceneNode(GameBindings::irr::scene::IMesh arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::int_expr arg2, GameBindings::irr::core::vector3df arg3, GameBindings::irr::core::vector3df arg4, GameBindings::irr::core::vector3df arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::scene::IMeshSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addMeshSceneNode", args, 7) };
}
auto ISceneManager::addAnimatedMeshSceneNode(GameBindings::irr::scene::IAnimatedMesh arg0, GameBindings::irr::scene::ISceneNode arg1, GameBindings::int_expr arg2, GameBindings::irr::core::vector3df arg3, GameBindings::irr::core::vector3df arg4, GameBindings::irr::core::vector3df arg5, GameBindings::bool_expr arg6) -> GameBindings::irr::scene::IAnimatedMeshSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "addAnimatedMeshSceneNode", args, 7) };
}
auto ISceneManager::addLightSceneNode(GameBindings::irr::scene::ISceneNode arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::video::SColorf arg2, GameBindings::float_expr arg3, GameBindings::int_expr arg4) -> GameBindings::irr::scene::ILightSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "addLightSceneNode", args, 5) };
}
auto ISceneManager::addCameraSceneNode(GameBindings::irr::scene::ISceneNode arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2, GameBindings::int_expr arg3, GameBindings::bool_expr arg4) -> GameBindings::irr::scene::ICameraSceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "addCameraSceneNode", args, 5) };
}
auto ISceneManager::addSkyBoxSceneNode(GameBindings::irr::video::ITexture arg0, GameBindings::irr::video::ITexture arg1, GameBindings::irr::video::ITexture arg2, GameBindings::irr::video::ITexture arg3, GameBindings::irr::video::ITexture arg4, GameBindings::irr::video::ITexture arg5, GameBindings::irr::scene::ISceneNode arg6, GameBindings::int_expr arg7) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr }; 
    return { ::LM::call(expr, "addSkyBoxSceneNode", args, 8) };
}
auto ISceneManager::getMeshManipulator() -> GameBindings::irr::scene::IMeshManipulator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMeshManipulator", args, 0) };
}
auto ISceneManager::createFollowSplineAnimator(GameBindings::int_expr arg0, GameBindings::irr::core::ArrayOfVector3df arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::bool_expr arg4, GameBindings::bool_expr arg5) -> GameBindings::irr::scene::ISceneNodeAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "createFollowSplineAnimator", args, 6) };
}
auto ISceneManager::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISceneManager::getRootSceneNode() -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getRootSceneNode", args, 0) };
}

auto E_TERRAIN_PATCH_SIZE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_TERRAIN_PATCH_SIZE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_BUFFER_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_BUFFER_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SMeshBuffer::ref_BoundingBox() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_BoundingBox", args, 0) };
}
auto SMeshBuffer::set_BoundingBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_BoundingBox", args, 1) };
}
auto SMeshBuffer::get_Indices() -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Indices", args, 0) };
}
auto SMeshBuffer::get_Vertices() -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Vertices", args, 0) };
}
auto SMeshBuffer::ref_Vertices() -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> >& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Vertices", args, 0) };
}
auto SMeshBuffer::get_BoundingBox() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_BoundingBox", args, 0) };
}
auto SMeshBuffer::ref_Material() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Material", args, 0) };
}
auto SMeshBuffer::set_Material(GameBindings::irr::video::SMaterial arg0) -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Material", args, 1) };
}
auto SMeshBuffer::ref_MappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MappingHint_Index", args, 0) };
}
auto SMeshBuffer::get_Material() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Material", args, 0) };
}
auto SMeshBuffer::set_MappingHint_Index(GameBindings::irr::scene::E_HARDWARE_MAPPING arg0) -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MappingHint_Index", args, 1) };
}
auto SMeshBuffer::ref_Indices() -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> >& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Indices", args, 0) };
}
auto SMeshBuffer::tmp() -> GameBindings::irr::scene::SMeshBuffer
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto SMeshBuffer::get_MappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MappingHint_Vertex", args, 0) };
}
auto SMeshBuffer::get_MappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MappingHint_Index", args, 0) };
}
auto SMeshBuffer::set_MappingHint_Vertex(GameBindings::irr::scene::E_HARDWARE_MAPPING arg0) -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MappingHint_Vertex", args, 1) };
}
auto SMeshBuffer::set_Indices(MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > const& (end) */  arg0) -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Indices", args, 1) };
}
auto SMeshBuffer::set_Vertices(MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > const& (end) */  arg0) -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Vertices", args, 1) };
}
auto SMeshBuffer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SMeshBuffer::lm_new() -> GameBindings::irr::scene::SMeshBuffer
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto SMeshBuffer::ref_MappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MappingHint_Vertex", args, 0) };
}
auto SMeshBuffer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_HARDWARE_MAPPING::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_HARDWARE_MAPPING::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IMesh::getMeshBuffer(GameBindings::uint_expr arg0) -> GameBindings::irr::scene::IMeshBuffer
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMeshBuffer", args, 1) };
}
auto IMesh::getMeshBufferForMaterial(GameBindings::irr::video::SMaterial arg0) -> GameBindings::irr::scene::IMeshBuffer
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMeshBufferForMaterial", args, 1) };
}
auto IMesh::setBoundingBox(GameBindings::irr::core::aabbox3df arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setBoundingBox", args, 1) };
}
auto IMesh::setHardwareMappingHint(GameBindings::irr::scene::E_HARDWARE_MAPPING arg0, GameBindings::irr::scene::E_BUFFER_TYPE arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setHardwareMappingHint", args, 2) };
}
auto IMesh::getBoundingBox() -> GameBindings::irr::core::aabbox3df
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBoundingBox", args, 0) };
}
auto IMesh::getMeshBufferCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMeshBufferCount", args, 0) };
}
auto IMesh::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IMesh::setMaterialFlag(GameBindings::irr::video::E_MATERIAL_FLAG arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMaterialFlag", args, 2) };
}
auto IMesh::setDirty(GameBindings::irr::scene::E_BUFFER_TYPE arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setDirty", args, 1) };
}
auto IMesh::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ISceneNodeAnimator::animateNode(GameBindings::irr::scene::ISceneNode arg0, GameBindings::uint_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "animateNode", args, 2) };
}
auto ISceneNodeAnimator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISceneNodeAnimator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ISceneCollisionManager::getSceneNodeFromScreenCoordinatesBB(GameBindings::irr::core::vector2di arg0, GameBindings::int_expr arg1, GameBindings::bool_expr arg2, GameBindings::irr::scene::ISceneNode arg3) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "getSceneNodeFromScreenCoordinatesBB", args, 4) };
}
auto ISceneCollisionManager::getSceneNodeFromRayBB(GameBindings::irr::core::line3df arg0, GameBindings::int_expr arg1, GameBindings::bool_expr arg2, GameBindings::irr::scene::ISceneNode arg3) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "getSceneNodeFromRayBB", args, 4) };
}
auto ISceneCollisionManager::getCollisionPoint(GameBindings::irr::core::line3df arg0, GameBindings::irr::scene::ITriangleSelector arg1, GameBindings::irr::core::vector3df arg2, GameBindings::irr::core::triangle3df arg3, GameBindings::irr::scene::ISceneNode arg4) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "getCollisionPoint", args, 5) };
}
auto ISceneCollisionManager::getSceneNodeAndCollisionPointFromRay(GameBindings::irr::core::line3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::triangle3df arg2, GameBindings::int_expr arg3, GameBindings::irr::scene::ISceneNode arg4, GameBindings::bool_expr arg5) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "getSceneNodeAndCollisionPointFromRay", args, 6) };
}
auto ISceneCollisionManager::getRayFromScreenCoordinates(GameBindings::irr::core::vector2di arg0, GameBindings::irr::scene::ICameraSceneNode arg1) -> GameBindings::irr::core::line3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getRayFromScreenCoordinates", args, 2) };
}
auto ISceneCollisionManager::getSceneNodeFromCameraBB(GameBindings::irr::scene::ICameraSceneNode arg0, GameBindings::int_expr arg1, GameBindings::bool_expr arg2) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "getSceneNodeFromCameraBB", args, 3) };
}
auto ISceneCollisionManager::getCollisionResultPosition(GameBindings::irr::scene::ITriangleSelector arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::core::vector3df arg2, GameBindings::irr::core::vector3df arg3, GameBindings::irr::core::triangle3df arg4, GameBindings::irr::core::vector3df arg5, GameBindings::bool_expr arg6, GameBindings::irr::scene::ISceneNode arg7, GameBindings::float_expr arg8, GameBindings::irr::core::vector3df arg9) -> GameBindings::irr::core::vector3df
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr, arg9.expr }; 
    return { ::LM::call(expr, "getCollisionResultPosition", args, 10) };
}
auto ISceneCollisionManager::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ISceneCollisionManager::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
