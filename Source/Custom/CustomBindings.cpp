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

using namespace LikeMagic;

using namespace irr::scene;

namespace Bindings { namespace Custom {

template <int N> class TooManyTypes {};

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
    typedef std::pair<IMesh*, IMesh*> pair_of_IMesh;
    LM_CLASS(ns_custom, pair_of_IMesh)
    LM_FIELD(pair_of_IMesh, (first)(second))

/*
    auto& testclass_LM = type_sys.register_class<TooManyTypes<1>>("foobar");

    typedef TooManyTypes<2> TooMany2;
    LM_CLASS(ns_custom, TooMany2)
    typedef TooManyTypes<3> TooMany3;
    LM_CLASS(ns_custom, TooMany3)
    typedef TooManyTypes<4> TooMany4;
    LM_CLASS(ns_custom, TooMany4)
    typedef TooManyTypes<5> TooMany5;
    LM_CLASS(ns_custom, TooMany5)
*/

}

}}
