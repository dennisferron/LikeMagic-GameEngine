// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btConcaveShape(Namespace const& ns_bullet)
{
    // Previously defined in btCollisionShape.cpp; needed here as a base.
    LM_CLASS(ns_bullet, btCollisionShape)

    LM_CLASS(ns_bullet, btConcaveShape)
    LM_BASE(btConcaveShape, btCollisionShape)
    LM_FUNC(btConcaveShape, (processAllTriangles)(getMargin)(setMargin))

    LM_CLASS(ns_bullet, btTriangleMeshShape)
    LM_BASE(btTriangleMeshShape, btConcaveShape)
    LM_FUNC(btTriangleMeshShape, (localGetSupportingVertex)(localGetSupportingVertexWithoutMargin)(recalcLocalAabb)(getLocalAabbMin)(getLocalAabbMax))
    LM_FUNC_OVERLOAD_BOTH(btTriangleMeshShape, getMeshInterface, btStridingMeshInterface*)

    LM_CLASS(ns_bullet, btBvhTriangleMeshShape)
    LM_BASE(btBvhTriangleMeshShape, btTriangleMeshShape)
    LM_CONSTR(btBvhTriangleMeshShape,, btStridingMeshInterface *, bool, bool)
    LM_CONSTR(btBvhTriangleMeshShape,, btStridingMeshInterface *, bool, const btVector3 &, const btVector3 &, bool)
    LM_FUNC(btBvhTriangleMeshShape, (getOwnsBvh)(performRaycast)(performConvexcast)(processAllTriangles)(refitTree)(partialRefitTree)(getOptimizedBvh)(setOptimizedBvh)(buildOptimizedBvh)(usesQuantizedAabbCompression))

    LM_CLASS(ns_bullet, btMultimaterialTriangleMeshShape)
    LM_BASE(btMultimaterialTriangleMeshShape, btBvhTriangleMeshShape)
    LM_CONSTR(btMultimaterialTriangleMeshShape,, btStridingMeshInterface*, bool, bool)
    LM_CONSTR(btMultimaterialTriangleMeshShape,, btStridingMeshInterface*, bool, const btVector3 &, const btVector3 &, bool)
    LM_FUNC(btMultimaterialTriangleMeshShape, (getMaterialProperties))

    LM_CLASS(ns_bullet, btHeightfieldTerrainShape)
    LM_BASE(btHeightfieldTerrainShape, btConcaveShape)
    LM_CONSTR(btHeightfieldTerrainShape,,
        int, int, void *, btScalar, btScalar, btScalar, int, PHY_ScalarType, bool)

    LM_FUNC(btHeightfieldTerrainShape, (setUseDiamondSubdivision))

    LM_ENUM(ns_bullet, PHY_ScalarType)
}

}}

