// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/Bindings.hpp"
#include "Bindings/Custom/Protos.hpp"
#include "Bindings/Custom/ScriptObjAnimator.hpp"
#include "Bindings/Custom/PhysicsAnimator.hpp"
#include "Bindings/Custom/KinematicAnimator.hpp"
#include "Bindings/Custom/LockAnimator.hpp"
#include "Bindings/Custom/IrrlichtBulletDebugDrawer.hpp"
#include "Bindings/Custom/GearConstraint.hpp"
#include "Bindings/Custom/SoftBodyMeshSynchronizer.hpp"
#include "Bindings/Custom/MeshTools.hpp"
#include "Bindings/Custom/FlagBits.hpp"
#include "Bindings/Custom/SurfaceQuadTree.hpp"

#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "LikeMagic/Utility/UserMacros.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

#include "IoObject.h"

#include "Bindings/Custom/SceneNodePtrTest.hpp"

using namespace LikeMagic;

using namespace irr;
using namespace irr::core;
using namespace irr::scene;


namespace Bindings { namespace Custom {


// Support FlagBits for Irrlicht Scene Node* ID
int  flag_bits_get_value(ISceneNode* node)            { return node->getID();       }
void flag_bits_set_value(ISceneNode* node, int value) {        node->setID(value);  }
typedef FlagBits<ISceneNode*> FlagBits_of_ISceneNode;

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_custom = Namespace::global(type_sys).subspace("Custom");

    LM_CLASS(ns_custom, SceneNodePtrTest)
    LM_STATIC_MEMBER_FUNC(SceneNodePtrTest,
        (printSceneNodePtr)(sceneNodePtrToVoidPtr)(voidPtrToSceneNodePtr)
        (sceneNodePtrToString)(stringToSceneNodePtr)(addLightSceneNode))

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

    LM_CLASS(ns_custom, ScriptObjAnimator)
    LM_BASE(ScriptObjAnimator, ISceneNodeAnimator)
    LM_CONSTR(ScriptObjAnimator,, IoObject*)
    LM_FUNC(ScriptObjAnimator, (getScriptObj))
    LM_STATIC_MEMBER_FUNC(ScriptObjAnimator, (findIn))

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

    LM_STATIC_FUNC(ns_custom, Bindings::Custom, add_protos)

    LM_CLASS(ns_custom, SoftBodyMeshSynchronizer)
    LM_CONSTR(SoftBodyMeshSynchronizer,, btSoftBody*, irr::scene::IMeshBuffer*)
    LM_FUNC(SoftBodyMeshSynchronizer, (sync))

    LM_CLASS(ns_custom, MeshTools)
    LM_STATIC_MEMBER_FUNC(MeshTools, (getBaseVertex)(createMeshFromSoftBody)(createSoftBodyFromMesh)(splitMeshZ)
        (createMeshFromHeightmap)(createHillMesh))

    // Needed to be able to access members from the return value of splitMeshZ
    typedef MeshTools::SplitMeshResult SplitMeshResult;
    LM_CLASS(ns_custom, SplitMeshResult)
    LM_FIELD(SplitMeshResult, (left)(middle)(right))

    LM_CLASS(ns_custom, FlagBits_of_ISceneNode)
    LM_CONSTR(FlagBits_of_ISceneNode,, ISceneNode*)
    LM_FUNC(FlagBits_of_ISceneNode, (getBit)(setBit)(extractNumber)(embedNumber))

    typedef SurfaceQuadTree::Shell Shell;
    LM_CLASS(ns_custom, Shell)

    LM_CLASS(ns_custom, SurfaceQuadTree)
    LM_CONSTR(SurfaceQuadTree,,rectf, TPS::ThinPlateQuilt&)
    LM_FUNC(SurfaceQuadTree, (triangulate)(split))
}

}}
