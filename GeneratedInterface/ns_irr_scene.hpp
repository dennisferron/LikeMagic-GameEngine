#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace scene
		{

struct IMeshManipulator
{
    ::LM::ExprPtr expr;
    auto makePlanarTextureMapping(GameBindings::irr::scene::IMeshBuffer, GameBindings::float_expr, GameBindings::float_expr, GameBindings::uchar_expr, GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_HARDWARE_MAPPING
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SMeshBuffer
{
    ::LM::ExprPtr expr;
    auto get_BoundingBox() -> GameBindings::irr::core::aabbox3df;
    auto set_BoundingBox(GameBindings::irr::core::aabbox3df) -> GameBindings::irr::core::aabbox3df;
    auto ref_BoundingBox() -> GameBindings::irr::core::aabbox3df;
    auto get_Indices() -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > */ ;
    auto set_Indices(MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > const& (end) */ ) -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > */ ;
    auto set_Vertices(MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > const& (end) */ ) -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > */ ;
    auto ref_Material() -> GameBindings::irr::video::SMaterial;
    auto get_Material() -> GameBindings::irr::video::SMaterial;
    auto set_Material(GameBindings::irr::video::SMaterial) -> GameBindings::irr::video::SMaterial;
    auto ref_MappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto get_Vertices() -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> > */ ;
    auto get_MappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto ref_Indices() -> MissingType /* C++ irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> >& */ ;
    auto set_MappingHint_Index(GameBindings::irr::scene::E_HARDWARE_MAPPING) -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto ref_Vertices() -> MissingType /* C++ irr::core::array<irr::video::S3DVertex, irr::core::irrAllocator<irr::video::S3DVertex> >& */ ;
    auto ref_MappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto get_MappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto tmp() -> GameBindings::irr::scene::SMeshBuffer;
    auto lm_new() -> GameBindings::irr::scene::SMeshBuffer;
    auto set_MappingHint_Vertex(GameBindings::irr::scene::E_HARDWARE_MAPPING) -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ITerrainSceneNode
{
    ::LM::ExprPtr expr;
    auto scaleTexture(GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ISceneNode
{
    ::LM::ExprPtr expr;
    auto setDebugDataVisible(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto setID(GameBindings::int_expr) -> GameBindings::void_expr;
    auto getID() -> GameBindings::int_expr;
    auto setMaterialType(GameBindings::irr::video::E_MATERIAL_TYPE) -> GameBindings::void_expr;
    auto setMaterialTexture(GameBindings::uint_expr, GameBindings::irr::video::ITexture) -> GameBindings::void_expr;
    auto remove() -> GameBindings::void_expr;
    auto removeAnimator(GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto updateAbsolutePosition() -> GameBindings::void_expr;
    auto getAbsolutePosition() -> GameBindings::irr::core::vector3df;
    auto getRotation() -> GameBindings::irr::core::vector3df;
    auto OnAnimate(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto setTriangleSelector(GameBindings::irr::scene::ITriangleSelector) -> GameBindings::void_expr;
    auto setPosition(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto getScale() -> GameBindings::irr::core::vector3df;
    auto getAnimators() -> GameBindings::irr::core::ListOfAnim;
    auto isDebugDataVisible() -> GameBindings::uint_expr;
    auto setRotation(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto setParent(GameBindings::irr::scene::ISceneNode) -> GameBindings::void_expr;
    auto getRelativeTransformation() -> GameBindings::irr::core::matrix4;
    auto getName() -> GameBindings::char_expr;
    auto removeAnimators() -> GameBindings::void_expr;
    auto getPosition() -> GameBindings::irr::core::vector3df;
    auto getMaterialCount() -> GameBindings::uint_expr;
    auto setScale(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto render() -> GameBindings::void_expr;
    auto getMaterial(GameBindings::uint_expr) -> GameBindings::irr::video::SMaterial;
    auto OnRegisterSceneNode() -> GameBindings::void_expr;
    auto getBoundingBox() -> GameBindings::irr::core::aabbox3df;
    auto setMaterialFlag(GameBindings::irr::video::E_MATERIAL_FLAG, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setVisible(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto addChild(GameBindings::irr::scene::ISceneNode) -> GameBindings::void_expr;
    auto getAbsoluteTransformation() -> GameBindings::irr::core::matrix4;
    auto addAnimator(GameBindings::irr::scene::ISceneNodeAnimator) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_TERRAIN_PATCH_SIZE
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SMesh
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ITriangleSelector
{
    ::LM::ExprPtr expr;
    auto getTrianglesForLine(GameBindings::irr::core::triangle3df, GameBindings::int_expr, GameBindings::int_expr, GameBindings::irr::core::line3df, GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto getTrianglesForNode(GameBindings::irr::core::triangle3df, GameBindings::int_expr, GameBindings::int_expr, GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto getTriangleCount() -> GameBindings::int_expr;
    auto getTrianglesForBox(GameBindings::irr::core::triangle3df, GameBindings::int_expr, GameBindings::int_expr, GameBindings::irr::core::aabbox3df, GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getSceneNodeForTriangle(GameBindings::uint_expr) -> GameBindings::irr::scene::ISceneNode;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IAnimatedMeshSceneNode
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto setAnimationSpeed(GameBindings::float_expr) -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ILightSceneNode
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ISceneNodeAnimator
{
    ::LM::ExprPtr expr;
    auto animateNode(GameBindings::irr::scene::ISceneNode, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IAnimatedMesh
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ICameraSceneNode
{
    ::LM::ExprPtr expr;
    auto setTarget(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto setUpVector(GameBindings::irr::core::vector3df) -> GameBindings::void_expr;
    auto OnEvent(GameBindings::irr::gui::SEvent) -> GameBindings::bool_expr;
    auto isOrthogonal() -> GameBindings::bool_expr;
    auto setInputReceiverEnabled(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setAspectRatio(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getViewMatrixAffector() -> GameBindings::irr::core::matrix4;
    auto setFarValue(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getTargetAndRotationBinding() -> GameBindings::bool_expr;
    auto getUpVector() -> GameBindings::irr::core::vector3df;
    auto getTarget() -> GameBindings::irr::core::vector3df;
    auto getNearValue() -> GameBindings::float_expr;
    auto getFOV() -> GameBindings::float_expr;
    auto isInputReceiverEnabled() -> GameBindings::bool_expr;
    auto getViewMatrix() -> GameBindings::irr::core::matrix4;
    auto getViewFrustum() -> MissingType /* C++ irr::scene::SViewFrustum const* */ ;
    auto setProjectionMatrix(GameBindings::irr::core::matrix4, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getFarValue() -> GameBindings::float_expr;
    auto setNearValue(GameBindings::float_expr) -> GameBindings::void_expr;
    auto getAspectRatio() -> GameBindings::float_expr;
    auto setViewMatrixAffector(GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto bindTargetAndRotation(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setFOV(GameBindings::float_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto getProjectionMatrix() -> GameBindings::irr::core::matrix4;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IMeshSceneNode
{
    ::LM::ExprPtr expr;
    auto setReadOnlyMaterials(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setMesh(GameBindings::irr::scene::IMesh) -> GameBindings::void_expr;
    auto isReadOnlyMaterials() -> GameBindings::bool_expr;
    auto getMesh() -> GameBindings::irr::scene::IMesh;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ISceneManager
{
    ::LM::ExprPtr expr;
    auto addTerrainSceneNodeFromPath(GameBindings::irr::core::irrFsStr, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColor, GameBindings::int_expr, GameBindings::irr::scene::E_TERRAIN_PATCH_SIZE, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ITerrainSceneNode;
    auto addTerrainSceneNodeFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */ , GameBindings::irr::scene::ISceneNode, GameBindings::int_expr, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColor, GameBindings::int_expr, GameBindings::irr::scene::E_TERRAIN_PATCH_SIZE, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ITerrainSceneNode;
    auto saveSceneToIReadFile(MissingType /* C++ irr::io::IWriteFile* (end) */ , GameBindings::irr::io::ISceneUserDataSerializer, GameBindings::irr::scene::ISceneNode) -> GameBindings::bool_expr;
    auto loadSceneFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */ , GameBindings::irr::io::ISceneUserDataSerializer, GameBindings::irr::scene::ISceneNode) -> GameBindings::bool_expr;
    auto createOctreeTriangleSelector(GameBindings::irr::scene::IMesh, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr) -> GameBindings::irr::scene::ITriangleSelector;
    auto createTriangleSelector(GameBindings::irr::scene::IAnimatedMeshSceneNode) -> GameBindings::irr::scene::ITriangleSelector;
    auto createTriangleSelector(GameBindings::irr::scene::IMesh, GameBindings::irr::scene::ISceneNode) -> GameBindings::irr::scene::ITriangleSelector;
    auto addSkyDomeSceneNode(GameBindings::irr::video::ITexture, GameBindings::uint_expr, GameBindings::uint_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr) -> GameBindings::irr::scene::ISceneNode;
    auto addSkyBoxSceneNode(GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::irr::video::ITexture, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr) -> GameBindings::irr::scene::ISceneNode;
    auto getSceneCollisionManager() -> GameBindings::irr::scene::ISceneCollisionManager;
    auto createFollowSplineAnimator(GameBindings::int_expr, GameBindings::irr::core::ArrayOfVector3df, GameBindings::float_expr, GameBindings::float_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ISceneNodeAnimator;
    auto getGeometryCreator() -> GameBindings::irr::scene::IGeometryCreator;
    auto drawAll() -> GameBindings::void_expr;
    auto getMeshFromPath(GameBindings::irr::core::irrFsStr) -> GameBindings::irr::scene::IAnimatedMesh;
    auto addLightSceneNode(GameBindings::irr::scene::ISceneNode, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColorf, GameBindings::float_expr, GameBindings::int_expr) -> GameBindings::irr::scene::ILightSceneNode;
    auto loadSceneFromPath(GameBindings::irr::core::irrFsStr, GameBindings::irr::io::ISceneUserDataSerializer, GameBindings::irr::scene::ISceneNode) -> GameBindings::bool_expr;
    auto createRotationAnimator(GameBindings::irr::core::vector3df) -> GameBindings::irr::scene::ISceneNodeAnimator;
    auto addCameraSceneNodeMaya(GameBindings::irr::scene::ISceneNode, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::int_expr, GameBindings::float_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ICameraSceneNode;
    auto addCameraSceneNodeFPS(GameBindings::irr::scene::ISceneNode, GameBindings::float_expr, GameBindings::float_expr, GameBindings::int_expr, GameBindings::irr::SKeyMap, GameBindings::int_expr, GameBindings::bool_expr, GameBindings::float_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ICameraSceneNode;
    auto addAnimatedMeshSceneNode(GameBindings::irr::scene::IAnimatedMesh, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::bool_expr) -> GameBindings::irr::scene::IAnimatedMeshSceneNode;
    auto getMeshFromIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */ ) -> GameBindings::irr::scene::IAnimatedMesh;
    auto getMeshManipulator() -> GameBindings::irr::scene::IMeshManipulator;
    auto lm_delete() -> GameBindings::void_expr;
    auto getRootSceneNode() -> GameBindings::irr::scene::ISceneNode;
    auto setAmbientLight(GameBindings::irr::video::SColorf) -> GameBindings::void_expr;
    auto addCameraSceneNode(GameBindings::irr::scene::ISceneNode, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ICameraSceneNode;
    auto saveSceneToPath(GameBindings::irr::core::irrFsStr, GameBindings::irr::io::ISceneUserDataSerializer, GameBindings::irr::scene::ISceneNode) -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto addMeshSceneNode(GameBindings::irr::scene::IMesh, GameBindings::irr::scene::ISceneNode, GameBindings::int_expr, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::bool_expr) -> GameBindings::irr::scene::IMeshSceneNode;
};struct ISceneCollisionManager
{
    ::LM::ExprPtr expr;
    auto getSceneNodeFromScreenCoordinatesBB(GameBindings::irr::core::vector2di, GameBindings::int_expr, GameBindings::bool_expr, GameBindings::irr::scene::ISceneNode) -> GameBindings::irr::scene::ISceneNode;
    auto getSceneNodeFromRayBB(GameBindings::irr::core::line3df, GameBindings::int_expr, GameBindings::bool_expr, GameBindings::irr::scene::ISceneNode) -> GameBindings::irr::scene::ISceneNode;
    auto getCollisionResultPosition(GameBindings::irr::scene::ITriangleSelector, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::triangle3df, GameBindings::irr::core::vector3df, GameBindings::bool_expr, GameBindings::irr::scene::ISceneNode, GameBindings::float_expr, GameBindings::irr::core::vector3df) -> GameBindings::irr::core::vector3df;
    auto getSceneNodeAndCollisionPointFromRay(GameBindings::irr::core::line3df, GameBindings::irr::core::vector3df, GameBindings::irr::core::triangle3df, GameBindings::int_expr, GameBindings::irr::scene::ISceneNode, GameBindings::bool_expr) -> GameBindings::irr::scene::ISceneNode;
    auto getCollisionPoint(GameBindings::irr::core::line3df, GameBindings::irr::scene::ITriangleSelector, GameBindings::irr::core::vector3df, GameBindings::irr::core::triangle3df, GameBindings::irr::scene::ISceneNode) -> GameBindings::bool_expr;
    auto getRayFromScreenCoordinates(GameBindings::irr::core::vector2di, GameBindings::irr::scene::ICameraSceneNode) -> GameBindings::irr::core::line3df;
    auto lm_delete() -> GameBindings::void_expr;
    auto getSceneNodeFromCameraBB(GameBindings::irr::scene::ICameraSceneNode, GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::irr::scene::ISceneNode;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IMeshBuffer
{
    ::LM::ExprPtr expr;
    auto getVertices_nc() -> GameBindings::void_expr;
    auto getVertices_c() -> GameBindings::void_expr;
    auto getTCoords_nc(GameBindings::uint_expr) -> GameBindings::irr::core::vector2df;
    auto getTCoords_c(GameBindings::uint_expr) -> GameBindings::irr::core::vector2df;
    auto getNormal_nc(GameBindings::uint_expr) -> GameBindings::irr::core::vector3df;
    auto getNormal_c(GameBindings::uint_expr) -> GameBindings::irr::core::vector3df;
    auto getMaterial_nc() -> GameBindings::irr::video::SMaterial;
    auto getIndices_nc() -> GameBindings::ushort_expr;
    auto getPosition_nc(GameBindings::uint_expr) -> GameBindings::irr::core::vector3df;
    auto getVertexType() -> GameBindings::irr::video::E_VERTEX_TYPE;
    auto getPosition_c(GameBindings::uint_expr) -> GameBindings::irr::core::vector3df;
    auto recalculateBoundingBox() -> GameBindings::void_expr;
    auto getVertexCount() -> GameBindings::uint_expr;
    auto getIndexCount() -> GameBindings::uint_expr;
    auto getHardwareMappingHint_Vertex() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto setDirty(GameBindings::irr::scene::E_BUFFER_TYPE) -> GameBindings::void_expr;
    auto append(GameBindings::irr::scene::IMeshBuffer) -> GameBindings::void_expr;
    auto append(GameBindings::void_expr, GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto getHardwareMappingHint_Index() -> GameBindings::irr::scene::E_HARDWARE_MAPPING;
    auto setHardwareMappingHint(GameBindings::irr::scene::E_HARDWARE_MAPPING, GameBindings::irr::scene::E_BUFFER_TYPE) -> GameBindings::void_expr;
    auto getBoundingBox() -> GameBindings::irr::core::aabbox3df;
    auto getIndexType() -> MissingType /* C++ irr::video::E_INDEX_TYPE */ ;
    auto getIndices_c() -> GameBindings::ushort_expr;
    auto setBoundingBox(GameBindings::irr::core::aabbox3df) -> GameBindings::void_expr;
    auto getMaterial_c() -> GameBindings::irr::video::SMaterial;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IGeometryCreator
{
    ::LM::ExprPtr expr;
    auto createVolumeLightMesh(GameBindings::uint_expr, GameBindings::uint_expr, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::float_expr, GameBindings::irr::core::vector3df) -> GameBindings::irr::scene::IMesh;
    auto createTerrainMesh(GameBindings::irr::video::IImage, GameBindings::irr::video::IImage, GameBindings::irr::core::dimension2df, GameBindings::float_expr, GameBindings::irr::video::IVideoDriver, GameBindings::irr::core::dimension2du, GameBindings::bool_expr) -> GameBindings::irr::scene::IMesh;
    auto createPlaneMesh(GameBindings::irr::core::dimension2df, GameBindings::irr::core::dimension2du, GameBindings::irr::video::SMaterial, GameBindings::irr::core::dimension2df) -> GameBindings::irr::scene::IMesh;
    auto createHillPlaneMesh(GameBindings::irr::core::dimension2df, GameBindings::irr::core::dimension2du, GameBindings::irr::video::SMaterial, GameBindings::float_expr, GameBindings::irr::core::dimension2df, GameBindings::irr::core::dimension2df) -> GameBindings::irr::scene::IMesh;
    auto createSphereMesh(GameBindings::float_expr, GameBindings::uint_expr, GameBindings::uint_expr) -> GameBindings::irr::scene::IMesh;
    auto createCubeMesh(GameBindings::irr::core::vector3df) -> GameBindings::irr::scene::IMesh;
    auto createConeMesh(GameBindings::float_expr, GameBindings::float_expr, GameBindings::uint_expr, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::float_expr) -> GameBindings::irr::scene::IMesh;
    auto createArrowMesh(GameBindings::uint_expr, GameBindings::uint_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor) -> GameBindings::irr::scene::IMesh;
    auto lm_delete() -> GameBindings::void_expr;
    auto createCylinderMesh(GameBindings::float_expr, GameBindings::float_expr, GameBindings::uint_expr, GameBindings::irr::video::SColor, GameBindings::bool_expr, GameBindings::float_expr) -> GameBindings::irr::scene::IMesh;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_BUFFER_TYPE
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IMesh
{
    ::LM::ExprPtr expr;
    auto getMeshBuffer(GameBindings::uint_expr) -> GameBindings::irr::scene::IMeshBuffer;
    auto getMeshBufferForMaterial(GameBindings::irr::video::SMaterial) -> GameBindings::irr::scene::IMeshBuffer;
    auto setHardwareMappingHint(GameBindings::irr::scene::E_HARDWARE_MAPPING, GameBindings::irr::scene::E_BUFFER_TYPE) -> GameBindings::void_expr;
    auto setDirty(GameBindings::irr::scene::E_BUFFER_TYPE) -> GameBindings::void_expr;
    auto getMeshBufferCount() -> GameBindings::uint_expr;
    auto setMaterialFlag(GameBindings::irr::video::E_MATERIAL_FLAG, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getBoundingBox() -> GameBindings::irr::core::aabbox3df;
    auto setBoundingBox(GameBindings::irr::core::aabbox3df) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
