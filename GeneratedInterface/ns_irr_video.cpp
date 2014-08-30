#include "forward_declares.hpp"
#include "MissingType.hpp"

#include "LikeMagic/Exprs/call_helper.hpp"

#include "ns_irr_io.hpp"
#include "ns_global.hpp"
#include "ns_irr_core.hpp"
#include "ns_irr_scene.hpp"
#include "ns_irr_video.hpp"

namespace GameBindings
{
	namespace irr
	{
		namespace video
		{

auto S3DVertex::tmpWithFloats(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::irr::video::SColor arg6, GameBindings::float_expr arg7, GameBindings::float_expr arg8) -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "tmpWithFloats", args, 9) };
}
auto S3DVertex::newWithFloats(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::float_expr arg5, GameBindings::irr::video::SColor arg6, GameBindings::float_expr arg7, GameBindings::float_expr arg8) -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr, arg8.expr }; 
    return { ::LM::call(expr, "newWithFloats", args, 9) };
}
auto S3DVertex::tmpWithVector3df(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::core::vector2df arg3) -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmpWithVector3df", args, 4) };
}
auto S3DVertex::tmp() -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto S3DVertex::newWithVector3df(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::core::vector2df arg3) -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "newWithVector3df", args, 4) };
}
auto S3DVertex::lm_new() -> GameBindings::irr::video::S3DVertex
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto S3DVertex::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto S3DVertex::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_TRANSFORMATION_STATE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_TRANSFORMATION_STATE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_TRANSFORMATION_STATE::operator !=(GameBindings::irr::video::E_TRANSFORMATION_STATE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_TRANSFORMATION_STATE::operator ==(GameBindings::irr::video::E_TRANSFORMATION_STATE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_TRANSFORMATION_STATE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_TRANSFORMATION_STATE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_MATERIAL_TYPE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_MATERIAL_TYPE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_MATERIAL_TYPE::operator !=(GameBindings::irr::video::E_MATERIAL_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_MATERIAL_TYPE::operator ==(GameBindings::irr::video::E_MATERIAL_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_MATERIAL_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_MATERIAL_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto ITexture::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto ITexture::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IVideoDriver::setRenderTargetFromEnum(MissingType /* C++ irr::video::E_RENDER_TARGET (end) */  arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2, GameBindings::irr::video::SColor arg3) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "setRenderTargetFromEnum", args, 4) };
}
auto IVideoDriver::drawIndexedTriangleListS3DVertex(GameBindings::irr::video::S3DVertex arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleListS3DVertex", args, 4) };
}
auto IVideoDriver::drawIndexedTriangleListS3DVertexTangents(MissingType /* C++ irr::video::S3DVertexTangents const* (end) */  arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleListS3DVertexTangents", args, 4) };
}
auto IVideoDriver::drawIndexedTriangleFanS3DVertex(GameBindings::irr::video::S3DVertex arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleFanS3DVertex", args, 4) };
}
auto IVideoDriver::drawIndexedTriangleFanS3DVertex2TCoords(MissingType /* C++ irr::video::S3DVertex2TCoords const* (end) */  arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleFanS3DVertex2TCoords", args, 4) };
}
auto IVideoDriver::drawIndexedTriangleFanS3DVertexTangents(MissingType /* C++ irr::video::S3DVertexTangents const* (end) */  arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleFanS3DVertexTangents", args, 4) };
}
auto IVideoDriver::draw2DRectangle(GameBindings::irr::video::SColor arg0, GameBindings::irr::core::recti arg1, GameBindings::irr::core::recti arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "draw2DRectangle", args, 3) };
}
auto IVideoDriver::draw2DRectangle(GameBindings::irr::core::recti arg0, GameBindings::irr::video::SColor arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::video::SColor arg3, GameBindings::irr::video::SColor arg4, GameBindings::irr::core::recti arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "draw2DRectangle", args, 6) };
}
auto IVideoDriver::draw2DImageBatch(GameBindings::irr::video::ITexture arg0, MissingType /* C++ irr::core::array<irr::core::vector2d<int>, irr::core::irrAllocator<irr::core::vector2d<int> > > const& (end) */  arg1, MissingType /* C++ irr::core::array<irr::core::rect<int>, irr::core::irrAllocator<irr::core::rect<int> > > const& (end) */  arg2, GameBindings::irr::core::recti arg3, GameBindings::irr::video::SColor arg4, GameBindings::bool_expr arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "draw2DImageBatch", args, 6) };
}
auto IVideoDriver::draw2DImageBatch(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::vector2di arg1, MissingType /* C++ irr::core::array<irr::core::rect<int>, irr::core::irrAllocator<irr::core::rect<int> > > const& (end) */  arg2, MissingType /* C++ irr::core::array<int, irr::core::irrAllocator<int> > const& (end) */  arg3, GameBindings::int_expr arg4, GameBindings::irr::core::recti arg5, GameBindings::irr::video::SColor arg6, GameBindings::bool_expr arg7) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr, arg7.expr }; 
    return { ::LM::call(expr, "draw2DImageBatch", args, 8) };
}
auto IVideoDriver::draw2DImageFromRectToRect(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::recti arg1, GameBindings::irr::core::recti arg2, GameBindings::irr::core::recti arg3, GameBindings::irr::video::SColor arg4, GameBindings::bool_expr arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "draw2DImageFromRectToRect", args, 6) };
}
auto IVideoDriver::addRenderTargetTexture(GameBindings::irr::core::dimension2du arg0, GameBindings::irr::core::irrFsStr arg1, MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg2) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "addRenderTargetTexture", args, 3) };
}
auto IVideoDriver::getVendorInfo() -> GameBindings::irr::core::irrFsStr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getVendorInfo", args, 0) };
}
auto IVideoDriver::writeImageToFileWithPath(GameBindings::irr::video::IImage arg0, GameBindings::irr::core::irrFsStr arg1, GameBindings::uint_expr arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "writeImageToFileWithPath", args, 3) };
}
auto IVideoDriver::createImageFromFileWithPath(GameBindings::irr::core::irrFsStr arg0) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createImageFromFileWithPath", args, 1) };
}
auto IVideoDriver::createImageWithSize(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg0, GameBindings::irr::core::dimension2du arg1) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createImageWithSize", args, 2) };
}
auto IVideoDriver::createImageFromImage(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg0, GameBindings::irr::video::IImage arg1) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createImageFromImage", args, 2) };
}
auto IVideoDriver::createImageFromImage(GameBindings::irr::video::IImage arg0, GameBindings::irr::core::vector2di arg1, GameBindings::irr::core::dimension2du arg2) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "createImageFromImage", args, 3) };
}
auto IVideoDriver::addTexture(GameBindings::irr::core::irrFsStr arg0, GameBindings::irr::video::IImage arg1, GameBindings::void_expr arg2) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "addTexture", args, 3) };
}
auto IVideoDriver::getTexture(GameBindings::irr::core::irrFsStr arg0) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTexture", args, 1) };
}
auto IVideoDriver::getTextureIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */  arg0) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTextureIReadFile", args, 1) };
}
auto IVideoDriver::drawStencilShadowVolume(GameBindings::irr::core::ArrayOfVector3df arg0, GameBindings::bool_expr arg1, GameBindings::uint_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "drawStencilShadowVolume", args, 3) };
}
auto IVideoDriver::makeColorKeyTextureWithColor(GameBindings::irr::video::ITexture arg0, GameBindings::irr::video::SColor arg1, GameBindings::bool_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "makeColorKeyTextureWithColor", args, 3) };
}
auto IVideoDriver::endScene() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "endScene", args, 0) };
}
auto IVideoDriver::createImageFromFileWithIReadFile(MissingType /* C++ irr::io::IReadFile* (end) */  arg0) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "createImageFromFileWithIReadFile", args, 1) };
}
auto IVideoDriver::removeAllTextures() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "removeAllTextures", args, 0) };
}
auto IVideoDriver::turnLightOn(GameBindings::int_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "turnLightOn", args, 2) };
}
auto IVideoDriver::setRenderTargetFromArray(MissingType /* C++ irr::core::array<irr::video::IRenderTarget, irr::core::irrAllocator<irr::video::IRenderTarget> > const& (end) */  arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2, GameBindings::irr::video::SColor arg3) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "setRenderTargetFromArray", args, 4) };
}
auto IVideoDriver::addExternalImageLoader(MissingType /* C++ irr::video::IImageLoader* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addExternalImageLoader", args, 1) };
}
auto IVideoDriver::createImageFromData(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg0, GameBindings::irr::core::dimension2du arg1, GameBindings::void_expr arg2, GameBindings::bool_expr arg3, GameBindings::bool_expr arg4) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "createImageFromData", args, 5) };
}
auto IVideoDriver::setViewPort(GameBindings::irr::core::recti arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setViewPort", args, 1) };
}
auto IVideoDriver::setMinHardwareBufferVertexCount(GameBindings::uint_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMinHardwareBufferVertexCount", args, 1) };
}
auto IVideoDriver::draw2DImageFromRectToPos(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::vector2di arg1, GameBindings::irr::core::recti arg2, GameBindings::irr::core::recti arg3, GameBindings::irr::video::SColor arg4, GameBindings::bool_expr arg5) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr }; 
    return { ::LM::call(expr, "draw2DImageFromRectToPos", args, 6) };
}
auto IVideoDriver::setMaterialRendererName(GameBindings::int_expr arg0, GameBindings::char_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setMaterialRendererName", args, 2) };
}
auto IVideoDriver::setAmbientLight(GameBindings::irr::video::SColorf arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAmbientLight", args, 1) };
}
auto IVideoDriver::setMaterial(GameBindings::irr::video::SMaterial arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setMaterial", args, 1) };
}
auto IVideoDriver::setAllowZWriteOnTransparent(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "setAllowZWriteOnTransparent", args, 1) };
}
auto IVideoDriver::removeTexture(GameBindings::irr::video::ITexture arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeTexture", args, 1) };
}
auto IVideoDriver::getMeshManipulator() -> GameBindings::irr::scene::IMeshManipulator
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMeshManipulator", args, 0) };
}
auto IVideoDriver::removeAllHardwareBuffers() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "removeAllHardwareBuffers", args, 0) };
}
auto IVideoDriver::queryFeature(MissingType /* C++ irr::video::E_VIDEO_DRIVER_FEATURE (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "queryFeature", args, 1) };
}
auto IVideoDriver::makeColorKeyTextureAtPos(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::vector2di arg1, GameBindings::bool_expr arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "makeColorKeyTextureAtPos", args, 3) };
}
auto IVideoDriver::makeNormalMapTexture(GameBindings::irr::video::ITexture arg0, GameBindings::float_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "makeNormalMapTexture", args, 2) };
}
auto IVideoDriver::getExposedVideoData() -> GameBindings::irr::video::SExposedVideoData
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getExposedVideoData", args, 0) };
}
auto IVideoDriver::getTransform(GameBindings::irr::video::E_TRANSFORMATION_STATE arg0) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTransform", args, 1) };
}
auto IVideoDriver::getTextureCreationFlag(MissingType /* C++ irr::video::E_TEXTURE_CREATION_FLAG (end) */  arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTextureCreationFlag", args, 1) };
}
auto IVideoDriver::setTransform(GameBindings::irr::video::E_TRANSFORMATION_STATE arg0, GameBindings::irr::core::matrix4 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setTransform", args, 2) };
}
auto IVideoDriver::getScreenSize() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getScreenSize", args, 0) };
}
auto IVideoDriver::getPrimitiveCountDrawn(GameBindings::uint_expr arg0) -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getPrimitiveCountDrawn", args, 1) };
}
auto IVideoDriver::draw2DImage(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::vector2di arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "draw2DImage", args, 2) };
}
auto IVideoDriver::getOverrideMaterial() -> MissingType /* C++ irr::video::SOverrideMaterial& */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getOverrideMaterial", args, 0) };
}
auto IVideoDriver::getMaximalPrimitiveCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaximalPrimitiveCount", args, 0) };
}
auto IVideoDriver::beginScene(GameBindings::bool_expr arg0, GameBindings::bool_expr arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::video::SExposedVideoData arg3, GameBindings::irr::core::recti arg4) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "beginScene", args, 5) };
}
auto IVideoDriver::drawPixel(GameBindings::uint_expr arg0, GameBindings::uint_expr arg1, GameBindings::irr::video::SColor arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "drawPixel", args, 3) };
}
auto IVideoDriver::writeImageToFileWithIWriteFile(GameBindings::irr::video::IImage arg0, MissingType /* C++ irr::io::IWriteFile* (end) */  arg1, GameBindings::uint_expr arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "writeImageToFileWithIWriteFile", args, 3) };
}
auto IVideoDriver::getMaxTextureSize() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaxTextureSize", args, 0) };
}
auto IVideoDriver::setTextureCreationFlag(MissingType /* C++ irr::video::E_TEXTURE_CREATION_FLAG (end) */  arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setTextureCreationFlag", args, 2) };
}
auto IVideoDriver::disableFeature(MissingType /* C++ irr::video::E_VIDEO_DRIVER_FEATURE (end) */  arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "disableFeature", args, 2) };
}
auto IVideoDriver::enableMaterial2D(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "enableMaterial2D", args, 1) };
}
auto IVideoDriver::getMaterialRenderer(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::IMaterialRenderer* */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMaterialRenderer", args, 1) };
}
auto IVideoDriver::getMaterialRendererName(GameBindings::uint_expr arg0) -> GameBindings::char_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getMaterialRendererName", args, 1) };
}
auto IVideoDriver::addTextureWithSize(GameBindings::irr::core::dimension2du arg0, GameBindings::irr::core::irrFsStr arg1, MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg2) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "addTextureWithSize", args, 3) };
}
auto IVideoDriver::getGPUProgrammingServices() -> MissingType /* C++ irr::video::IGPUProgrammingServices* */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getGPUProgrammingServices", args, 0) };
}
auto IVideoDriver::getMaterialRendererCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaterialRendererCount", args, 0) };
}
auto IVideoDriver::setClipPlane(GameBindings::uint_expr arg0, GameBindings::irr::core::plane3df arg1, GameBindings::bool_expr arg2) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "setClipPlane", args, 3) };
}
auto IVideoDriver::getDriverType() -> GameBindings::irr::video::E_DRIVER_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDriverType", args, 0) };
}
auto IVideoDriver::getMaximalDynamicLightAmount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaximalDynamicLightAmount", args, 0) };
}
auto IVideoDriver::getImageWriter(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::IImageWriter* */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getImageWriter", args, 1) };
}
auto IVideoDriver::getTextureCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getTextureCount", args, 0) };
}
auto IVideoDriver::drawIndexedTriangleList(GameBindings::irr::video::S3DVertex arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleList", args, 4) };
}
auto IVideoDriver::getTextureByIndex(GameBindings::uint_expr arg0) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTextureByIndex", args, 1) };
}
auto IVideoDriver::getImageLoaderCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getImageLoaderCount", args, 0) };
}
auto IVideoDriver::getImageLoader(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::IImageLoader* */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getImageLoader", args, 1) };
}
auto IVideoDriver::getFog(GameBindings::irr::video::SColor arg0, MissingType /* C++ irr::video::E_FOG_TYPE& (end) */  arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::bool_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "getFog", args, 7) };
}
auto IVideoDriver::getMaterial2D() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getMaterial2D", args, 0) };
}
auto IVideoDriver::getDynamicLightCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDynamicLightCount", args, 0) };
}
auto IVideoDriver::getColorFormat() -> MissingType /* C++ irr::video::ECOLOR_FORMAT */ 
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getColorFormat", args, 0) };
}
auto IVideoDriver::getName() -> GameBindings::wchar_t_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getName", args, 0) };
}
auto IVideoDriver::draw2DLine(GameBindings::irr::core::vector2di arg0, GameBindings::irr::core::vector2di arg1, GameBindings::irr::video::SColor arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "draw2DLine", args, 3) };
}
auto IVideoDriver::fillMaterialStructureFromAttributes(GameBindings::irr::video::SMaterial arg0, GameBindings::irr::io::IAttributes arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "fillMaterialStructureFromAttributes", args, 2) };
}
auto IVideoDriver::draw2DRectangleOutline(GameBindings::irr::core::recti arg0, GameBindings::irr::video::SColor arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "draw2DRectangleOutline", args, 2) };
}
auto IVideoDriver::draw3DTriangle(GameBindings::irr::core::triangle3df arg0, GameBindings::irr::video::SColor arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "draw3DTriangle", args, 2) };
}
auto IVideoDriver::checkDriverReset() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "checkDriverReset", args, 0) };
}
auto IVideoDriver::drawMeshBuffer(GameBindings::irr::scene::IMeshBuffer arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "drawMeshBuffer", args, 1) };
}
auto IVideoDriver::drawStencilShadow(GameBindings::bool_expr arg0, GameBindings::irr::video::SColor arg1, GameBindings::irr::video::SColor arg2, GameBindings::irr::video::SColor arg3, GameBindings::irr::video::SColor arg4) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr }; 
    return { ::LM::call(expr, "drawStencilShadow", args, 5) };
}
auto IVideoDriver::draw3DBox(GameBindings::irr::core::aabbox3df arg0, GameBindings::irr::video::SColor arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "draw3DBox", args, 2) };
}
auto IVideoDriver::getDynamicLight(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::SLight const& */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getDynamicLight", args, 1) };
}
auto IVideoDriver::findTexture(GameBindings::irr::core::irrFsStr arg0) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "findTexture", args, 1) };
}
auto IVideoDriver::renameTexture(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::irrFsStr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "renameTexture", args, 2) };
}
auto IVideoDriver::deleteAllDynamicLights() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "deleteAllDynamicLights", args, 0) };
}
auto IVideoDriver::addExternalImageWriter(MissingType /* C++ irr::video::IImageWriter* (end) */  arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addExternalImageWriter", args, 1) };
}
auto IVideoDriver::getImageWriterCount() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getImageWriterCount", args, 0) };
}
auto IVideoDriver::drawVertexPrimitiveList(GameBindings::void_expr arg0, GameBindings::uint_expr arg1, GameBindings::void_expr arg2, GameBindings::uint_expr arg3, GameBindings::irr::video::E_VERTEX_TYPE arg4, MissingType /* C++ irr::scene::E_PRIMITIVE_TYPE (end) */  arg5, MissingType /* C++ irr::video::E_INDEX_TYPE (end) */  arg6) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "drawVertexPrimitiveList", args, 7) };
}
auto IVideoDriver::getViewPort() -> GameBindings::irr::core::recti
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getViewPort", args, 0) };
}
auto IVideoDriver::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto IVideoDriver::draw2DVertexPrimitiveList(GameBindings::void_expr arg0, GameBindings::uint_expr arg1, GameBindings::void_expr arg2, GameBindings::uint_expr arg3, GameBindings::irr::video::E_VERTEX_TYPE arg4, MissingType /* C++ irr::scene::E_PRIMITIVE_TYPE (end) */  arg5, MissingType /* C++ irr::video::E_INDEX_TYPE (end) */  arg6) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "draw2DVertexPrimitiveList", args, 7) };
}
auto IVideoDriver::draw2DPolygon(GameBindings::irr::core::vector2di arg0, GameBindings::float_expr arg1, GameBindings::irr::video::SColor arg2, GameBindings::int_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "draw2DPolygon", args, 4) };
}
auto IVideoDriver::setFog(GameBindings::irr::video::SColor arg0, MissingType /* C++ irr::video::E_FOG_TYPE (end) */  arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3, GameBindings::float_expr arg4, GameBindings::bool_expr arg5, GameBindings::bool_expr arg6) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr, arg4.expr, arg5.expr, arg6.expr }; 
    return { ::LM::call(expr, "setFog", args, 7) };
}
auto IVideoDriver::createAttributesFromMaterial(GameBindings::irr::video::SMaterial arg0, MissingType /* C++ irr::io::SAttributeReadWriteOptions* (end) */  arg1) -> GameBindings::irr::io::IAttributes
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createAttributesFromMaterial", args, 2) };
}
auto IVideoDriver::removeHardwareBuffer(GameBindings::irr::scene::IMeshBuffer arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "removeHardwareBuffer", args, 1) };
}
auto IVideoDriver::getCurrentRenderTargetSize() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getCurrentRenderTargetSize", args, 0) };
}
auto IVideoDriver::setRenderTargetFromTexture(GameBindings::irr::video::ITexture arg0, GameBindings::bool_expr arg1, GameBindings::bool_expr arg2, GameBindings::irr::video::SColor arg3) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "setRenderTargetFromTexture", args, 4) };
}
auto IVideoDriver::clearZBuffer() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "clearZBuffer", args, 0) };
}
auto IVideoDriver::createScreenShot(MissingType /* C++ irr::video::ECOLOR_FORMAT (end) */  arg0, MissingType /* C++ irr::video::E_RENDER_TARGET (end) */  arg1) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "createScreenShot", args, 2) };
}
auto IVideoDriver::createImageFromTexture(GameBindings::irr::video::ITexture arg0, GameBindings::irr::core::vector2di arg1, GameBindings::irr::core::dimension2du arg2) -> GameBindings::irr::video::IImage
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "createImageFromTexture", args, 3) };
}
auto IVideoDriver::draw3DLine(GameBindings::irr::core::vector3df arg0, GameBindings::irr::core::vector3df arg1, GameBindings::irr::video::SColor arg2) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr }; 
    return { ::LM::call(expr, "draw3DLine", args, 3) };
}
auto IVideoDriver::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IVideoDriver::drawIndexedTriangleListS3DVertex2TCoords(MissingType /* C++ irr::video::S3DVertex2TCoords const* (end) */  arg0, GameBindings::uint_expr arg1, GameBindings::ushort_expr arg2, GameBindings::uint_expr arg3) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "drawIndexedTriangleListS3DVertex2TCoords", args, 4) };
}
auto IVideoDriver::getFPS() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getFPS", args, 0) };
}
auto IVideoDriver::addMaterialRenderer(MissingType /* C++ irr::video::IMaterialRenderer* (end) */  arg0, GameBindings::char_expr arg1) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "addMaterialRenderer", args, 2) };
}
auto IVideoDriver::enableClipPlane(GameBindings::uint_expr arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "enableClipPlane", args, 2) };
}
auto IVideoDriver::addDynamicLight(MissingType /* C++ irr::video::SLight const& (end) */  arg0) -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "addDynamicLight", args, 1) };
}

