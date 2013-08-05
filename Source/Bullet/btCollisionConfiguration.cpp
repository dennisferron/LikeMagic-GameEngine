// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btCollisionConfiguration(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btCollisionConfiguration)

    LM_CLASS(ns_bullet, btDefaultCollisionConfiguration)
    LM_BASE(btDefaultCollisionConfiguration, btCollisionConfiguration)
    LM_CONSTR(btDefaultCollisionConfiguration,,)
    LM_CONSTR(btDefaultCollisionConfiguration,,btDefaultCollisionConstructionInfo const&)

    LM_CLASS(ns_bullet, btSoftBodyRigidBodyCollisionConfiguration)
    LM_BASE(btSoftBodyRigidBodyCollisionConfiguration, btDefaultCollisionConfiguration)
    LM_CONSTR(btSoftBodyRigidBodyCollisionConfiguration,,)
    LM_CONSTR(btSoftBodyRigidBodyCollisionConfiguration,, btDefaultCollisionConstructionInfo const&)

    LM_CLASS(ns_bullet, btDefaultCollisionConstructionInfo)
    LM_CONSTR(btDefaultCollisionConstructionInfo,,)
    LM_FIELD(btDefaultCollisionConstructionInfo,
        (m_stackAlloc)
        // These cause a compile error due to the pool allocator class only being forward declared.
        //(m_persistentManifoldPool)
        //(m_collisionAlgorithmPool)
        (m_defaultMaxPersistentManifoldPoolSize)
        (m_defaultMaxCollisionAlgorithmPoolSize)
        (m_customCollisionAlgorithmMaxElementSize)
        (m_defaultStackAllocatorSize)
        (m_useEpaPenetrationAlgorithm)
    )

}

}}

