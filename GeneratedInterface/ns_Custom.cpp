#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_global.hpp"
#include "ns_Custom.hpp"
#include "ns_Bullet.hpp"
#include "ns_irr_core.hpp"
#include "ns_irr_scene.hpp"
#include "ns_TPS.hpp"
#include "ns_irr_video.hpp"
#include "ns_std.hpp"

namespace GameBindings
{
	namespace Custom
	{

auto SplitMeshResult::ref_right() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_right", args, 0) };
}
auto SplitMeshResult::get_right() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_right", args, 0) };
}
auto SplitMeshResult::get_middle() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_middle", args, 0) };
}
auto SplitMeshResult::set_middle(GameBindings::irr::scene::IMesh arg0) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_middle", args, 1) };
}
auto SplitMeshResult::ref_left() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_left", args, 0) };
}
auto SplitMeshResult::set_right(GameBindings::irr::scene::IMesh arg0) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_right", args, 1) };
}
auto SplitMeshResult::get_left() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_left", args, 0) };
}
auto SplitMeshResult::set_left(GameBindings::irr::scene::IMesh arg0) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_left", args, 1) };
}
auto SplitMeshResult::ref_middle() -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_middle", args, 0) };
}
auto SplitMeshResult::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SplitMeshResult::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IrrlichtBulletDebugDrawer::drawLine(GameBindings::Bullet::btVector3 arg0, GameBindings::Bullet::btVector3 arg1, GameBindings::Bullet::btVector3 arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "drawLine", args, 3) };
}
auto IrrlichtBulletDebugDrawer::tmp(GameBindings::irr::video::IVideoDriver arg0) -> GameBindings::Custom::IrrlichtBulletDebugDrawer
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto IrrlichtBulletDebugDrawer::lm_new(GameBindings::irr::video::IVideoDriver arg0) -> GameBindings::Custom::IrrlichtBulletDebugDrawer
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto IrrlichtBulletDebugDrawer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IrrlichtBulletDebugDrawer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SceneNodePtrTest::addLightSceneNode(GameBindings::irr::scene::ISceneManager arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addLightSceneNode", args, 1) };
}
auto SceneNodePtrTest::stringToSceneNodePtr(GameBindings::string_expr arg0) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "stringToSceneNodePtr", args, 1) };
}
auto SceneNodePtrTest::voidPtrToSceneNodePtr(GameBindings::void_expr arg0) -> GameBindings::irr::scene::ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "voidPtrToSceneNodePtr", args, 1) };
}
auto SceneNodePtrTest::sceneNodePtrToVoidPtr(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "sceneNodePtrToVoidPtr", args, 1) };
}
auto SceneNodePtrTest::sceneNodePtrToString(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "sceneNodePtrToString", args, 1) };
}
auto SceneNodePtrTest::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SceneNodePtrTest::printSceneNodePtr(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "printSceneNodePtr", args, 1) };
}
auto SceneNodePtrTest::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SurfaceQuadTree::fit(GameBindings::irr::core::dimension2df arg0, GameBindings::std::vector_of_double arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "fit", args, 2) };
}
auto SurfaceQuadTree::split(GameBindings::int_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "split", args, 1) };
}
auto SurfaceQuadTree::triangulate(MissingType /* C++ std::vector<boost::intrusive_ptr<Bindings::Custom::PossibleVertex>, std::allocator<boost::intrusive_ptr<Bindings::Custom::PossibleVertex> > >& (end) */  arg0, GameBindings::irr::core::rectf arg1, GameBindings::double_expr arg2, GameBindings::double_expr arg3, MissingType /* C++ Bindings::Custom::SurfaceQuadTree::Visitor* (end) */  arg4) -> GameBindings::Custom::Shell
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "triangulate", args, 5) };
}
auto SurfaceQuadTree::tmp(GameBindings::irr::core::rectf arg0, GameBindings::TPS::ThinPlateQuilt arg1, GameBindings::string_expr arg2) -> GameBindings::Custom::SurfaceQuadTree
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto SurfaceQuadTree::lm_new(GameBindings::irr::core::rectf arg0, GameBindings::TPS::ThinPlateQuilt arg1, GameBindings::string_expr arg2) -> GameBindings::Custom::SurfaceQuadTree
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto SurfaceQuadTree::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SurfaceQuadTree::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto Shell::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto Shell::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto FlagBits_of_ISceneNode::embedNumber(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::uint_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "embedNumber", args, 3) };
}
auto FlagBits_of_ISceneNode::getBit(GameBindings::int_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getBit", args, 1) };
}
auto FlagBits_of_ISceneNode::tmp(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::Custom::FlagBits_of_ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto FlagBits_of_ISceneNode::lm_new(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::Custom::FlagBits_of_ISceneNode
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto FlagBits_of_ISceneNode::extractNumber(GameBindings::int_expr arg0, GameBindings::int_expr arg1) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "extractNumber", args, 2) };
}
auto FlagBits_of_ISceneNode::setBit(GameBindings::int_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setBit", args, 2) };
}
auto FlagBits_of_ISceneNode::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto FlagBits_of_ISceneNode::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto MeshTools::createHillMesh(GameBindings::Custom::SurfaceQuadTree arg0, GameBindings::irr::core::rectf arg1, GameBindings::double_expr arg2, GameBindings::double_expr arg3) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "createHillMesh", args, 4) };
}
auto MeshTools::createMeshFromHeightmap(GameBindings::irr::video::IImage arg0, GameBindings::irr::core::dimension2du arg1, GameBindings::irr::core::vector2di arg2, GameBindings::bool_expr arg3) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "createMeshFromHeightmap", args, 4) };
}
auto MeshTools::splitMeshZ(GameBindings::irr::scene::IMesh arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::bool_expr arg3, GameBindings::bool_expr arg4) -> GameBindings::Custom::SplitMeshResult
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "splitMeshZ", args, 5) };
}
auto MeshTools::createSoftBodyFromMesh(GameBindings::Bullet::btSoftBodyWorldInfo arg0, GameBindings::irr::scene::IMesh arg1) -> GameBindings::Bullet::btSoftBody
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createSoftBodyFromMesh", args, 2) };
}
auto MeshTools::getBaseVertex(GameBindings::irr::scene::IMeshBuffer arg0, GameBindings::int_expr arg1) -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "getBaseVertex", args, 2) };
}
auto MeshTools::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto MeshTools::createMeshFromSoftBody(GameBindings::Bullet::btSoftBody arg0) -> GameBindings::irr::scene::IMesh
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createMeshFromSoftBody", args, 1) };
}
auto MeshTools::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SoftBodyMeshSynchronizer::sync() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "sync", args, 0) };
}
auto SoftBodyMeshSynchronizer::tmp(GameBindings::Bullet::btSoftBody arg0, GameBindings::irr::scene::IMeshBuffer arg1) -> GameBindings::Custom::SoftBodyMeshSynchronizer
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto SoftBodyMeshSynchronizer::lm_new(GameBindings::Bullet::btSoftBody arg0, GameBindings::irr::scene::IMeshBuffer arg1) -> GameBindings::Custom::SoftBodyMeshSynchronizer
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto SoftBodyMeshSynchronizer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SoftBodyMeshSynchronizer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto GearConstraint::tmp(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::float_expr arg2) -> GameBindings::Custom::GearConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "tmp", args, 3) };
}
auto GearConstraint::getRotZ(GameBindings::Bullet::btRigidBody arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getRotZ", args, 1) };
}
auto GearConstraint::lm_new(GameBindings::Bullet::btRigidBody arg0, GameBindings::Bullet::btRigidBody arg1, GameBindings::float_expr arg2) -> GameBindings::Custom::GearConstraint
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "new", args, 3) };
}
auto GearConstraint::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto GearConstraint::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ScriptObjAnimator::getScriptObj() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getScriptObj", args, 0) };
}
auto ScriptObjAnimator::tmp(GameBindings::void_expr arg0) -> GameBindings::Custom::ScriptObjAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto ScriptObjAnimator::lm_new(GameBindings::void_expr arg0) -> GameBindings::Custom::ScriptObjAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto ScriptObjAnimator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ScriptObjAnimator::findIn(GameBindings::irr::scene::ISceneNode arg0) -> GameBindings::Custom::ScriptObjAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "findIn", args, 1) };
}
auto ScriptObjAnimator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto KinematicAnimator::tmp(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::KinematicAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto KinematicAnimator::lm_new(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::KinematicAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto KinematicAnimator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto KinematicAnimator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto PhysicsAnimator::tmp(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::PhysicsAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto PhysicsAnimator::lm_new(GameBindings::Bullet::btTransform arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::PhysicsAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto PhysicsAnimator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto PhysicsAnimator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto LockAnimator::ref_stop_rotation() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_stop_rotation", args, 0) };
}
auto LockAnimator::set_stop_rotation(GameBindings::bool_expr arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_stop_rotation", args, 1) };
}
auto LockAnimator::tmp(GameBindings::Bullet::btMotionState arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::LockAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "tmp", args, 2) };
}
auto LockAnimator::get_stop_rotation() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_stop_rotation", args, 0) };
}
auto LockAnimator::lm_new(GameBindings::Bullet::btMotionState arg0, GameBindings::Bullet::btTransform arg1) -> GameBindings::Custom::LockAnimator
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "new", args, 2) };
}
auto LockAnimator::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto LockAnimator::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

	}
}