auto SMaterialLayer::set_BilinearFilter(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_BilinearFilter", args, 1) };
}
auto SMaterialLayer::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SMaterialLayer::get_BilinearFilter() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_BilinearFilter", args, 0) };
}
auto SMaterialLayer::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SColorf::tmpWithRGBA(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::video::SColorf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmpWithRGBA", args, 4) };
}
auto SColorf::newWithRGBA(GameBindings::float_expr arg0, GameBindings::float_expr arg1, GameBindings::float_expr arg2, GameBindings::float_expr arg3) -> GameBindings::irr::video::SColorf
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "newWithRGBA", args, 4) };
}
auto SColorf::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SColorf::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_DRIVER_TYPE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_DRIVER_TYPE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_DRIVER_TYPE::operator !=(GameBindings::irr::video::E_DRIVER_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_DRIVER_TYPE::operator ==(GameBindings::irr::video::E_DRIVER_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_DRIVER_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_DRIVER_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SMaterial::getTextureMatrix_c(GameBindings::uint_expr arg0) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTextureMatrix_c", args, 1) };
}
auto SMaterial::get_TextureLayer(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::SMaterialLayer [] */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "get_TextureLayer", args, 1) };
}
auto SMaterial::get_ZWriteEnable() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ZWriteEnable", args, 0) };
}
auto SMaterial::set_Wireframe(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Wireframe", args, 1) };
}
auto SMaterial::get_Wireframe() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Wireframe", args, 0) };
}
auto SMaterial::get_PointCloud() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_PointCloud", args, 0) };
}
auto SMaterial::get_NormalizeNormals() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_NormalizeNormals", args, 0) };
}
auto SMaterial::set_Lighting(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Lighting", args, 1) };
}
auto SMaterial::get_Lighting() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Lighting", args, 0) };
}
auto SMaterial::set_GouraudShading(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_GouraudShading", args, 1) };
}
auto SMaterial::get_GouraudShading() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_GouraudShading", args, 0) };
}
auto SMaterial::set_NormalizeNormals(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_NormalizeNormals", args, 1) };
}
auto SMaterial::set_FrontfaceCulling(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_FrontfaceCulling", args, 1) };
}
auto SMaterial::set_PointCloud(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_PointCloud", args, 1) };
}
auto SMaterial::get_FogEnable() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_FogEnable", args, 0) };
}
auto SMaterial::tmp() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto SMaterial::tmp(GameBindings::irr::video::SMaterial arg0) -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "tmp", args, 1) };
}
auto SMaterial::set_MaterialTypeParam2(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MaterialTypeParam2", args, 1) };
}
auto SMaterial::get_ColorMaterial() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ColorMaterial", args, 0) };
}
auto SMaterial::set_BackfaceCulling(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_BackfaceCulling", args, 1) };
}
auto SMaterial::set_Thickness(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Thickness", args, 1) };
}
auto SMaterial::get_BackfaceCulling() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_BackfaceCulling", args, 0) };
}
auto SMaterial::get_FrontfaceCulling() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_FrontfaceCulling", args, 0) };
}
auto SMaterial::get_ZBuffer() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ZBuffer", args, 0) };
}
auto SMaterial::set_EmissiveColor(GameBindings::irr::video::SColor arg0) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_EmissiveColor", args, 1) };
}
auto SMaterial::set_SpecularColor(GameBindings::irr::video::SColor arg0) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_SpecularColor", args, 1) };
}
auto SMaterial::set_ZWriteEnable(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ZWriteEnable", args, 1) };
}
auto SMaterial::set_Shininess(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_Shininess", args, 1) };
}
auto SMaterial::get_ColorMask() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_ColorMask", args, 0) };
}
auto SMaterial::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SMaterial::ref_MaterialType() -> GameBindings::irr::video::E_MATERIAL_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MaterialType", args, 0) };
}
auto SMaterial::get_Shininess() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Shininess", args, 0) };
}
auto SMaterial::getTextureMatrix_nc(GameBindings::uint_expr arg0) -> GameBindings::irr::core::matrix4
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTextureMatrix_nc", args, 1) };
}
auto SMaterial::ref_Shininess() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Shininess", args, 0) };
}
auto SMaterial::ref_MaterialTypeParam() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MaterialTypeParam", args, 0) };
}
auto SMaterial::ref_MaterialTypeParam2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_MaterialTypeParam2", args, 0) };
}
auto SMaterial::get_MaterialTypeParam2() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MaterialTypeParam2", args, 0) };
}
auto SMaterial::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}
auto SMaterial::getFlag(GameBindings::irr::video::E_MATERIAL_FLAG arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getFlag", args, 1) };
}
auto SMaterial::get_AmbientColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_AmbientColor", args, 0) };
}
auto SMaterial::get_SpecularColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_SpecularColor", args, 0) };
}
auto SMaterial::get_MaterialType() -> GameBindings::irr::video::E_MATERIAL_TYPE
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MaterialType", args, 0) };
}
auto SMaterial::set_MaterialType(GameBindings::irr::video::E_MATERIAL_TYPE arg0) -> GameBindings::irr::video::E_MATERIAL_TYPE
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MaterialType", args, 1) };
}
auto SMaterial::ref_EmissiveColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_EmissiveColor", args, 0) };
}
auto SMaterial::get_EmissiveColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_EmissiveColor", args, 0) };
}
auto SMaterial::ref_SpecularColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_SpecularColor", args, 0) };
}
auto SMaterial::get_DiffuseColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_DiffuseColor", args, 0) };
}
auto SMaterial::ref_AntiAliasing() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_AntiAliasing", args, 0) };
}
auto SMaterial::ref_Thickness() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_Thickness", args, 0) };
}
auto SMaterial::ref_DiffuseColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_DiffuseColor", args, 0) };
}
auto SMaterial::set_DiffuseColor(GameBindings::irr::video::SColor arg0) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_DiffuseColor", args, 1) };
}
auto SMaterial::get_AntiAliasing() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_AntiAliasing", args, 0) };
}
auto SMaterial::ref_TextureLayer(GameBindings::uint_expr arg0) -> MissingType /* C++ irr::video::SMaterialLayer []& */ 
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "ref_TextureLayer", args, 1) };
}
auto SMaterial::set_ColorMask(GameBindings::uchar_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ColorMask", args, 1) };
}
auto SMaterial::setTexture(GameBindings::uint_expr arg0, GameBindings::irr::video::ITexture arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setTexture", args, 2) };
}
auto SMaterial::set_AntiAliasing(GameBindings::uchar_expr arg0) -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_AntiAliasing", args, 1) };
}
auto SMaterial::ref_AmbientColor() -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_AmbientColor", args, 0) };
}
auto SMaterial::getTexture(GameBindings::uint_expr arg0) -> GameBindings::irr::video::ITexture
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "getTexture", args, 1) };
}
auto SMaterial::set_TextureLayer(GameBindings::uint_expr arg0, GameBindings::irr::video::SMaterialLayer arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "set_TextureLayer", args, 2) };
}
auto SMaterial::set_ZBuffer(GameBindings::uchar_expr arg0) -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ZBuffer", args, 1) };
}
auto SMaterial::get_MaterialTypeParam() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_MaterialTypeParam", args, 0) };
}
auto SMaterial::isTransparent() -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "isTransparent", args, 0) };
}
auto SMaterial::setFlag(GameBindings::irr::video::E_MATERIAL_FLAG arg0, GameBindings::bool_expr arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setFlag", args, 2) };
}
auto SMaterial::set_MaterialTypeParam(GameBindings::float_expr arg0) -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_MaterialTypeParam", args, 1) };
}
auto SMaterial::set_ColorMaterial(GameBindings::uchar_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_ColorMaterial", args, 1) };
}
auto SMaterial::setTextureMatrix(GameBindings::uint_expr arg0, GameBindings::irr::core::matrix4 arg1) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr }; 
    return { ::LM::call(expr, "setTextureMatrix", args, 2) };
}
auto SMaterial::set_FogEnable(GameBindings::bool_expr arg0) -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_FogEnable", args, 1) };
}
auto SMaterial::lm_new() -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto SMaterial::lm_new(GameBindings::irr::video::SMaterial arg0) -> GameBindings::irr::video::SMaterial
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "new", args, 1) };
}
auto SMaterial::ref_ZBuffer() -> GameBindings::uchar_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "ref_ZBuffer", args, 0) };
}
auto SMaterial::get_Thickness() -> GameBindings::float_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "get_Thickness", args, 0) };
}
auto SMaterial::set_AmbientColor(GameBindings::irr::video::SColor arg0) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "set_AmbientColor", args, 1) };
}

