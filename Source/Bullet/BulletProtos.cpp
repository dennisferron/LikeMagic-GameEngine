// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Bullet/Protos.hpp"

#include "LikeMagic/BindingMacros.hpp"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#include "btBulletDynamicsCommon.h"


using namespace std;
using namespace Iocaste::LMAdapters;
using namespace LM;

namespace Bindings { namespace Bullet {

void add_protos(IoVM& vm)
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_path = register_namespace("Bullet", global_ns);

    add_proto<double>(vm, "TAU", 2*M_PI, "Bullet", true);

    add_proto(vm, "DefaultFilter", btBroadphaseProxy::DefaultFilter);
    add_proto(vm, "StaticFilter", btBroadphaseProxy::StaticFilter);
    add_proto(vm, "KinematicFilter", btBroadphaseProxy::KinematicFilter);
    add_proto(vm, "DebrisFilter", btBroadphaseProxy::DebrisFilter);
    add_proto(vm, "SensorTrigger", btBroadphaseProxy::SensorTrigger);
    add_proto(vm, "CharacterFilter", btBroadphaseProxy::CharacterFilter);
    add_proto(vm, "AllFilter", btBroadphaseProxy::AllFilter);

    add_proto(vm, "DBG_NoDebug",  btIDebugDraw::DBG_NoDebug);
    add_proto(vm, "DBG_DrawWireframe",  btIDebugDraw::DBG_DrawWireframe);
    add_proto(vm, "DBG_DrawAabb",  btIDebugDraw::DBG_DrawAabb);
    add_proto(vm, "DBG_DrawFeaturesText",  btIDebugDraw::DBG_DrawFeaturesText);
    add_proto(vm, "DBG_DrawContactPoints",  btIDebugDraw::DBG_DrawContactPoints);
    add_proto(vm, "DBG_NoDeactivation",  btIDebugDraw::DBG_NoDeactivation);
    add_proto(vm, "DBG_NoHelpText",  btIDebugDraw::DBG_NoHelpText);
    add_proto(vm, "DBG_DrawText",  btIDebugDraw::DBG_DrawText);
    add_proto(vm, "DBG_ProfileTimings",  btIDebugDraw::DBG_ProfileTimings);
    add_proto(vm, "DBG_EnableSatComparison",  btIDebugDraw::DBG_EnableSatComparison);
    add_proto(vm, "DBG_DisableBulletLCP",  btIDebugDraw::DBG_DisableBulletLCP);
    add_proto(vm, "DBG_EnableCCD",  btIDebugDraw::DBG_EnableCCD);
    add_proto(vm, "DBG_DrawConstraints",  btIDebugDraw::DBG_DrawConstraints);
    add_proto(vm, "DBG_DrawConstraintLimits",  btIDebugDraw::DBG_DrawConstraintLimits);
    add_proto(vm, "DBG_FastWireframe",  btIDebugDraw::DBG_FastWireframe);
    add_proto(vm, "DBG_MAX_DEBUG_DRAW_MODE",  btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

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

