#include "Bindings/Bullet/ScriptedWorldManager.hpp"

using namespace Bindings::Bullet;



ScriptedWorldManager::ScriptedWorldManager() {}


void ScriptedWorldManager::setOnTick(btDynamicsWorld& world, IoBlock onTick_)
{
    onTick = onTick_;
    world.setInternalTickCallback(static_tick_callback, this, false);
}

void ScriptedWorldManager::setOnPreTick(btDynamicsWorld& world, IoBlock onPreTick_)
{
    onPreTick = onPreTick_;
    world.setInternalTickCallback(static_pretick_callback, this, true);
}

void ScriptedWorldManager::static_tick_callback(btDynamicsWorld *world, btScalar timeStep)
{
    static_cast<ScriptedWorldManager*>(world->getWorldUserInfo())->tick_callback(world, timeStep);
}

void ScriptedWorldManager::tick_callback(btDynamicsWorld *world, btScalar timeStep)
{
    // For testing
    static int count = 0;
    if (++count % 1 != 0)
        return;

    if (!onTick.empty())
        onTick(world, timeStep);
}

void ScriptedWorldManager::static_pretick_callback(btDynamicsWorld *world, btScalar timeStep)
{
    static_cast<ScriptedWorldManager*>(world->getWorldUserInfo())->pretick_callback(world, timeStep);
}

void ScriptedWorldManager::pretick_callback(btDynamicsWorld *world, btScalar timeStep)
{
    if (!onPreTick.empty())
        onPreTick(world, timeStep);
}

void ScriptedWorldManager::mark() const
{
    onTick.mark();
    onPreTick.mark();
}
