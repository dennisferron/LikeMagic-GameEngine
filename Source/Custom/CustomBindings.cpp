// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/Bindings.hpp"
#include "Bindings/Custom/CustomValues.hpp"
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

#include "LikeMagic/BindingMacros.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

//#include "void.h"

#include "Bindings/Custom/SceneNodePtrTest.hpp"

using namespace LM;
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

namespace Bindings { namespace Custom {

// Support FlagBits for Irrlicht Scene Node* ID
int  flag_bits_get_value(ISceneNode* node)            { return node->getID();       }
void flag_bits_set_value(ISceneNode* node, int value) {        node->setID(value);  }
typedef FlagBits<ISceneNode*> FlagBits_of_ISceneNode;

MESHTOOLS_BINDINGS_API void add_bindings()
{
    TypeMirror& ns_global = type_system->global_namespace();
    TypeMirror& ns_custom = register_namespace("Custom", ns_global);

    LM_CLASS(ns_custom, SceneNodePtrTest)
    LM_STATIC_MEMBER_FUNC(SceneNodePtrTest,
        (printSceneNodePtr)(sceneNodePtrToVoidPtr)(voidPtrToSceneNodePtr)
        (sceneNodePtrToString)(stringToSceneNodePtr)(addLightSceneNode))

    LM_CLASS(ns_custom, btMotionState)
    LM_CLASS(ns_custom, ISceneNodeAnimator)

    LM_CLASS(ns_custom, PhysicsAnimator)
    LM_BASE(PhysicsAnimator, btMotionState)
    LM_BASE(PhysicsAnimator, ISceneNodeAnimator)
    LM_CONSTR(PhysicsAnimator, "new", btTransform const&, btTransform const&)

    LM_CLASS(ns_custom, KinematicAnimator)
    LM_BASE(KinematicAnimator, btMotionState)
    LM_BASE(KinematicAnimator, ISceneNodeAnimator)
    LM_CONSTR(KinematicAnimator, "new", btTransform const&, btTransform const&)

    LM_CLASS(ns_custom, LockAnimator)
    LM_BASE(LockAnimator, btMotionState)
    LM_BASE(LockAnimator, ISceneNodeAnimator)
    LM_CONSTR(LockAnimator, "new", btMotionState const&, btTransform const&)
    LM_FIELD(LockAnimator, (stop_rotation))

    LM_CLASS(ns_custom, ScriptObjAnimator)
    LM_BASE(ScriptObjAnimator, ISceneNodeAnimator)
    LM_CONSTR(ScriptObjAnimator, "new", void*)
    LM_FUNC(ScriptObjAnimator, (getScriptObj))
    LM_STATIC_MEMBER_FUNC(ScriptObjAnimator, (findIn))

    LM_CLASS(ns_custom, btIDebugDraw)

    LM_CLASS(ns_custom, IrrlichtBulletDebugDrawer)
    LM_BASE(IrrlichtBulletDebugDrawer, btIDebugDraw)
    LM_CONSTR(IrrlichtBulletDebugDrawer, "new", irr::video::IVideoDriver*)
    LM_FUNC(IrrlichtBulletDebugDrawer, (drawLine))

    LM_CLASS(ns_custom, btTypedConstraint)

    LM_CLASS(ns_custom, GearConstraint)
    LM_BASE(GearConstraint, btTypedConstraint)
    LM_CONSTR(GearConstraint, "new", btRigidBody&, btRigidBody&, btScalar)
    LM_STATIC_FUNC_NAME(GearConstraint_LM, "getRotZ", GearConstraint::getRotZ)

    LM_STATIC_FUNC_NAME(ns_custom, "add_values", Bindings::Custom::add_values)

    LM_CLASS(ns_custom, SoftBodyMeshSynchronizer)
    LM_CONSTR(SoftBodyMeshSynchronizer, "new", btSoftBody*, irr::scene::IMeshBuffer*)
    LM_FUNC(SoftBodyMeshSynchronizer, (sync))

    LM_CLASS(ns_custom, MeshTools)
    LM_STATIC_MEMBER_FUNC(MeshTools, (getBaseVertex)(createMeshFromSoftBody)(createSoftBodyFromMesh)(splitMeshZ)
        (createMeshFromHeightmap)(createHillMesh))

    // Needed to be able to access members from the return value of splitMeshZ
    typedef MeshTools::SplitMeshResult SplitMeshResult;
    LM_CLASS(ns_custom, SplitMeshResult)
    LM_FIELD(SplitMeshResult, (left)(middle)(right))

    LM_CLASS(ns_custom, FlagBits_of_ISceneNode)
    LM_CONSTR(FlagBits_of_ISceneNode, "new", ISceneNode*)
    LM_FUNC(FlagBits_of_ISceneNode, (getBit)(setBit)(extractNumber)(embedNumber))

    typedef SurfaceQuadTree::Shell Shell;
    LM_CLASS(ns_custom, Shell)

    LM_CLASS(ns_custom, SurfaceQuadTree)
    LM_CONSTR(SurfaceQuadTree, "new",rectf, TPS::ThinPlateQuilt&, std::string)
    LM_FUNC(SurfaceQuadTree, (triangulate)(split)(fit))
}

}}