auto E_MATERIAL_FLAG::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_MATERIAL_FLAG::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_MATERIAL_FLAG::operator !=(GameBindings::irr::video::E_MATERIAL_FLAG arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_MATERIAL_FLAG::operator ==(GameBindings::irr::video::E_MATERIAL_FLAG arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_MATERIAL_FLAG::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_MATERIAL_FLAG::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto IImage::getBytesPerPixel() -> GameBindings::uint_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getBytesPerPixel", args, 0) };
}
auto IImage::getDimension() -> GameBindings::irr::core::dimension2du
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "getDimension", args, 0) };
}
auto IImage::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto IImage::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SExposedVideoData::tmp() -> GameBindings::irr::video::SExposedVideoData
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "tmp", args, 0) };
}
auto SExposedVideoData::lm_new() -> GameBindings::irr::video::SExposedVideoData
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "new", args, 0) };
}
auto SExposedVideoData::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SExposedVideoData::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto SColor::tmpWithARGB(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmpWithARGB", args, 4) };
}
auto SColor::newWithARGB(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "newWithARGB", args, 4) };
}
auto SColor::tmp(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "tmp", args, 4) };
}
auto SColor::lm_new(GameBindings::int_expr arg0, GameBindings::int_expr arg1, GameBindings::int_expr arg2, GameBindings::int_expr arg3) -> GameBindings::irr::video::SColor
{
    ::LM::ExprPtr args[] = { arg0.expr, arg1.expr, arg2.expr, arg3.expr }; 
    return { ::LM::call(expr, "new", args, 4) };
}
auto SColor::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto SColor::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_COLOR_MATERIAL::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_COLOR_MATERIAL::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_COLOR_MATERIAL::operator !=(GameBindings::irr::video::E_COLOR_MATERIAL arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_COLOR_MATERIAL::operator ==(GameBindings::irr::video::E_COLOR_MATERIAL arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_COLOR_MATERIAL::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_COLOR_MATERIAL::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_VERTEX_TYPE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_VERTEX_TYPE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_VERTEX_TYPE::operator !=(GameBindings::irr::video::E_VERTEX_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_VERTEX_TYPE::operator ==(GameBindings::irr::video::E_VERTEX_TYPE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_VERTEX_TYPE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_VERTEX_TYPE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto E_ANTI_ALIASING_MODE::asString() -> GameBindings::string_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "asString", args, 0) };
}
auto E_ANTI_ALIASING_MODE::value() -> GameBindings::int_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "value", args, 0) };
}
auto E_ANTI_ALIASING_MODE::operator !=(GameBindings::irr::video::E_ANTI_ALIASING_MODE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "!=", args, 1) };
}
auto E_ANTI_ALIASING_MODE::operator ==(GameBindings::irr::video::E_ANTI_ALIASING_MODE arg0) -> GameBindings::bool_expr
{
    ::LM::ExprPtr args[] = { arg0.expr }; 
    return { ::LM::call(expr, "==", args, 1) };
}
auto E_ANTI_ALIASING_MODE::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto E_ANTI_ALIASING_MODE::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

auto vector_of_S3DVertex::lm_delete() -> GameBindings::void_expr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "delete", args, 0) };
}
auto vector_of_S3DVertex::unsafe_ptr_cast() -> GameBindings::BottomPtr
{
    ::LM::ExprPtr args[] = {  }; 
    return { ::LM::call(expr, "unsafe_ptr_cast", args, 0) };
}

		}
	}
}
