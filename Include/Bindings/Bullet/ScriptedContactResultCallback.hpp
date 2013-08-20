
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/Exprs/TermDeleter.hpp"
LM_CUSTOM_DELETER(btCollisionObjectWrapper*, /* do nothing */)
LM_CUSTOM_DELETER(btCollisionObjectWrapper const*, /* do nothing */)

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
    virtual ~ScriptedContactResultCallback();

    virtual void mark() const;
    bool baseNeedsCollision(btBroadphaseProxy* proxy) const;

    virtual bool needsCollision(btBroadphaseProxy* proxy) const;

    /* Old signature
	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult(btManifoldPoint& cp,
                                    const btCollisionObject* colObj0,int partId0,int index0,
                                    const btCollisionObject* colObj1,int partId1,int index1);
    */

	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
    virtual	btScalar addSingleResult(btManifoldPoint& cp,
                                    const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
                                    const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1);

private:
    IoBlock onAddSingleResult;
    IoBlock onNeedsCollision;
};

}}
