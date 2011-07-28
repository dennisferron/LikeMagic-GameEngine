// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btStridingMeshInterface(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btStridingMeshInterface)
    LM_FUNC(btStridingMeshInterface, (InternalProcessAllTriangles)(calculateAabbBruteForce)(getLockedVertexIndexBase)(getLockedReadOnlyVertexIndexBase)
            (unLockVertexBase)(unLockReadOnlyVertexBase)(getNumSubParts)(preallocateVertices)(preallocateIndices)(hasPremadeAabb)(setPremadeAabb)(getPremadeAabb)
            (getScaling)(setScaling)(calculateSerializeBufferSize)(serialize))

    LM_CLASS(ns_bullet, btTriangleIndexVertexArray)
    LM_BASE(btTriangleIndexVertexArray, btStridingMeshInterface)
    LM_CONSTR(btTriangleIndexVertexArray,,)
    LM_CONSTR(btTriangleIndexVertexArray,, int, int*, int, int, btScalar *, int)
    LM_FUNC(btTriangleIndexVertexArray, (addIndexedMesh)(getLockedVertexIndexBase)(getLockedReadOnlyVertexIndexBase)(unLockVertexBase)(unLockReadOnlyVertexBase)
            (getNumSubParts)(preallocateVertices)(preallocateIndices)(hasPremadeAabb)(setPremadeAabb)(getPremadeAabb))

    LM_FUNC_OVERLOAD_BOTH(btTriangleIndexVertexArray, getIndexedMeshArray, IndexedMeshArray &)

    LM_CLASS(ns_bullet, btTriangleMesh)
    LM_BASE(btTriangleMesh, btTriangleIndexVertexArray)
    LM_CONSTR(btTriangleMesh,, bool, bool)
    LM_FUNC(btTriangleMesh, (getUse32bitIndices)(getUse4componentVertices)(addTriangle)(getNumTriangles)(addIndex))

/* Not in this version of bullet ?
    LM_CLASS(ns_bullet, btTriangleIndexVertexMaterialArray)
    LM_BASE(btTriangleIndexVertexMaterialArray, btTriangleIndexVertexArray)
    LM_CONSTR(btTriangleIndexVertexMaterialArray,,)
    LM_CONSTR(btTriangleIndexVertexMaterialArray,, int, int *, int, int, btScalar *, int, int, unsigned char *, int, int *, int)
    LM_FUNC(btTriangleIndexVertexMaterialArray, (addMaterialProperties)(getLockedMaterialBase)(getLockedReadOnlyMaterialBase))
*/
}

}}

