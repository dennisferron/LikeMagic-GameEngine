
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"

namespace Bindings { namespace Bullet {

using LM::BlockPtr;
using LM::IMarkable;

class ScriptedWorldManager : public IMarkable
{
public:
    ScriptedWorldManager();
    virtual ~ScriptedWorldManager();
    virtual void mark() const;

    void setOnTick(btDynamicsWorld& world, BlockPtr onTick_);
    void setOnPreTick(btDynamicsWorld& world, BlockPtr onPreTick_);

private:
    BlockPtr onPreTick;
    BlockPtr onTick;

    static void static_tick_callback(btDynamicsWorld *world, btScalar timeStep);
    void tick_callback(btDynamicsWorld *world, btScalar timeStep);

    static void static_pretick_callback(btDynamicsWorld *world, btScalar timeStep);
    void pretick_callback(btDynamicsWorld *world, btScalar timeStep);
};

}}
