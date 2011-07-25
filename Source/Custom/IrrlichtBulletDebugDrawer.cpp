// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/IrrlichtBulletDebugDrawer.hpp"
#include "irrlicht.h"

#include <iostream>

using namespace Bindings::Custom;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

IrrlichtBulletDebugDrawer::IrrlichtBulletDebugDrawer(IVideoDriver* driver_) :
    driver(driver_), debugMode(btIDebugDraw::DBG_DrawConstraints | btIDebugDraw::DBG_DrawConstraintLimits | btIDebugDraw::DBG_DrawWireframe)
{
}

IrrlichtBulletDebugDrawer::~IrrlichtBulletDebugDrawer()
{
    driver->drop();
}

void IrrlichtBulletDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
    driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);

    SMaterial m;
    m.Lighting = false;
    driver->setMaterial(m);
//    driver->draw3DLine(
//                        vector3df(0, 0, 0),
//                        vector3df(-100, 100, 20),
//                        SColor(255, 255, 255, 255));
    driver->draw3DLine(
                        vector3df(from.x(), from.y(), from.z()),
                        vector3df(to.x(), to.y(), to.z()),
                        SColor(255, 255*color.x(), 255*color.y(), 255*color.z()));

}

void IrrlichtBulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    // Just draws a line in the direction of the normal.  This could be improve.  For instance get an arrow from geometry creator.
    btVector3 tip(normalOnB);
    tip *= 10;
    tip += PointOnB;

    drawLine(PointOnB, tip, color);
}

void IrrlichtBulletDebugDrawer::reportErrorWarning(const char* warningString)
{
    std::cout << warningString << std::endl;
}

void IrrlichtBulletDebugDrawer::draw3dText(const btVector3 &location, const char *textString)
{
    std::cout << "3d text: " << textString << std::endl;
}

void IrrlichtBulletDebugDrawer::setDebugMode(int debugMode_)
{
    debugMode = debugMode_;
}

int IrrlichtBulletDebugDrawer::getDebugMode() const
{
    return debugMode;
}
