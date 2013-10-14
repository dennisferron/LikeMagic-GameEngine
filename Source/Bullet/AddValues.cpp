// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Bullet/AddValues.hpp"

#include "LikeMagic/BindingMacros.hpp"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#include "btBulletDynamicsCommon.h"

using namespace std;
using namespace LM;

namespace Bindings { namespace Bullet {

BULLET_BINDINGS_API void add_values()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_ADD_VALUE_NAME(ns_bullet, "TAU", 2*M_PI)

    LM_ADD_VALUE_NAME(ns_bullet, "DefaultFilter", btBroadphaseProxy::DefaultFilter);
    LM_ADD_VALUE_NAME(ns_bullet, "StaticFilter", btBroadphaseProxy::StaticFilter);
    LM_ADD_VALUE_NAME(ns_bullet, "KinematicFilter", btBroadphaseProxy::KinematicFilter);
    LM_ADD_VALUE_NAME(ns_bullet, "DebrisFilter", btBroadphaseProxy::DebrisFilter);
    LM_ADD_VALUE_NAME(ns_bullet, "SensorTrigger", btBroadphaseProxy::SensorTrigger);
    LM_ADD_VALUE_NAME(ns_bullet, "CharacterFilter", btBroadphaseProxy::CharacterFilter);
    LM_ADD_VALUE_NAME(ns_bullet, "AllFilter", btBroadphaseProxy::AllFilter);

    LM_ADD_VALUE_NAME(ns_bullet, "DBG_NoDebug",  btIDebugDraw::DBG_NoDebug);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawWireframe",  btIDebugDraw::DBG_DrawWireframe);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawAabb",  btIDebugDraw::DBG_DrawAabb);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawFeaturesText",  btIDebugDraw::DBG_DrawFeaturesText);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawContactPoints",  btIDebugDraw::DBG_DrawContactPoints);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_NoDeactivation",  btIDebugDraw::DBG_NoDeactivation);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_NoHelpText",  btIDebugDraw::DBG_NoHelpText);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawText",  btIDebugDraw::DBG_DrawText);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_ProfileTimings",  btIDebugDraw::DBG_ProfileTimings);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_EnableSatComparison",  btIDebugDraw::DBG_EnableSatComparison);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DisableBulletLCP",  btIDebugDraw::DBG_DisableBulletLCP);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_EnableCCD",  btIDebugDraw::DBG_EnableCCD);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawConstraints",  btIDebugDraw::DBG_DrawConstraints);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_DrawConstraintLimits",  btIDebugDraw::DBG_DrawConstraintLimits);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_FastWireframe",  btIDebugDraw::DBG_FastWireframe);
    LM_ADD_VALUE_NAME(ns_bullet, "DBG_MAX_DEBUG_DRAW_MODE",  btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

    LM_ENUM_VALUES(ns_bullet,
        (PHY_FLOAT)
        (PHY_DOUBLE)
        (PHY_INTEGER)
        (PHY_SHORT)
        (PHY_FIXEDPOINT88)
        (PHY_UCHAR)
    )

}

}}

