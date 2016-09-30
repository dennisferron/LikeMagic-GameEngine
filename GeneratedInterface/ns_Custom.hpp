#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace Custom
	{

struct Shell
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct PhysicsAnimator
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Custom::PhysicsAnimator;
    auto lm_new(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Custom::PhysicsAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IrrlichtBulletDebugDrawer
{
    ::LM::ExprPtr expr;
    auto drawLine(GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3, GameBindings::Bullet::btVector3) -> GameBindings::void_expr;
    auto tmp(GameBindings::irr::video::IVideoDriver) -> GameBindings::Custom::IrrlichtBulletDebugDrawer;
    auto lm_new(GameBindings::irr::video::IVideoDriver) -> GameBindings::Custom::IrrlichtBulletDebugDrawer;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct MeshTools
{
    ::LM::ExprPtr expr;
    auto createHillMesh(GameBindings::Custom::SurfaceQuadTree, GameBindings::irr::core::rectf, GameBindings::double_expr, GameBindings::double_expr) -> GameBindings::irr::scene::IMesh;
    auto createMeshFromHeightmap(GameBindings::irr::video::IImage, GameBindings::irr::core::dimension2du, GameBindings::irr::core::vector2di, GameBindings::bool_expr) -> GameBindings::irr::scene::IMesh;
    auto createSoftBodyFromMesh(GameBindings::Bullet::btSoftBodyWorldInfo, GameBindings::irr::scene::IMesh) -> GameBindings::Bullet::btSoftBody;
    auto getBaseVertex(GameBindings::irr::scene::IMeshBuffer, GameBindings::int_expr) -> GameBindings::irr::video::S3DVertex;
    auto createMeshFromSoftBody(GameBindings::Bullet::btSoftBody) -> GameBindings::irr::scene::IMesh;
    auto lm_delete() -> GameBindings::void_expr;
    auto splitMeshZ(GameBindings::irr::scene::IMesh, GameBindings::float_expr, GameBindings::float_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::Custom::SplitMeshResult;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct LockAnimator
{
    ::LM::ExprPtr expr;
    auto ref_stop_rotation() -> GameBindings::bool_expr;
    auto set_stop_rotation(GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto tmp(GameBindings::Bullet::btMotionState, GameBindings::Bullet::btTransform) -> GameBindings::Custom::LockAnimator;
    auto lm_new(GameBindings::Bullet::btMotionState, GameBindings::Bullet::btTransform) -> GameBindings::Custom::LockAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_stop_rotation() -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct GearConstraint
{
    ::LM::ExprPtr expr;
    auto getRotZ(GameBindings::Bullet::btRigidBody) -> GameBindings::float_expr;
    auto tmp(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::float_expr) -> GameBindings::Custom::GearConstraint;
    auto lm_new(GameBindings::Bullet::btRigidBody, GameBindings::Bullet::btRigidBody, GameBindings::float_expr) -> GameBindings::Custom::GearConstraint;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SplitMeshResult
{
    ::LM::ExprPtr expr;
    auto get_right() -> GameBindings::irr::scene::IMesh;
    auto ref_right() -> GameBindings::irr::scene::IMesh;
    auto set_right(GameBindings::irr::scene::IMesh) -> GameBindings::irr::scene::IMesh;
    auto get_middle() -> GameBindings::irr::scene::IMesh;
    auto set_middle(GameBindings::irr::scene::IMesh) -> GameBindings::irr::scene::IMesh;
    auto ref_left() -> GameBindings::irr::scene::IMesh;
    auto get_left() -> GameBindings::irr::scene::IMesh;
    auto set_left(GameBindings::irr::scene::IMesh) -> GameBindings::irr::scene::IMesh;
    auto ref_middle() -> GameBindings::irr::scene::IMesh;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SceneNodePtrTest
{
    ::LM::ExprPtr expr;
    auto addLightSceneNode(GameBindings::irr::scene::ISceneManager) -> GameBindings::void_expr;
    auto stringToSceneNodePtr(GameBindings::string_expr) -> GameBindings::irr::scene::ISceneNode;
    auto sceneNodePtrToString(GameBindings::irr::scene::ISceneNode) -> GameBindings::string_expr;
    auto voidPtrToSceneNodePtr(GameBindings::void_expr) -> GameBindings::irr::scene::ISceneNode;
    auto sceneNodePtrToVoidPtr(GameBindings::irr::scene::ISceneNode) -> GameBindings::void_expr;
    auto printSceneNodePtr(GameBindings::irr::scene::ISceneNode) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct FlagBits_of_ISceneNode
{
    ::LM::ExprPtr expr;
    auto embedNumber(GameBindings::int_expr, GameBindings::int_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto setBit(GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getBit(GameBindings::int_expr) -> GameBindings::bool_expr;
    auto tmp(GameBindings::irr::scene::ISceneNode) -> GameBindings::Custom::FlagBits_of_ISceneNode;
    auto lm_new(GameBindings::irr::scene::ISceneNode) -> GameBindings::Custom::FlagBits_of_ISceneNode;
    auto lm_delete() -> GameBindings::void_expr;
    auto extractNumber(GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::uint_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct KinematicAnimator
{
    ::LM::ExprPtr expr;
    auto tmp(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Custom::KinematicAnimator;
    auto lm_new(GameBindings::Bullet::btTransform, GameBindings::Bullet::btTransform) -> GameBindings::Custom::KinematicAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ScriptObjAnimator
{
    ::LM::ExprPtr expr;
    auto findIn(GameBindings::irr::scene::ISceneNode) -> GameBindings::Custom::ScriptObjAnimator;
    auto getScriptObj() -> GameBindings::void_expr;
    auto tmp(GameBindings::void_expr) -> GameBindings::Custom::ScriptObjAnimator;
    auto lm_new(GameBindings::void_expr) -> GameBindings::Custom::ScriptObjAnimator;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SoftBodyMeshSynchronizer
{
    ::LM::ExprPtr expr;
    auto sync() -> GameBindings::void_expr;
    auto tmp(GameBindings::Bullet::btSoftBody, GameBindings::irr::scene::IMeshBuffer) -> GameBindings::Custom::SoftBodyMeshSynchronizer;
    auto lm_new(GameBindings::Bullet::btSoftBody, GameBindings::irr::scene::IMeshBuffer) -> GameBindings::Custom::SoftBodyMeshSynchronizer;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SurfaceQuadTree
{
    ::LM::ExprPtr expr;
    auto fit(GameBindings::irr::core::dimension2df, GameBindings::std::vector_of_double) -> GameBindings::void_expr;
    auto triangulate(MissingType /* C++ std::vector<boost::intrusive_ptr<Bindings::Custom::PossibleVertex>, std::allocator<boost::intrusive_ptr<Bindings::Custom::PossibleVertex> > >& (end) */ , GameBindings::irr::core::rectf, GameBindings::double_expr, GameBindings::double_expr, MissingType /* C++ Bindings::Custom::SurfaceQuadTree::Visitor* (end) */ ) -> GameBindings::Custom::Shell;
    auto tmp(GameBindings::irr::core::rectf, GameBindings::TPS::ThinPlateQuilt, GameBindings::string_expr) -> GameBindings::Custom::SurfaceQuadTree;
    auto lm_new(GameBindings::irr::core::rectf, GameBindings::TPS::ThinPlateQuilt, GameBindings::string_expr) -> GameBindings::Custom::SurfaceQuadTree;
    auto lm_delete() -> GameBindings::void_expr;
    auto split(GameBindings::int_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

	}
}
