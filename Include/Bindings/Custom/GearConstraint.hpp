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

class GearConstraint : public btTypedConstraint, public irr::scene::ISceneNodeAnimator
{
public:

    GearConstraint(btRigidBody& rbA, btRigidBody& rbB, btScalar ratio);

    virtual void solveConstraintObsolete(
        btRigidBody& bodyA, btRigidBody& bodyB, btScalar timeStep);

    virtual void getInfo1(btConstraintInfo1* info);

    virtual void getInfo2(btConstraintInfo2* info);
    virtual void setParam (int num, btScalar value, int axis=-1);
    virtual btScalar getParam (int num, int axis=-1) const;

    // Irrlicht stuff
    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                    irr::scene::ISceneManager* newManager=0);

    static btScalar getRotZ(btRigidBody const& body);

private:
    btScalar ratio;
    btScalar lastDrivingAng;
    btScalar lastDrivenAng;

    //double spoolA;
    //double spoolB;
};

}}
