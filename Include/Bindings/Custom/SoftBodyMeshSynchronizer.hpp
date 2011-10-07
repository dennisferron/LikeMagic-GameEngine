// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"

class btSoftBody;

namespace Bindings { namespace Custom {

class SoftBodyMeshSynchronizer : public irr::scene::ISceneNodeAnimator
{
private:
    btSoftBody* softBody;

public:
    SoftBodyMeshSynchronizer(btSoftBody* softBody_);
    ~SoftBodyMeshSynchronizer();

    // Irrlicht stuff
    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                    irr::scene::ISceneManager* newManager=0);
};

}}
