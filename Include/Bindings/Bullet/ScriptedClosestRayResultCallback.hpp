
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"

namespace Bindings { namespace Bullet {

using LM::BlockPtr;
using LM::IMarkable;

class ScriptedClosestRayResultCallback : public IMarkable, public btCollisionWorld::ClosestRayResultCallback
{
public:
    ScriptedClosestRayResultCallback(BlockPtr onAddSingleResult_);
    virtual ~ScriptedClosestRayResultCallback();

    virtual void mark() const;
    virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    btScalar baseAddSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    bool test_equals(btCollisionObject* a, btCollisionObject* b) const;

private:
    BlockPtr onAddSingleResult;
};

}}
