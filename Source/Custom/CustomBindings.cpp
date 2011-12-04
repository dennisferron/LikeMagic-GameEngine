// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/Bindings.hpp"
#include "Bindings/Custom/Protos.hpp"
#include "Bindings/Custom/PhysicsAnimator.hpp"
#include "Bindings/Custom/KinematicAnimator.hpp"
#include "Bindings/Custom/LockAnimator.hpp"
#include "Bindings/Custom/IrrlichtBulletDebugDrawer.hpp"
#include "Bindings/Custom/GearConstraint.hpp"
#include "Bindings/Custom/SoftBodyMeshSynchronizer.hpp"
#include "Bindings/Custom/MeshTools.hpp"

#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "LikeMagic/Utility/UserMacros.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

#include "IoObject.h"

using namespace LikeMagic;

using namespace irr;
using namespace irr::scene;

namespace Bindings { namespace Custom {

// Extension methods

IoObject* at(std::map<s32, IoObject*> const& self, s32 key)
{
    auto result = self.find(key);
    if (result == self.end())
        return NULL;
    else
        return result->second;
}

IoObject* atPut(std::map<s32, IoObject*>& self, s32 key, IoObject* value)
{
    return self[key] = value;
}

void removeAt(std::map<s32, IoObject*>& self, s32 key)
{
    self.erase(key);
}


DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_custom = Namespace::global(type_sys).subspace("Custom");

    LM_CLASS(ns_custom, btMotionState)
    LM_CLASS(ns_custom, ISceneNodeAnimator)

    LM_CLASS(ns_custom, PhysicsAnimator)
    LM_BASE(PhysicsAnimator, btMotionState)
    LM_BASE(PhysicsAnimator, ISceneNodeAnimator)
    LM_CONSTR(PhysicsAnimator,, btTransform const&, btTransform const&)

    LM_CLASS(ns_custom, KinematicAnimator)
    LM_BASE(KinematicAnimator, btMotionState)
    LM_BASE(KinematicAnimator, ISceneNodeAnimator)
    LM_CONSTR(KinematicAnimator,, btTransform const&, btTransform const&)

    LM_CLASS(ns_custom, LockAnimator)
    LM_BASE(LockAnimator, btMotionState)
    LM_BASE(LockAnimator, ISceneNodeAnimator)
    LM_CONSTR(LockAnimator,, btMotionState const&, btTransform const&)
    LM_FIELD(LockAnimator, (stop_rotation))

    LM_CLASS(ns_custom, btIDebugDraw)

    LM_CLASS(ns_custom, IrrlichtBulletDebugDrawer)
    LM_BASE(IrrlichtBulletDebugDrawer, btIDebugDraw)
    LM_CONSTR(IrrlichtBulletDebugDrawer,, irr::video::IVideoDriver*)
    LM_FUNC(IrrlichtBulletDebugDrawer, (drawLine))

    LM_CLASS(ns_custom, btTypedConstraint)

    LM_CLASS(ns_custom, GearConstraint)
    LM_BASE(GearConstraint, btTypedConstraint)
    LM_CONSTR(GearConstraint,, btRigidBody&, btRigidBody&, btScalar)
    GearConstraint_LM.bind_static_method("getRotZ", GearConstraint::getRotZ);

    //LM_STATIC_FUNC(ns_custom, KinematicAnimator, get_watch_node)
    //LM_STATIC_FUNC(ns_custom, KinematicAnimator, set_watch_node)

    //LM_STATIC_FUNC(ns_custom, PhysicsAnimator, get_watch_node2)
    //LM_STATIC_FUNC(ns_custom, PhysicsAnimator, set_watch_node2)

    LM_STATIC_FUNC(ns_custom, Bindings::Custom, add_protos)

    LM_CLASS(ns_custom, SoftBodyMeshSynchronizer)
    LM_CONSTR(SoftBodyMeshSynchronizer,, btSoftBody*, irr::scene::IMeshBuffer*)
    LM_FUNC(SoftBodyMeshSynchronizer, (sync))

    LM_CLASS(ns_custom, MeshTools)
    LM_STATIC_MEMBER_FUNC(MeshTools, (getBaseVertex)(createMeshFromSoftBody)(createSoftBodyFromMesh)(splitMeshZ)
        (createMeshFromHeightmap))

    // Needed to be able to access members from the return value of splitMeshZ
    typedef MeshTools::SplitMeshResult SplitMeshResult;
    LM_CLASS(ns_custom, SplitMeshResult)
    LM_FIELD(SplitMeshResult, (left)(middle)(right))

    typedef std::map<irr::s32, IoObject*> map_of_s32_IoObject;
    LM_CLASS(ns_custom, map_of_s32_IoObject)
    LM_CONSTR(map_of_s32_IoObject,,)
    LM_EXTENSION_METHOD(map_of_s32_IoObject, (at)(atPut)(removeAt))

}

}}
