// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftBody.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btSoftBody(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btCollisionObject)


    LM_CLASS_NO_COPY(ns_bullet, btSoftBody)
    LM_BASE(btSoftBody, btCollisionObject)
    LM_CONSTR(btSoftBody,, btSoftBodyWorldInfo*, int, const btVector3*, const btScalar*)

    // btSoftBody class has lots of functions; most of them overloaded.  I'll add them later.
    // Also has lots of fields.

    LM_CLASS(ns_bullet, btSoftBodyHelpers)
    LM_STATIC_MEMBER_FUNC(btSoftBodyHelpers,
        (Draw)
        (DrawInfos)
        (DrawNodeTree)
        (DrawFaceTree)
        (DrawClusterTree)
        (DrawFrame)
        (CreateRope)
        (CreatePatch)
        (CreatePatchUV)
        (CalculateUV)
        (CreateEllipsoid)
        (CreateFromTriMesh)
        (CreateFromConvexHull)
        (CreateFromTetGenData)
    )

    LM_CLASS(ns_bullet,	btSoftBodyWorldInfo)
    LM_CONSTR(btSoftBodyWorldInfo,,)
    LM_FIELD(btSoftBodyWorldInfo, (air_density)(water_density)(water_offset)(water_normal)(m_broadphase)(m_dispatcher)(m_gravity)(m_sparsesdf))

    typedef btSparseSdf<3> btSparseSdf_3;
    LM_CLASS(ns_bullet, btSparseSdf_3)
    LM_CONSTR(btSparseSdf_3,,)
    LM_FIELD(btSparseSdf_3,(cells)(voxelsz)(puid)(ncells)(nprobes)(nqueries))
    LM_FUNC(btSparseSdf_3, (Initialize)(Reset)(GarbageCollect)(RemoveReferences)(Evaluate)(BuildCell))
    LM_STATIC_MEMBER_FUNC(btSparseSdf_3, (DistanceToShape)(Decompose)(Lerp)(Hash))


}

}}

