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
using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace irr::io;


namespace Bindings { namespace Irrlicht {

void add_bindings_scene(RuntimeTypeSystem& type_sys)
{
    auto ns_irr_scene = Namespace::global(type_sys).subspace("irr").subspace("scene");

    LM_CLASS(ns_irr_scene, E_BUFFER_TYPE)
    LM_CLASS(ns_irr_scene, E_HARDWARE_MAPPING)

    // LM_FUNC for this already defined in "irr" bindings.
    LM_CLASS(ns_irr_scene, IReferenceCounted)
    LM_FUNC(IReferenceCounted, (drop)(grab)(getDebugName)(getReferenceCount))

    LM_CLASS(ns_irr_scene, ISceneManager)
    LM_FUNC(ISceneManager, (getRootSceneNode)
            (addCameraSceneNode)(addCameraSceneNodeFPS)(addCameraSceneNodeMaya)
            (addMeshSceneNode)(createRotationAnimator)(drawAll)(getGeometryCreator)
            (addLightSceneNode)(createFollowSplineAnimator)
            (getSceneCollisionManager)(addAnimatedMeshSceneNode))
    LM_FUNC_OVERLOAD(ISceneManager, "createTriangleSelector", createTriangleSelector, ITriangleSelector*, IAnimatedMeshSceneNode*)
    LM_FUNC_OVERLOAD(ISceneManager, "createTriangleSelector", createTriangleSelector, ITriangleSelector*, IMesh*, ISceneNode*)
    LM_FUNC_OVERLOAD(ISceneManager, "getMeshFromIReadFile", getMesh, IAnimatedMesh*, IReadFile*);
    LM_FUNC_OVERLOAD(ISceneManager, "getMeshFromPath", getMesh, IAnimatedMesh*, path const&);

    LM_CLASS(ns_irr_scene, IMeshBuffer)
    LM_BASE(IMeshBuffer, IReferenceCounted)
    LM_FUNC(IMeshBuffer, (getBoundingBox)(getHardwareMappingHint_Index)(getHardwareMappingHint_Vertex)
            (getIndexCount)(getIndexType)(getVertexCount)(getVertexType)(recalculateBoundingBox)(setBoundingBox)(setDirty)(setHardwareMappingHint)
    )
    LM_FUNC_OVERLOAD(IMeshBuffer, "append", append, void, const IMeshBuffer *const)
    LM_FUNC_OVERLOAD(IMeshBuffer, "append", append, void,
        const void *const,
        u32,
        const u16 *const,
        u32
    )
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getIndices, u16*)
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getMaterial, video::SMaterial&)
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getNormal, core::vector3df&, u32)
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getPosition, core::vector3df&, u32)
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getTCoords, core::vector2df&, u32)
    LM_FUNC_OVERLOAD_BOTH(IMeshBuffer, getVertices, void*)


    LM_CLASS(ns_irr_scene, IMesh)
    LM_BASE(IMesh, IReferenceCounted)
    LM_FUNC(IMesh, (getBoundingBox)(getMeshBufferCount)(setBoundingBox)(setDirty)(setHardwareMappingHint)(setMaterialFlag))

    LM_FUNC_OVERLOAD_CONST(IMesh, "getMeshBufferForMaterial", getMeshBuffer, IMeshBuffer*, const video::SMaterial&)
    LM_FUNC_OVERLOAD_CONST(IMesh, "getMeshBuffer", getMeshBuffer, IMeshBuffer*, u32)

    LM_CLASS(ns_irr_scene, SMesh)
    LM_BASE(SMesh, IMesh)

    LM_CLASS(ns_irr_scene, IAnimatedMesh)
    LM_BASE(IAnimatedMesh, IMesh)

    LM_CLASS(ns_irr_scene, IGeometryCreator)
    LM_FUNC(IGeometryCreator, (createArrowMesh)(createConeMesh)(createCubeMesh)(createCylinderMesh)
            (createHillPlaneMesh)(createPlaneMesh)(createSphereMesh)(createTerrainMesh)(createVolumeLightMesh))

    LM_CLASS(ns_irr_scene, ISceneNodeAnimator)
    LM_BASE(ISceneNodeAnimator, IReferenceCounted)
    LM_FUNC(ISceneNodeAnimator, (animateNode))

    LM_CLASS(ns_irr_scene, ISceneNode)
    LM_BASE(ISceneNode, IReferenceCounted)
    LM_FUNC(ISceneNode, (addAnimator)(addChild)(setMaterialFlag)(OnRegisterSceneNode)(render)
                        (getBoundingBox)(getMaterialCount)(getMaterial)
                        (getAbsoluteTransformation)(getRelativeTransformation)(setParent)
                        (setPosition)(getPosition)(setRotation)(getRotation)(getAbsolutePosition)(getAnimators)
                        (setScale)(getScale)(removeAnimator)(removeAnimators)(remove)(setMaterialTexture)(setMaterialType)
                        (updateAbsolutePosition)(OnAnimate)(setTriangleSelector)(getName)(getID)
           )

    LM_CLASS(ns_irr_scene, IMeshSceneNode)
    LM_BASE(IMeshSceneNode, ISceneNode)

    LM_CLASS(ns_irr_scene, ILightSceneNode)
    LM_BASE(ILightSceneNode, ISceneNode)

    LM_CLASS(ns_irr_scene, IAnimatedMeshSceneNode)
    LM_BASE(IAnimatedMeshSceneNode, ISceneNode)
    LM_FUNC(IAnimatedMeshSceneNode, (setAnimationSpeed))

    LM_CLASS(ns_irr_scene, ICameraSceneNode)
    LM_BASE(ICameraSceneNode, ISceneNode)
    LM_FUNC(ICameraSceneNode, (bindTargetAndRotation)(getAspectRatio)(getFarValue)(getFOV)(getNearValue)(getProjectionMatrix)
            (getTarget)(getTargetAndRotationBinding)(getUpVector)(getViewFrustum)(getViewMatrix)(getViewMatrixAffector)(isInputReceiverEnabled)
            (isOrthogonal)(OnEvent)(setAspectRatio)(setFarValue)(setFOV)(setInputReceiverEnabled)(setNearValue)(setProjectionMatrix)(setRotation)
            (setTarget)(setUpVector)(setViewMatrixAffector))

    LM_CLASS(ns_irr_scene, ITriangleSelector)
    LM_BASE(ITriangleSelector, IReferenceCounted)
    LM_FUNC(ITriangleSelector, (getSceneNodeForTriangle)(getTriangleCount))
    LM_FUNC_OVERLOAD_CONST(ITriangleSelector, "getTrianglesForNode", getTriangles, void, triangle3df*, s32, s32&, const core::matrix4*)
    LM_FUNC_OVERLOAD_CONST(ITriangleSelector, "getTrianglesForBox",  getTriangles, void, triangle3df*, s32, s32&, const core::aabbox3d<f32>&, const core::matrix4*)
    LM_FUNC_OVERLOAD_CONST(ITriangleSelector, "getTrianglesForLine", getTriangles, void, triangle3df*, s32, s32&, const core::line3d<f32>&,   const core::matrix4*)

    LM_CLASS(ns_irr_scene, ISceneCollisionManager)
    LM_BASE(ISceneCollisionManager, IReferenceCounted)
    LM_FUNC(ISceneCollisionManager, (getRayFromScreenCoordinates)(getSceneNodeAndCollisionPointFromRay)(getCollisionPoint)(getCollisionResultPosition)
            (getSceneNodeFromCameraBB)(getSceneNodeFromRayBB)(getSceneNodeFromScreenCoordinatesBB))
}

}}
