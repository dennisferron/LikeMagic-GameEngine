
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"

namespace Bindings { namespace Bullet {

using LikeMagic::Backends::Io::IoBlock;
using LikeMagic::IMarkable;

class ScriptedWorldManager : public IMarkable
{
public:
    ScriptedWorldManager();
    virtual void mark() const;

    void setOnTick(btDynamicsWorld& world, IoBlock onTick_);
    void setOnPreTick(btDynamicsWorld& world, IoBlock onPreTick_);

private:
    IoBlock onPreTick;
    IoBlock onTick;

    static void static_tick_callback(btDynamicsWorld *world, btScalar timeStep);
    void tick_callback(btDynamicsWorld *world, btScalar timeStep);

    static void static_pretick_callback(btDynamicsWorld *world, btScalar timeStep);
    void pretick_callback(btDynamicsWorld *world, btScalar timeStep);
};

}}
