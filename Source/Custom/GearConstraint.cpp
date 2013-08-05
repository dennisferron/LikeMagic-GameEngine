// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/GearConstraint.hpp"

#include <stdexcept>
#include <iostream>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#define TAU 2*M_PI

using namespace Bindings::Custom;

GearConstraint::GearConstraint(btRigidBody& rbA, btRigidBody& rbB, btScalar ratio_)
:
    btTypedConstraint(POINT2POINT_CONSTRAINT_TYPE, rbA, rbB),
    ratio(ratio_)
{
    setDbgDrawSize(0);

    // Constrain the gears' rotation to one plane.
    rbA.setAngularFactor(btVector3(0,0,1));
    rbB.setAngularFactor(btVector3(0,0,1));
}

btScalar GearConstraint::getRotZ(btRigidBody const& body)
{
    btQuaternion quat = body.getOrientation();

    btScalar w = quat.getW();
    btScalar x = quat.getX();
    btScalar y = quat.getY();
    btScalar z = quat.getZ();
    return atan2(
        2.0 * (x*y + z*w),
        (x*x - y*y - z*z + w*w));
}

int sign(double value)
{
    if (value < 0)
        return -1;
    else
        return 1;
}


void GearConstraint::solveConstraintObsolete(
    btRigidBody& bodyA, btRigidBody& bodyB, btScalar timeStep)
{
    //std::cout << "GearConstraint ratio is " << ratio << std::endl;

    btScalar drivingVel = bodyA.getAngularVelocity().getZ();
    btScalar drivenVel = bodyB.getAngularVelocity().getZ();

    bodyB.setAngularVelocity(bodyA.getAngularVelocity()*ratio);

    /*
    btScalar drivingTrq = bodyA.getTotalTorque().getZ();
    btScalar drivenTrq = bodyB.getTotalTorque().getZ();

    btScalar correctionVel = drivingVel - drivenVel;

    btScalar force = correctionVel*60*timeStep / ((drivingVel+drivenVel)/2);
    //btScalar force = drivingTrq - drivenTrq;

    btScalar action_force = force/sqrt_ratio;
    btScalar reaction_force = -force*sqrt_ratio;

    std::cout << "ATrq: " << drivingTrq << " BTrq: " << drivenTrq << " Aforce: " << action_force << " Bforce: " << reaction_force << std::endl;

    bodyB.applyTorque(btVector3(0, 0, action_force));

    // Action causes reaction
    bodyA.applyTorque(btVector3(0, 0, reaction_force));

    //std::cout << "Correction angle: " << correctionAng << std::endl;

    //bodyB.applyTorque(btVector3(0, 0, 5));
    */

}

void GearConstraint::getInfo1 (btConstraintInfo1* info)
{
    //Don't solve any rows using PGS, just report 0
    info->m_numConstraintRows = 0;
    info->nub = 0;
}

void GearConstraint::getInfo2(btConstraintInfo2* info) {}
void GearConstraint::setParam (int num, btScalar value, int axis) {}
btScalar GearConstraint::getParam (int num, int axis) const { return 0; }

// Irrlicht stuff
void GearConstraint::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
    // TODO:  Add gear animation here.
}

irr::scene::ISceneNodeAnimator* GearConstraint::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
{
    throw std::runtime_error("createClone for irrlicht not implemented yet because I'm not sure how/whether the physics object gets cloned.");
}


