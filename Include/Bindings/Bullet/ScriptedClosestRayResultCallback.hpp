
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"

namespace Bindings { namespace Bullet {

using LikeMagic::Backends::Io::IoBlock;
using LikeMagic::IMarkable;

class ScriptedClosestRayResultCallback : public IMarkable, public btCollisionWorld::ClosestRayResultCallback
{
public:
    ScriptedClosestRayResultCallback(IoBlock onAddSingleResult_);

    virtual void mark() const;
    virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    btScalar baseAddSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace);
    bool test_equals(btCollisionObject* a, btCollisionObject* b) const;

private:
    IoBlock onAddSingleResult;
};

}}
