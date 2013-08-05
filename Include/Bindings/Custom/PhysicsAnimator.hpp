// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

namespace Bindings { namespace Custom {

class PhysicsAnimator : public btMotionState, public irr::scene::ISceneNodeAnimator
{
public:

    // Bullet stuff
    virtual void setWorldTransform(btTransform const& worldTrans);
    virtual void getWorldTransform(btTransform& worldTrans) const;

    // Irrlicht stuff
    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                    irr::scene::ISceneManager* newManager=0);
    irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const;

    PhysicsAnimator(btTransform const& trans_, btTransform const& centerOfMassOffset_);

    static irr::scene::ISceneNode* watch_node;
    static irr::scene::ISceneNode* get_watch_node2() { return watch_node; }
    static void set_watch_node2(irr::scene::ISceneNode* value) { watch_node = value; }

private:

    btTransform trans;
    btTransform centerOfMassOffset;
    irr::scene::ISceneNode* cached_node;

    void sync();

};

}}
