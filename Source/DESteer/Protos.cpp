// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/DESteer/Protos.hpp"

#include "LikeMagic/BindingMacros.hpp"

#include "desteer/controller/SimpleSteeringController.hpp"

using namespace std;
using namespace Iocaste::LMAdapters;
using namespace desteer::controller;

namespace Bindings { namespace DESteer {

void add_protos(IoVM& vm)
{
    LM_ENUM_PROTOS(vm,
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

