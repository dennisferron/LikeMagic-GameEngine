#include "Bindings/Bullet/ScriptedClosestRayResultCallback.hpp"

using namespace Bindings::Bullet;

ScriptedClosestRayResultCallback::ScriptedClosestRayResultCallback(IoBlock onAddSingleResult_)
    : btCollisionWorld::ClosestRayResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0)),
        onAddSingleResult(onAddSingleResult_)
{
}

btScalar ScriptedClosestRayResultCallback::addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
{
    return onAddSingleResult.eval<btScalar>(rayResult, normalInWorldSpace);
}

btScalar ScriptedClosestRayResultCallback::baseAddSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
{
    return ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
}

void ScriptedClosestRayResultCallback::mark() const
{
    onAddSingleResult.mark();
}

bool ScriptedClosestRayResultCallback::test_equals(btCollisionObject* a, btCollisionObject* b) const
{
    return a == b;
}
