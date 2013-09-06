// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftBody.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btSoftBody()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btCollisionObject)

    LM_CLASS(ns_bullet, btSoftBody)
    LM_BASE(btSoftBody, btCollisionObject)
    LM_CONSTR(btSoftBody, "new", btSoftBodyWorldInfo*, int, const btVector3*, const btScalar*)
    LM_FUNC(btSoftBody, (transform)(translate)(rotate))
    LM_FIELD(btSoftBody,
        (m_collisionDisabledObjects)(m_cfg)(m_sst)(m_pose)(m_tag)(m_worldInfo)(m_notes)
        (m_nodes)(m_links)(m_faces)(m_tetras)(m_anchors)(m_rcontacts)(m_scontacts)(m_joints)
        (m_materials)(m_timeacc)(m_bUpdateRtCst)(m_clusters)
        (m_clusterConnectivity)(m_initialWorldTransform)(m_userIndexMapping)

        // Can't set these because they are noncopyable classes
        //(m_ndbvt)(m_fdbvt)(m_cdbvt)
    )

    LM_ARRAY_FIELD(btSoftBody, (m_bounds))

    typedef btSoftBody::Config btSoftBody_Config;
    LM_CLASS(ns_bullet, btSoftBody_Config)
    LM_FIELD(btSoftBody_Config,
        (aeromodel)(kVCF)(kDP)(kDG)(kLF)(kPR)(kVC)(kDF)(kMT)(kCHR)(kKHR)(kSHR)(kAHR)
        (kSRHR_CL)(kSKHR_CL)(kSSHR_CL)(kSR_SPLT_CL)(kSK_SPLT_CL)(kSS_SPLT_CL)(maxvolume)
        (timescale)(viterations)(piterations)(diterations)(citerations)(collisions)
        (m_vsequence)(m_psequence)(m_dsequence)
    )

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
    LM_CONSTR(btSoftBodyWorldInfo,"new")
    LM_FIELD(btSoftBodyWorldInfo, (air_density)(water_density)(water_offset)(water_normal)(m_broadphase)(m_dispatcher)(m_gravity)(m_sparsesdf))

    typedef btSparseSdf<3> btSparseSdf_3;
    LM_CLASS(ns_bullet, btSparseSdf_3)
    LM_CONSTR(btSparseSdf_3,"new")
    LM_FIELD(btSparseSdf_3,(cells)(voxelsz)(puid)(ncells)(nprobes)(nqueries))
    LM_FUNC(btSparseSdf_3, (Initialize)(Reset)(GarbageCollect)(RemoveReferences)(Evaluate)(BuildCell))
    LM_STATIC_MEMBER_FUNC(btSparseSdf_3, (DistanceToShape)(Decompose)(Lerp)(Hash))
}

}}

