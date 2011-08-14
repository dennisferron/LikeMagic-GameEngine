// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Irrlicht/ScriptedSceneNode.hpp"

#include <irrlicht.h>

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace irr::video;

using irr::core::vector3df;
using irr::core::vector2df;



namespace Bindings { namespace Irrlicht {

void add_bindings_video(RuntimeTypeSystem& type_sys)
{
    auto ns_irr_video = Namespace::global(type_sys).subspace("irr").subspace("video");

    // enums
    LM_ENUM(ns_irr_video, E_DRIVER_TYPE)
    LM_ENUM(ns_irr_video, E_MATERIAL_FLAG)
    LM_ENUM(ns_irr_video, E_TRANSFORMATION_STATE)
    LM_ENUM(ns_irr_video, E_ANTI_ALIASING_MODE)
    LM_ENUM(ns_irr_video, E_MATERIAL_TYPE)
    LM_ENUM(ns_irr_video, E_VERTEX_TYPE)
    LM_ENUM(ns_irr_video, E_COLOR_MATERIAL)

    LM_CLASS(ns_irr_video, S3DVertex)
    LM_CONSTR(S3DVertex,,)
    LM_CONSTR(S3DVertex, "newWithFloats", f32,f32,f32,  f32,f32,f32,  SColor,  f32,f32)
    LM_CONSTR(S3DVertex, "newWithVector3df", vector3df, vector3df, SColor, vector2df)

    typedef std::vector<S3DVertex> vector_of_S3DVertex;
    LM_CLASS(ns_irr_video, vector_of_S3DVertex)

    LM_CLASS(ns_irr_video, SColor)
    LM_CONSTR(SColor,, int,int,int,int)
    LM_CONSTR(SColor, "newWithARGB", int,int,int,int)

    LM_CLASS(ns_irr_video, SColorf)
    LM_CONSTR(SColorf, "newWithRGBA", f32,f32,f32,f32)

    LM_CLASS(ns_irr_video, SExposedVideoData)
    LM_CONSTR(SExposedVideoData,,)

    LM_CLASS(ns_irr_video, SMaterial)
    LM_FUNC(SMaterial, (setFlag)(getFlag)(getTexture)(setTexture)(setTextureMatrix)(isTransparent))
    LM_FIELD(SMaterial, (AntiAliasing)(AmbientColor)(DiffuseColor)(EmissiveColor)(MaterialType)(MaterialTypeParam)(MaterialTypeParam2)(Shininess)(SpecularColor)(Thickness)(ZBuffer))
    LM_BIT_FIELD(SMaterial, BackfaceCulling)
    LM_BIT_FIELD(SMaterial, ColorMask)
    LM_BIT_FIELD(SMaterial, ColorMaterial)
    LM_BIT_FIELD(SMaterial, FogEnable)
    LM_BIT_FIELD(SMaterial, FrontfaceCulling)
    LM_BIT_FIELD(SMaterial, GouraudShading)
    LM_BIT_FIELD(SMaterial, Lighting)
    LM_BIT_FIELD(SMaterial, NormalizeNormals)
    LM_BIT_FIELD(SMaterial, PointCloud)
    LM_BIT_FIELD(SMaterial, Wireframe)
    LM_BIT_FIELD(SMaterial, ZWriteEnable)

    LM_ARRAY_FIELD(SMaterial, (TextureLayer))
    LM_FUNC_OVERLOAD_BOTH(SMaterial, getTextureMatrix, core::matrix4&, u32)

    LM_CLASS(ns_irr_video, SMaterialLayer)

    // "error:  invalid pointer to bit-field 'irr::video::SMaterialLayer::BilinearFilter"
    //LM_FIELD(SMaterialLayer, (BilinearFilter))
    LM_BIT_FIELD(SMaterialLayer, BilinearFilter)

    LM_CLASS(ns_irr_video, IVideoDriver)
    LM_FUNC(IVideoDriver,
            (addDynamicLight)(addExternalImageLoader)(addExternalImageWriter)(addMaterialRenderer)(addRenderTargetTexture)
            (beginScene)(checkDriverReset)(clearZBuffer)(createAttributesFromMaterial)(createScreenShot)(deleteAllDynamicLights)
            (disableFeature)(draw2DLine)(draw2DPolygon)(draw2DRectangleOutline)(draw2DVertexPrimitiveList)(draw3DBox)(draw3DLine)
            (draw3DTriangle)(drawMeshBuffer)(drawPixel)(drawStencilShadow)(drawStencilShadowVolume)(drawVertexPrimitiveList)
            (enableClipPlane)(enableMaterial2D)(endScene)(fillMaterialStructureFromAttributes)(findTexture)(getColorFormat)(getCurrentRenderTargetSize)
            (getDriverType)(getDynamicLight)(getDynamicLightCount)(getExposedVideoData)(getFog)(getFPS)(getGPUProgrammingServices)(getImageLoader)
            (getImageLoaderCount)(getImageWriter)(getImageWriterCount)(getMaterial2D)(getMaterialRenderer)(getMaterialRendererCount)(getMaterialRendererName)
            (getMaximalDynamicLightAmount)(getMaximalPrimitiveCount)(getMaxTextureSize)(getMeshManipulator)(getName)(getOverrideMaterial)(getPrimitiveCountDrawn)
            (getScreenSize)(getTextureByIndex)(getTextureCount)(getTextureCreationFlag)(getTransform)(getVendorInfo)(getViewPort)(makeNormalMapTexture)
            (queryFeature)(removeAllHardwareBuffers)(removeAllTextures)(removeHardwareBuffer)(removeTexture)(renameTexture)(setAllowZWriteOnTransparent)
            (setAmbientLight)(setClipPlane)(setFog)(setMaterial)(setMaterialRendererName)(setMinHardwareBufferVertexCount)(setTextureCreationFlag)
            (setTransform)(setViewPort)(turnLightOn)
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleList", drawIndexedTriangleList, void, const S3DVertex*, u32, const u16*, u32)
    LM_FUNC_OVERLOAD_CONST(IVideoDriver, "makeColorKeyTextureAtPos", makeColorKeyTexture, void, video::ITexture*, irr::core::vector2d<s32>, bool)
    LM_FUNC_OVERLOAD_CONST(IVideoDriver, "makeColorKeyTextureWithColor", makeColorKeyTexture, void, video::ITexture*, video::SColor, bool)
    LM_FUNC_OVERLOAD(IVideoDriver, "getTextureIReadFile", getTexture, ITexture*, io::IReadFile *)
    LM_FUNC_OVERLOAD(IVideoDriver, "getTexture", getTexture, ITexture*, const io::path&)
    LM_FUNC_OVERLOAD(IVideoDriver, "addTexture", addTexture, ITexture*, const io::path&, IImage*, void*)
    LM_FUNC_OVERLOAD(IVideoDriver, "addTextureWithSize", addTexture, ITexture*, const core::dimension2d<u32> &, const io::path&, ECOLOR_FORMAT)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromTexture", createImage, IImage*, ITexture*, const core::position2d<s32>&, const core::dimension2d<u32>&)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromImage", createImage, IImage*, IImage*, const core::position2d<s32>&, const core::dimension2d<u32>&)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromImage", createImage, IImage*, ECOLOR_FORMAT, IImage*)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageWithSize", createImage, IImage*, ECOLOR_FORMAT, const core::dimension2d<u32>&)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromData", createImageFromData, IImage*, ECOLOR_FORMAT, const core::dimension2d<u32>&, void*, bool, bool)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromFileIReadFile", createImageFromFile, IImage*, io::IReadFile*)
    LM_FUNC_OVERLOAD(IVideoDriver, "createImageFromFile", createImageFromFile, IImage*, const io::path&)
    LM_FUNC_OVERLOAD(IVideoDriver, "writeImageToFile", writeImageToFile, bool, IImage*, const io::path&, u32)
    LM_FUNC_OVERLOAD(IVideoDriver, "writeImageToFileIWriteFile", writeImageToFile, bool, IImage*, io::IWriteFile*, u32)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DImage", draw2DImage,
            void,
            const video::ITexture*,
            const core::position2d<s32>& d)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DImageFromRectToPos", draw2DImage,
            void,
            const video::ITexture*,
            const core::position2d<s32>& d,
            const core::rect<s32>&,
            const core::rect<s32>*,
            SColor,
            bool)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DImageFromRectToRect", draw2DImage,
            void,
            const video::ITexture*,
            const core::rect<s32>&,
            const core::rect<s32>&,
            const core::rect<s32>*,
            const SColor*,
            bool)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DImageBatch", draw2DImageBatch,
            void,
            const video::ITexture*,
            const core::array<core::position2d<s32>>& d,
            const core::array<core::rect<s32>>&,
            const core::rect<s32>*,
            SColor,
            bool)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DImageBatch", draw2DImageBatch,
            void,
            const video::ITexture*,
            const core::position2d<s32>&,
            const core::array<core::rect<s32>>&,
            const core::array<s32>&,
            s32,
            const core::rect<s32>*,
            SColor,
            bool)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DRectangle", draw2DRectangle,
            void,
            const core::rect<s32>&,
            SColor,
            SColor,
            SColor,
            SColor,
            const core::rect<s32>*)

    LM_FUNC_OVERLOAD(IVideoDriver, "draw2DRectangle", draw2DRectangle,
            void,
            SColor,
            const core::rect<s32>&,
            const core::rect<s32>*)

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleFanS3DVertexTangents", drawIndexedTriangleFan,
            void,
            const S3DVertexTangents*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleFanS3DVertex2TCoords", drawIndexedTriangleFan,
            void,
            const S3DVertex2TCoords*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleFanS3DVertex", drawIndexedTriangleFan,
            void,
            const S3DVertex*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleListS3DVertexTangents", drawIndexedTriangleList,
            void,
            const S3DVertexTangents*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleListS3DVertex2TCoords", drawIndexedTriangleList,
            void,
            const S3DVertex2TCoords*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "drawIndexedTriangleListS3DVertex", drawIndexedTriangleList,
            void,
            const S3DVertex*,
            u32,
            const u16*,
            u32
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "setRenderTargetFromArray", setRenderTarget,
        bool,
        const core::array< video::IRenderTarget > &,
        bool,
        bool,
        SColor
    )


    LM_FUNC_OVERLOAD(IVideoDriver, "setRenderTargetFromEnum", setRenderTarget,
        bool,
        E_RENDER_TARGET,
        bool,
        bool,
        SColor
    )

    LM_FUNC_OVERLOAD(IVideoDriver, "setRenderTargetFromTexture", setRenderTarget,
        bool,
        video::ITexture*,
        bool,
        bool,
        SColor
    )


    LM_CLASS(ns_irr_video, ITexture)
}

}}
