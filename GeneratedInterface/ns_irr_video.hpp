#pragma once

#include "forward_declares.hpp"

#include "LikeMagic/Exprs/Expr.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace video
		{

struct S3DVertex
{
    ::LM::ExprPtr expr;
    auto tmpWithFloats(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::irr::video::SColor, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::video::S3DVertex;
    auto newWithFloats(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::irr::video::SColor, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::video::S3DVertex;
    auto tmpWithVector3df(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColor, GameBindings::irr::core::vector2df) -> GameBindings::irr::video::S3DVertex;
    auto tmp() -> GameBindings::irr::video::S3DVertex;
    auto newWithVector3df(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColor, GameBindings::irr::core::vector2df) -> GameBindings::irr::video::S3DVertex;
    auto lm_new() -> GameBindings::irr::video::S3DVertex;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_TRANSFORMATION_STATE
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_TRANSFORMATION_STATE) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_TRANSFORMATION_STATE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_MATERIAL_TYPE
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_MATERIAL_TYPE) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_MATERIAL_TYPE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct ITexture
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IVideoDriver
{
    ::LM::ExprPtr expr;
    auto setRenderTargetFromEnum(MissingType /* C++ irr::video::E_RENDER_TARGET (end) */ , GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::video::SColor) -> GameBindings::bool_expr;
    auto drawIndexedTriangleListS3DVertex(GameBindings::irr::video::S3DVertex, GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto drawIndexedTriangleListS3DVertexTangents(MissingType /* C++ irr::video::S3DVertexTangents const* (end) */ , GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto drawIndexedTriangleFanS3DVertex(GameBindings::irr::video::S3DVertex, GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto drawIndexedTriangleFanS3DVertex2TCoords(MissingType /* C++ irr::video::S3DVertex2TCoords const* (end) */ , GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto drawIndexedTriangleFanS3DVertexTangents(MissingType /* C++ irr::video::S3DVertexTangents const* (end) */ , GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto draw2DRectangle(GameBindings::irr::video::SColor, GameBindings::irr::core::recti, GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto draw2DRectangle(GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto draw2DImageBatch(GameBindings::irr::video::ITexture, MissingType /* C++ irr::core::array<irr::core::vector2d<int>, irr::core::irrAllocator<irr::core::vector2d<int> > > const& (end) */ , MissingType /* C++ irr::core::array<irr::core::rect<int>, irr::core::irrAllocator<irr::core::rect<int> > > const& (end) */ , GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto draw2DImageBatch(GameBindings::irr::video::ITexture, GameBindings::irr::core::vector2di, MissingType /* C++ irr::core::array<irr::core::rect<int>, irr::core::irrAllocator<irr::core::rect<int> > > const& (end) */ , MissingType /* C++ irr::core::array<int, irr::core::irrAllocator<int> > const& (end) */ , GameBindings::int_expr, GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto draw2DImageFromRectToRect(GameBindings::irr::video::ITexture, GameBindings::irr::core::recti, GameBindings::irr::core::recti, GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto addRenderTargetTexture(GameBindings::irr::core::dimension2du, GameBindings::irr::core::irrFsStr, MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ ) -> GameBindings::irr::video::ITexture;
    auto getVendorInfo() -> GameBindings::irr::core::irrFsStr;
    auto writeImageToFileWithPath(GameBindings::irr::video::IImage, GameBindings::irr::core::irrFsStr, GameBindings::uint_expr) -> GameBindings::bool_expr;
    auto createImageFromFileWithPath(GameBindings::irr::core::irrFsStr) -> GameBindings::irr::video::IImage;
    auto createImageWithSize(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ , GameBindings::irr::core::dimension2du) -> GameBindings::irr::video::IImage;
    auto createImageFromImage(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ , GameBindings::irr::video::IImage) -> GameBindings::irr::video::IImage;
    auto createImageFromImage(GameBindings::irr::video::IImage, GameBindings::irr::core::vector2di, GameBindings::irr::core::dimension2du) -> GameBindings::irr::video::IImage;
    auto addTexture(GameBindings::irr::core::irrFsStr, GameBindings::irr::video::IImage, GameBindings::void_expr) -> GameBindings::irr::video::ITexture;
    auto getTexture(GameBindings::irr::core::irrFsStr) -> GameBindings::irr::video::ITexture;
    auto getTextureIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */ ) -> GameBindings::irr::video::ITexture;
    auto drawStencilShadowVolume(GameBindings::irr::core::ArrayOfVector3df, GameBindings::bool_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto makeColorKeyTextureWithColor(GameBindings::irr::video::ITexture, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto endScene() -> GameBindings::bool_expr;
    auto createImageFromFileWithIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */ ) -> GameBindings::irr::video::IImage;
    auto removeAllTextures() -> GameBindings::void_expr;
    auto turnLightOn(GameBindings::int_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setRenderTargetFromArray(MissingType /* C++ irr::core::array<irr::video::IRenderTarget, irr::core::irrAllocator<irr::video::IRenderTarget> > const& (end) */ , GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::video::SColor) -> GameBindings::bool_expr;
    auto addExternalImageLoader(MissingType /* C++ irr::video::IImageLoader* (end) */ ) -> GameBindings::void_expr;
    auto createImageFromData(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ , GameBindings::irr::core::dimension2du, GameBindings::void_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::irr::video::IImage;
    auto setViewPort(GameBindings::irr::core::recti) -> GameBindings::void_expr;
    auto setMinHardwareBufferVertexCount(GameBindings::uint_expr) -> GameBindings::void_expr;
    auto draw2DImageFromRectToPos(GameBindings::irr::video::ITexture, GameBindings::irr::core::vector2di, GameBindings::irr::core::recti, GameBindings::irr::core::recti, GameBindings::irr::video::SColor, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto setMaterialRendererName(GameBindings::int_expr, GameBindings::char_expr) -> GameBindings::void_expr;
    auto setAmbientLight(GameBindings::irr::video::SColorf) -> GameBindings::void_expr;
    auto setMaterial(GameBindings::irr::video::SMaterial) -> GameBindings::void_expr;
    auto setAllowZWriteOnTransparent(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto removeTexture(GameBindings::irr::video::ITexture) -> GameBindings::void_expr;
    auto getMeshManipulator() -> GameBindings::irr::scene::IMeshManipulator;
    auto removeAllHardwareBuffers() -> GameBindings::void_expr;
    auto queryFeature(MissingType /* C++ irr::video::E_VIDEO_DRIVER_FEATURE (end) */ ) -> GameBindings::bool_expr;
    auto makeColorKeyTextureAtPos(GameBindings::irr::video::ITexture, GameBindings::irr::core::vector2di, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto makeNormalMapTexture(GameBindings::irr::video::ITexture, GameBindings::float_expr) -> GameBindings::void_expr;
    auto getExposedVideoData() -> GameBindings::irr::video::SExposedVideoData;
    auto getTransform(GameBindings::irr::video::E_TRANSFORMATION_STATE) -> GameBindings::irr::core::matrix4;
    auto getTextureCreationFlag(MissingType /* C++ irr::video::E_TEXTURE_CREATION_FLAG (end) */ ) -> GameBindings::bool_expr;
    auto setTransform(GameBindings::irr::video::E_TRANSFORMATION_STATE, GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto getScreenSize() -> GameBindings::irr::core::dimension2du;
    auto getPrimitiveCountDrawn(GameBindings::uint_expr) -> GameBindings::uint_expr;
    auto draw2DImage(GameBindings::irr::video::ITexture, GameBindings::irr::core::vector2di) -> GameBindings::void_expr;
    auto getOverrideMaterial() -> MissingType /* C++ irr::video::SOverrideMaterial& */ ;
    auto getMaximalPrimitiveCount() -> GameBindings::uint_expr;
    auto beginScene(GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::video::SColor, GameBindings::irr::video::SExposedVideoData, GameBindings::irr::core::recti) -> GameBindings::bool_expr;
    auto drawPixel(GameBindings::uint_expr, GameBindings::uint_expr, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto writeImageToFileWithIWriteFile(GameBindings::irr::video::IImage, MissingType /* C++ irr::io::IWriteFile* (end) */ , GameBindings::uint_expr) -> GameBindings::bool_expr;
    auto getMaxTextureSize() -> GameBindings::irr::core::dimension2du;
    auto setTextureCreationFlag(MissingType /* C++ irr::video::E_TEXTURE_CREATION_FLAG (end) */ , GameBindings::bool_expr) -> GameBindings::void_expr;
    auto disableFeature(MissingType /* C++ irr::video::E_VIDEO_DRIVER_FEATURE (end) */ , GameBindings::bool_expr) -> GameBindings::void_expr;
    auto enableMaterial2D(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getMaterialRenderer(GameBindings::uint_expr) -> MissingType /* C++ irr::video::IMaterialRenderer* */ ;
    auto getMaterialRendererName(GameBindings::uint_expr) -> GameBindings::char_expr;
    auto addTextureWithSize(GameBindings::irr::core::dimension2du, GameBindings::irr::core::irrFsStr, MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ ) -> GameBindings::irr::video::ITexture;
    auto getGPUProgrammingServices() -> MissingType /* C++ irr::video::IGPUProgrammingServices* */ ;
    auto getMaterialRendererCount() -> GameBindings::uint_expr;
    auto setClipPlane(GameBindings::uint_expr, GameBindings::irr::core::plane3df, GameBindings::bool_expr) -> GameBindings::bool_expr;
    auto getDriverType() -> GameBindings::irr::video::E_DRIVER_TYPE;
    auto getMaximalDynamicLightAmount() -> GameBindings::uint_expr;
    auto getImageWriter(GameBindings::uint_expr) -> MissingType /* C++ irr::video::IImageWriter* */ ;
    auto getTextureCount() -> GameBindings::uint_expr;
    auto drawIndexedTriangleList(GameBindings::irr::video::S3DVertex, GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto getTextureByIndex(GameBindings::uint_expr) -> GameBindings::irr::video::ITexture;
    auto getImageLoaderCount() -> GameBindings::uint_expr;
    auto getImageLoader(GameBindings::uint_expr) -> MissingType /* C++ irr::video::IImageLoader* */ ;
    auto getFog(GameBindings::irr::video::SColor, MissingType /* C++ irr::video::E_FOG_TYPE& (end) */ , GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto getMaterial2D() -> GameBindings::irr::video::SMaterial;
    auto getDynamicLightCount() -> GameBindings::uint_expr;
    auto getColorFormat() -> MissingType /* C++ irr::video::ECOLOR_FORMAT */ ;
    auto getName() -> GameBindings::wchar_t_expr;
    auto draw2DLine(GameBindings::irr::core::vector2di, GameBindings::irr::core::vector2di, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto fillMaterialStructureFromAttributes(GameBindings::irr::video::SMaterial, GameBindings::irr::io::IAttributes) -> GameBindings::void_expr;
    auto draw2DRectangleOutline(GameBindings::irr::core::recti, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto draw3DTriangle(GameBindings::irr::core::triangle3df, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto checkDriverReset() -> GameBindings::bool_expr;
    auto drawMeshBuffer(GameBindings::irr::scene::IMeshBuffer) -> GameBindings::void_expr;
    auto drawStencilShadow(GameBindings::bool_expr, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto draw3DBox(GameBindings::irr::core::aabbox3df, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto getDynamicLight(GameBindings::uint_expr) -> MissingType /* C++ irr::video::SLight const& */ ;
    auto findTexture(GameBindings::irr::core::irrFsStr) -> GameBindings::irr::video::ITexture;
    auto renameTexture(GameBindings::irr::video::ITexture, GameBindings::irr::core::irrFsStr) -> GameBindings::void_expr;
    auto deleteAllDynamicLights() -> GameBindings::void_expr;
    auto addExternalImageWriter(MissingType /* C++ irr::video::IImageWriter* (end) */ ) -> GameBindings::void_expr;
    auto getImageWriterCount() -> GameBindings::uint_expr;
    auto drawVertexPrimitiveList(GameBindings::void_expr, GameBindings::uint_expr, GameBindings::void_expr, GameBindings::uint_expr, GameBindings::irr::video::E_VERTEX_TYPE, MissingType /* C++ irr::scene::E_PRIMITIVE_TYPE (end) */ , MissingType /* C++ irr::video::E_INDEX_TYPE (end) */ ) -> GameBindings::void_expr;
    auto getViewPort() -> GameBindings::irr::core::recti;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto draw2DVertexPrimitiveList(GameBindings::void_expr, GameBindings::uint_expr, GameBindings::void_expr, GameBindings::uint_expr, GameBindings::irr::video::E_VERTEX_TYPE, MissingType /* C++ irr::scene::E_PRIMITIVE_TYPE (end) */ , MissingType /* C++ irr::video::E_INDEX_TYPE (end) */ ) -> GameBindings::void_expr;
    auto draw2DPolygon(GameBindings::irr::core::vector2di, GameBindings::float_expr, GameBindings::irr::video::SColor, GameBindings::int_expr) -> GameBindings::void_expr;
    auto setFog(GameBindings::irr::video::SColor, MissingType /* C++ irr::video::E_FOG_TYPE (end) */ , GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::bool_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto createAttributesFromMaterial(GameBindings::irr::video::SMaterial, MissingType /* C++ irr::io::SAttributeReadWriteOptions* (end) */ ) -> GameBindings::irr::io::IAttributes;
    auto removeHardwareBuffer(GameBindings::irr::scene::IMeshBuffer) -> GameBindings::void_expr;
    auto getCurrentRenderTargetSize() -> GameBindings::irr::core::dimension2du;
    auto setRenderTargetFromTexture(GameBindings::irr::video::ITexture, GameBindings::bool_expr, GameBindings::bool_expr, GameBindings::irr::video::SColor) -> GameBindings::bool_expr;
    auto clearZBuffer() -> GameBindings::void_expr;
    auto createScreenShot(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */ , MissingType /* C++ irr::video::E_RENDER_TARGET (end) */ ) -> GameBindings::irr::video::IImage;
    auto createImageFromTexture(GameBindings::irr::video::ITexture, GameBindings::irr::core::vector2di, GameBindings::irr::core::dimension2du) -> GameBindings::irr::video::IImage;
    auto draw3DLine(GameBindings::irr::core::vector3df, GameBindings::irr::core::vector3df, GameBindings::irr::video::SColor) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto drawIndexedTriangleListS3DVertex2TCoords(MissingType /* C++ irr::video::S3DVertex2TCoords const* (end) */ , GameBindings::uint_expr, GameBindings::ushort_expr, GameBindings::uint_expr) -> GameBindings::void_expr;
    auto getFPS() -> GameBindings::int_expr;
    auto addMaterialRenderer(MissingType /* C++ irr::video::IMaterialRenderer* (end) */ , GameBindings::char_expr) -> GameBindings::int_expr;
    auto enableClipPlane(GameBindings::uint_expr, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto addDynamicLight(MissingType /* C++ irr::video::SLight const& (end) */ ) -> GameBindings::int_expr;
};struct SMaterialLayer
{
    ::LM::ExprPtr expr;
    auto set_BilinearFilter(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto get_BilinearFilter() -> GameBindings::bool_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SColorf
{
    ::LM::ExprPtr expr;
    auto tmpWithRGBA(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::video::SColorf;
    auto newWithRGBA(GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr, GameBindings::float_expr) -> GameBindings::irr::video::SColorf;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_DRIVER_TYPE
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_DRIVER_TYPE) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_DRIVER_TYPE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SMaterial
{
    ::LM::ExprPtr expr;
    auto getTextureMatrix_c(GameBindings::uint_expr) -> GameBindings::irr::core::matrix4;
    auto get_TextureLayer(GameBindings::uint_expr) -> MissingType /* C++ irr::video::SMaterialLayer [] */ ;
    auto get_ZWriteEnable() -> GameBindings::bool_expr;
    auto set_Wireframe(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_Wireframe() -> GameBindings::bool_expr;
    auto get_PointCloud() -> GameBindings::bool_expr;
    auto get_NormalizeNormals() -> GameBindings::bool_expr;
    auto set_Lighting(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_Lighting() -> GameBindings::bool_expr;
    auto set_GouraudShading(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_GouraudShading() -> GameBindings::bool_expr;
    auto set_NormalizeNormals(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_FrontfaceCulling(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_PointCloud(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto get_FogEnable() -> GameBindings::bool_expr;
    auto tmp() -> GameBindings::irr::video::SMaterial;
    auto tmp(GameBindings::irr::video::SMaterial) -> GameBindings::irr::video::SMaterial;
    auto set_MaterialTypeParam2(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_ColorMaterial() -> GameBindings::uchar_expr;
    auto set_BackfaceCulling(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_Thickness(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_BackfaceCulling() -> GameBindings::bool_expr;
    auto get_FrontfaceCulling() -> GameBindings::bool_expr;
    auto get_ZBuffer() -> GameBindings::uchar_expr;
    auto set_EmissiveColor(GameBindings::irr::video::SColor) -> GameBindings::irr::video::SColor;
    auto set_SpecularColor(GameBindings::irr::video::SColor) -> GameBindings::irr::video::SColor;
    auto set_ZWriteEnable(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_Shininess(GameBindings::float_expr) -> GameBindings::float_expr;
    auto get_ColorMask() -> GameBindings::uchar_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto ref_MaterialType() -> GameBindings::irr::video::E_MATERIAL_TYPE;
    auto get_Shininess() -> GameBindings::float_expr;
    auto getTextureMatrix_nc(GameBindings::uint_expr) -> GameBindings::irr::core::matrix4;
    auto ref_Shininess() -> GameBindings::float_expr;
    auto ref_MaterialTypeParam() -> GameBindings::float_expr;
    auto ref_MaterialTypeParam2() -> GameBindings::float_expr;
    auto get_MaterialTypeParam2() -> GameBindings::float_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
    auto getFlag(GameBindings::irr::video::E_MATERIAL_FLAG) -> GameBindings::bool_expr;
    auto get_AmbientColor() -> GameBindings::irr::video::SColor;
    auto get_SpecularColor() -> GameBindings::irr::video::SColor;
    auto get_MaterialType() -> GameBindings::irr::video::E_MATERIAL_TYPE;
    auto set_MaterialType(GameBindings::irr::video::E_MATERIAL_TYPE) -> GameBindings::irr::video::E_MATERIAL_TYPE;
    auto ref_EmissiveColor() -> GameBindings::irr::video::SColor;
    auto get_EmissiveColor() -> GameBindings::irr::video::SColor;
    auto ref_SpecularColor() -> GameBindings::irr::video::SColor;
    auto get_DiffuseColor() -> GameBindings::irr::video::SColor;
    auto ref_AntiAliasing() -> GameBindings::uchar_expr;
    auto ref_Thickness() -> GameBindings::float_expr;
    auto ref_DiffuseColor() -> GameBindings::irr::video::SColor;
    auto set_DiffuseColor(GameBindings::irr::video::SColor) -> GameBindings::irr::video::SColor;
    auto get_AntiAliasing() -> GameBindings::uchar_expr;
    auto ref_TextureLayer(GameBindings::uint_expr) -> MissingType /* C++ irr::video::SMaterialLayer []& */ ;
    auto set_ColorMask(GameBindings::uchar_expr) -> GameBindings::void_expr;
    auto setTexture(GameBindings::uint_expr, GameBindings::irr::video::ITexture) -> GameBindings::void_expr;
    auto set_AntiAliasing(GameBindings::uchar_expr) -> GameBindings::uchar_expr;
    auto ref_AmbientColor() -> GameBindings::irr::video::SColor;
    auto getTexture(GameBindings::uint_expr) -> GameBindings::irr::video::ITexture;
    auto set_TextureLayer(GameBindings::uint_expr, GameBindings::irr::video::SMaterialLayer) -> GameBindings::void_expr;
    auto set_ZBuffer(GameBindings::uchar_expr) -> GameBindings::uchar_expr;
    auto get_MaterialTypeParam() -> GameBindings::float_expr;
    auto isTransparent() -> GameBindings::bool_expr;
    auto setFlag(GameBindings::irr::video::E_MATERIAL_FLAG, GameBindings::bool_expr) -> GameBindings::void_expr;
    auto set_MaterialTypeParam(GameBindings::float_expr) -> GameBindings::float_expr;
    auto set_ColorMaterial(GameBindings::uchar_expr) -> GameBindings::void_expr;
    auto setTextureMatrix(GameBindings::uint_expr, GameBindings::irr::core::matrix4) -> GameBindings::void_expr;
    auto set_FogEnable(GameBindings::bool_expr) -> GameBindings::void_expr;
    auto lm_new() -> GameBindings::irr::video::SMaterial;
    auto lm_new(GameBindings::irr::video::SMaterial) -> GameBindings::irr::video::SMaterial;
    auto ref_ZBuffer() -> GameBindings::uchar_expr;
    auto get_Thickness() -> GameBindings::float_expr;
    auto set_AmbientColor(GameBindings::irr::video::SColor) -> GameBindings::irr::video::SColor;
};struct E_MATERIAL_FLAG
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_MATERIAL_FLAG) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_MATERIAL_FLAG) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct IImage
{
    ::LM::ExprPtr expr;
    auto getBytesPerPixel() -> GameBindings::uint_expr;
    auto getDimension() -> GameBindings::irr::core::dimension2du;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SExposedVideoData
{
    ::LM::ExprPtr expr;
    auto tmp() -> GameBindings::irr::video::SExposedVideoData;
    auto lm_new() -> GameBindings::irr::video::SExposedVideoData;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct SColor
{
    ::LM::ExprPtr expr;
    auto tmpWithARGB(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::video::SColor;
    auto newWithARGB(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::video::SColor;
    auto tmp(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::video::SColor;
    auto lm_new(GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr, GameBindings::int_expr) -> GameBindings::irr::video::SColor;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_COLOR_MATERIAL
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_COLOR_MATERIAL) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_COLOR_MATERIAL) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_VERTEX_TYPE
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_VERTEX_TYPE) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_VERTEX_TYPE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct E_ANTI_ALIASING_MODE
{
    ::LM::ExprPtr expr;
    auto asString() -> GameBindings::string_expr;
    auto value() -> GameBindings::int_expr;
    auto operator !=(GameBindings::irr::video::E_ANTI_ALIASING_MODE) -> GameBindings::bool_expr;
    auto operator ==(GameBindings::irr::video::E_ANTI_ALIASING_MODE) -> GameBindings::bool_expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};struct vector_of_S3DVertex
{
    ::LM::ExprPtr expr;
    auto lm_delete() -> GameBindings::void_expr;
    auto unsafe_ptr_cast() -> GameBindings::BottomPtr;
};

		}
	}
}
