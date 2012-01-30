// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/PhysicsAnimator.hpp"
#include "Bindings/Custom/CustomAnimatorTypes.hpp"

#include <stdexcept>
#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

using namespace Bindings::Custom;

PhysicsAnimator::PhysicsAnimator(btTransform const& trans_, btTransform const& centerOfMassOffset_)
    : trans(trans_), centerOfMassOffset(centerOfMassOffset_), cached_node(0)
{
    // bug fix:  motion states are never updated by bullet for nonmoving objects
    // so need to synchronize the irrlicht object to the start transform.
    // WAIT!  How can this work?  There is no cached node yet to sync!
    sync();
}

ESCENE_NODE_ANIMATOR_TYPE PhysicsAnimator::getType() const
{
    return static_cast<ESCENE_NODE_ANIMATOR_TYPE>(C_ESNAT_PHYSICAL);
}

// For debugging
ISceneNode* PhysicsAnimator::watch_node = NULL;

void PhysicsAnimator::sync()
{
    if (cached_node)
    {
        irr::core::matrix4 matr;
        (trans*centerOfMassOffset).getOpenGLMatrix(matr.pointer());
        cached_node->setRotation(matr.getRotationDegrees());
        cached_node->setPosition(matr.getTranslation());
        cached_node->updateAbsolutePosition();
    }
}

void PhysicsAnimator::setWorldTransform(btTransform const& worldTrans)
{
    trans = worldTrans;

    sync();

    //if (watch_node == cached_node)
    //    std::cout << " setTrans phys, world: " << worldTrans.getOrigin().getY() << " trans: " << trans.getOrigin().getY() << " disp: " << cached_node->getAbsolutePosition().Y << std::endl;
}

void PhysicsAnimator::getWorldTransform(btTransform& worldTrans) const
{
    worldTrans = trans;
}

void PhysicsAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
    // We don't care about the timeMs value here; bullet is handling that.

    // Set scene node stuff to the transform values.
    //btVector3 pos = trans.getOrigin();
    //node->setPosition(vector3df(pos.x(), pos.y(), pos.z()));

    cached_node = node;
    sync();

    //if (watch_node == cached_node)
    //    std::cout << "anim phys, phys: " << trans.getOrigin().getY() << " disp: " << cached_node->getAbsolutePosition().Y << std::endl;

}


ISceneNodeAnimator* PhysicsAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
{
    throw std::runtime_error("createClone for irrlicht not implemented yet because I'm not sure how/whether the physics object gets cloned.");
}
