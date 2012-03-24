
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

namespace Bindings { namespace Bullet {

using Iocaste::LikeMagicAdapters::IoBlock;
using LikeMagic::IMarkable;

class ScriptedContactResultCallback : public IMarkable, public btCollisionWorld::ContactResultCallback
{
public:
    ScriptedContactResultCallback(IoBlock onAddSingleResult_, IoBlock onNeedsCollision);

    virtual void mark() const;
    bool baseNeedsCollision(btBroadphaseProxy* proxy) const;

    virtual bool needsCollision(btBroadphaseProxy* proxy) const;

	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult(btManifoldPoint& cp,
                                    const btCollisionObject* colObj0,int partId0,int index0,
                                    const btCollisionObject* colObj1,int partId1,int index1);

private:
    IoBlock onAddSingleResult;
    IoBlock onNeedsCollision;
};

}}
