// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Bullet/Protos.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#include "btBulletDynamicsCommon.h"


using namespace std;
using namespace Iocaste::LikeMagicAdapters;

namespace Bindings { namespace Bullet {

DLL_PUBLIC void add_protos(IoVM& vm)
{
    auto ns_path = LikeMagic::NamespacePath::global().subspace("Bullet");

    vm.add_proto<double>("TAU", 2*M_PI, ns_path, true);

    vm.add_proto("DefaultFilter", btBroadphaseProxy::DefaultFilter);
    vm.add_proto("StaticFilter", btBroadphaseProxy::StaticFilter);
    vm.add_proto("KinematicFilter", btBroadphaseProxy::KinematicFilter);
    vm.add_proto("DebrisFilter", btBroadphaseProxy::DebrisFilter);
    vm.add_proto("SensorTrigger", btBroadphaseProxy::SensorTrigger);
    vm.add_proto("CharacterFilter", btBroadphaseProxy::CharacterFilter);
    vm.add_proto("AllFilter", btBroadphaseProxy::AllFilter);

    vm.add_proto("DBG_NoDebug",  btIDebugDraw::DBG_NoDebug);
    vm.add_proto("DBG_DrawWireframe",  btIDebugDraw::DBG_DrawWireframe);
    vm.add_proto("DBG_DrawAabb",  btIDebugDraw::DBG_DrawAabb);
    vm.add_proto("DBG_DrawFeaturesText",  btIDebugDraw::DBG_DrawFeaturesText);
    vm.add_proto("DBG_DrawContactPoints",  btIDebugDraw::DBG_DrawContactPoints);
    vm.add_proto("DBG_NoDeactivation",  btIDebugDraw::DBG_NoDeactivation);
    vm.add_proto("DBG_NoHelpText",  btIDebugDraw::DBG_NoHelpText);
    vm.add_proto("DBG_DrawText",  btIDebugDraw::DBG_DrawText);
    vm.add_proto("DBG_ProfileTimings",  btIDebugDraw::DBG_ProfileTimings);
    vm.add_proto("DBG_EnableSatComparison",  btIDebugDraw::DBG_EnableSatComparison);
    vm.add_proto("DBG_DisableBulletLCP",  btIDebugDraw::DBG_DisableBulletLCP);
    vm.add_proto("DBG_EnableCCD",  btIDebugDraw::DBG_EnableCCD);
    vm.add_proto("DBG_DrawConstraints",  btIDebugDraw::DBG_DrawConstraints);
    vm.add_proto("DBG_DrawConstraintLimits",  btIDebugDraw::DBG_DrawConstraintLimits);
    vm.add_proto("DBG_FastWireframe",  btIDebugDraw::DBG_FastWireframe);
    vm.add_proto("DBG_MAX_DEBUG_DRAW_MODE",  btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

    LM_ENUM_PROTOS(vm,
        (PHY_FLOAT)
        (PHY_DOUBLE)
        (PHY_INTEGER)
        (PHY_SHORT)
        (PHY_FIXEDPOINT88)
        (PHY_UCHAR)
    )

}

}}

