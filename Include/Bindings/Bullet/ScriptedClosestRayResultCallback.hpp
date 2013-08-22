
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

namespace Bindings { namespace Bullet {

using Iocaste::LMAdapters::IoBlock;
using LM::IMarkable;

class ScriptedClosestRayResultCallback : public IMarkable, public btCollisionWorld::ClosestRayResultCallback
{
public:
    ScriptedClosestRayResultCallback(IoBlock onAddSingleResult_);
    virtual ~ScriptedClosestRayResultCallback();

    virtual void mark() const;
    virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    btScalar baseAddSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    bool test_equals(btCollisionObject* a, btCollisionObject* b) const;

private:
    IoBlock onAddSingleResult;
};

}}
