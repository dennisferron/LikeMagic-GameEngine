
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "LikeMagic/Exprs/TermDeleter.hpp"
LM_CUSTOM_DELETER(btCollisionObjectWrapper, /* do nothing */)

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"

namespace Bindings { namespace Bullet {

using LM::BlockPtr;
using LM::IMarkable;

class ScriptedContactResultCallback : public IMarkable, public btCollisionWorld::ContactResultCallback
{
public:
    ScriptedContactResultCallback(BlockPtr onAddSingleResult_, BlockPtr onNeedsCollision);
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
    BlockPtr onAddSingleResult;
    BlockPtr onNeedsCollision;
};

}}
