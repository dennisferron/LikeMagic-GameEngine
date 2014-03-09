// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btStridingMeshInterface()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btStridingMeshInterface)
    LM_FUNC(btStridingMeshInterface, (InternalProcessAllTriangles)(calculateAabbBruteForce)(getLockedVertexIndexBase)(getLockedReadOnlyVertexIndexBase)
            (unLockVertexBase)(unLockReadOnlyVertexBase)(getNumSubParts)(preallocateVertices)(preallocateIndices)(hasPremadeAabb)(setPremadeAabb)(getPremadeAabb)
            (getScaling)(setScaling)(calculateSerializeBufferSize)(serialize))

    LM_CLASS(ns_bullet, btTriangleIndexVertexArray)
    LM_BASE(btTriangleIndexVertexArray, btStridingMeshInterface)
    LM_CONSTR(btTriangleIndexVertexArray,"new")
    LM_CONSTR(btTriangleIndexVertexArray, "new", int, int*, int, int, btScalar *, int)
    LM_FUNC(btTriangleIndexVertexArray, (addIndexedMesh)(getLockedVertexIndexBase)(getLockedReadOnlyVertexIndexBase)(unLockVertexBase)(unLockReadOnlyVertexBase)
            (getNumSubParts)(preallocateVertices)(preallocateIndices)(hasPremadeAabb)(setPremadeAabb)(getPremadeAabb))

    LM_FUNC_OVERLOAD_BOTH(btTriangleIndexVertexArray, getIndexedMeshArray, IndexedMeshArray &)

    LM_CLASS(ns_bullet, btTriangleMesh)
    LM_BASE(btTriangleMesh, btTriangleIndexVertexArray)
    LM_CONSTR(btTriangleMesh, "new", bool, bool)
    LM_FUNC(btTriangleMesh, (getUse32bitIndices)(getUse4componentVertices)(addTriangle)(getNumTriangles)(addIndex))

/* Not in this version of bullet ?
    LM_CLASS(ns_bullet, btTriangleIndexVertexMaterialArray)
    LM_BASE(btTriangleIndexVertexMaterialArray, btTriangleIndexVertexArray)
    LM_CONSTR(btTriangleIndexVertexMaterialArray,"new")
    LM_CONSTR(btTriangleIndexVertexMaterialArray, "new", int, int *, int, int, btScalar *, int, int, unsigned char *, int, int *, int)
    LM_FUNC(btTriangleIndexVertexMaterialArray, (addMaterialProperties)(getLockedMaterialBase)(getLockedReadOnlyMaterialBase))
*/

    LM_CLASS(ns_bullet, btIndexedMesh)
    LM_CONSTR(btIndexedMesh,"new")
    LM_FIELD(btIndexedMesh, (m_numTriangles)(m_triangleIndexBase)(m_triangleIndexStride)(m_numVertices)(m_vertexBase)(m_vertexStride)(m_indexType)(m_vertexType))
}

}}

