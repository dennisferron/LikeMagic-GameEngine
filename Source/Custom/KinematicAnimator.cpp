// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/KinematicAnimator.hpp"

#include <stdexcept>
#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

using namespace Bindings::Custom;

KinematicAnimator::KinematicAnimator(btTransform const& trans_, btTransform const& centerOfMassOffset_)
    : init(false), trans(trans_), centerOfMassOffset(centerOfMassOffset_), cached_node(NULL)
{
    // bug fix:  motion states are never updated by bullet for nonmoving objects
    // so need to synchronize the irrlicht object to the start transform.
    // (Actually the bug was with PhysicsAnimator but I added a call to sync
    // here too for consistency & defensivce programming.)
    sync_to_irrlicht();
}


void KinematicAnimator::setWorldTransform(btTransform const& worldTrans)
{
    trans = worldTrans;
}

void KinematicAnimator::getWorldTransform(btTransform& worldTrans) const
{
    sync_to_irrlicht();
    worldTrans = trans;

    //if (cached_node)
    //    std::cout << "getTrans kinetic, phys: " << trans.getOrigin().getY() << " disp: " << cached_node->getAbsolutePosition().Y << std::endl;
}

// For debugging
ISceneNode* KinematicAnimator::watch_node = NULL;

void KinematicAnimator::sync_to_irrlicht() const
{
    if (cached_node)
    {
        cached_node->updateAbsolutePosition();
        irr::core::matrix4 matr = cached_node->getAbsoluteTransformation();
        trans.setFromOpenGLMatrix(matr.pointer());
        trans *= centerOfMassOffset.inverse();
    }
}


void KinematicAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
    cached_node = node;

    if (!init)
    {
        // Make display shape position & orientation equal the initial phys obj pos.
        init = true;
        irr::core::matrix4 matr;
        (trans*centerOfMassOffset).getOpenGLMatrix(matr.pointer());
        node->setRotation(matr.getRotationDegrees());
        node->setPosition(matr.getTranslation());
    }

    // run all the other animators for this scene node.
    auto anims = node->getAnimators();

    for (auto it=anims.begin(); it != anims.end(); ++it)
        if (*it != this)
            (**it).animateNode(node, timeMs);

    sync_to_irrlicht();

    //std::cout << "animate kinetic, phys: " << trans.getOrigin().getY() << " disp: " << cached_node->getAbsolutePosition().Y << std::endl;
}


ISceneNodeAnimator* KinematicAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
{
    throw std::runtime_error("createClone for irrlicht not implemented yet because I'm not sure how/whether the physics object gets cloned.");
}
