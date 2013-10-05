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
using namespace LM;

namespace Bindings { namespace Bullet {

void add_values(LangInterpreter& vm)
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_path = register_namespace("Bullet", global_ns);

    vm.add_value("TAU", 2*M_PI, "Bullet", true);

    vm.add_value("DefaultFilter", btBroadphaseProxy::DefaultFilter);
    vm.add_value("StaticFilter", btBroadphaseProxy::StaticFilter);
    vm.add_value("KinematicFilter", btBroadphaseProxy::KinematicFilter);
    vm.add_value("DebrisFilter", btBroadphaseProxy::DebrisFilter);
    vm.add_value("SensorTrigger", btBroadphaseProxy::SensorTrigger);
    vm.add_value("CharacterFilter", btBroadphaseProxy::CharacterFilter);
    vm.add_value("AllFilter", btBroadphaseProxy::AllFilter);

    vm.add_value("DBG_NoDebug",  btIDebugDraw::DBG_NoDebug);
    vm.add_value("DBG_DrawWireframe",  btIDebugDraw::DBG_DrawWireframe);
    vm.add_value("DBG_DrawAabb",  btIDebugDraw::DBG_DrawAabb);
    vm.add_value("DBG_DrawFeaturesText",  btIDebugDraw::DBG_DrawFeaturesText);
    vm.add_value("DBG_DrawContactPoints",  btIDebugDraw::DBG_DrawContactPoints);
    vm.add_value("DBG_NoDeactivation",  btIDebugDraw::DBG_NoDeactivation);
    vm.add_value("DBG_NoHelpText",  btIDebugDraw::DBG_NoHelpText);
    vm.add_value("DBG_DrawText",  btIDebugDraw::DBG_DrawText);
    vm.add_value("DBG_ProfileTimings",  btIDebugDraw::DBG_ProfileTimings);
    vm.add_value("DBG_EnableSatComparison",  btIDebugDraw::DBG_EnableSatComparison);
    vm.add_value("DBG_DisableBulletLCP",  btIDebugDraw::DBG_DisableBulletLCP);
    vm.add_value("DBG_EnableCCD",  btIDebugDraw::DBG_EnableCCD);
    vm.add_value("DBG_DrawConstraints",  btIDebugDraw::DBG_DrawConstraints);
    vm.add_value("DBG_DrawConstraintLimits",  btIDebugDraw::DBG_DrawConstraintLimits);
    vm.add_value("DBG_FastWireframe",  btIDebugDraw::DBG_FastWireframe);
    vm.add_value("DBG_MAX_DEBUG_DRAW_MODE",  btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

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

