#include "Bindings/Bullet/ScriptedContactResultCallback.hpp"

using namespace Bindings::Bullet;

ScriptedContactResultCallback::ScriptedContactResultCallback(IoBlock onAddSingleResult_, IoBlock onNeedsCollision_)
    : onAddSingleResult(onAddSingleResult_), onNeedsCollision(onNeedsCollision_)
{
}

void ScriptedContactResultCallback::mark() const
{
    onAddSingleResult.mark();
    onNeedsCollision.mark();
}

btScalar ScriptedContactResultCallback::addSingleResult(btManifoldPoint& cp,
		const btCollisionObject* colObj0,int partId0,int index0,
		const btCollisionObject* colObj1,int partId1,int index1)
{
    return onAddSingleResult.eval<btScalar>(cp, colObj0, partId0, index0, colObj1, partId1, index1);
}

bool ScriptedContactResultCallback::needsCollision(btBroadphaseProxy* proxy) const
{
    return onNeedsCollision.eval<bool>(proxy);
}

bool ScriptedContactResultCallback::baseNeedsCollision(btBroadphaseProxy* proxy) const
{
    return btCollisionWorld::ContactResultCallback::needsCollision(proxy);
}
