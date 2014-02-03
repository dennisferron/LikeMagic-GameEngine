// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/DESteer/AddValues.hpp"

#include "LikeMagic/BindingMacros.hpp"

#include "desteer/controller/SimpleSteeringController.hpp"

using namespace std;
using namespace LM;
using namespace desteer::controller;

namespace Bindings { namespace DESteer {

void add_values()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_desteer = register_namespace("desteer", global_ns);
    auto& ns_controller = register_namespace("controller", ns_desteer);

    LM_ENUM_VALUES(ns_controller,
        (EBF_ARRIVE)
        (EBF_EVADE)
        (EBF_FLEE)
        (EBF_HIDE)
        (EBF_SEEK)
        (EBF_PURSUIT)
        (EBF_WANDER)
        (EBF_AVOID)
    )
}

}}

