// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/ThinPlateSpline/Bindings.hpp"
#include "Bindings/ThinPlateSpline/Protos.hpp"

#include "ThinPlateSpline/ThinPlateQuilt.hpp"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;
using namespace TPS;

namespace Bindings { namespace ThinPlateSpline {

void add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_tps = register_namespace("TPS", global_ns);

    LM_CLASS(ns_tps, Vec)
    LM_FIELD(Vec, (x)(y)(z))
    LM_CONSTR(Vec,"new")
    LM_CONSTR(Vec, "new",float,float,float)
    LM_CONSTR(Vec, "new",Vec const&)
    LM_FUNC(Vec,(norm)(len))
    LM_OP(Vec,(+=)(+)(-=)(*=)(*)(/=)(/)(==))
    LM_OP_OVERLOAD(Vec, const, -, Vec)
    LM_OP_OVERLOAD(Vec, const, -, Vec, Vec const&)

    LM_CLASS(ns_tps, ControlPoint)
    LM_CONSTR(ControlPoint, "new", Vec const&)
    LM_FIELD(ControlPoint,(pos))

    LM_CLASS(ns_tps, ControlPointPtr)
    LM_FUNC(ControlPointPtr, (get))

    typedef ::TPS::ThinPlateSpline ThinPlateSpline;
    LM_CLASS(ns_tps, ThinPlateSpline)

    LM_CLASS(ns_tps, ThinPlateQuilt)
    LM_CONSTR(ThinPlateQuilt, "new",int,int,Vec,Vec)
    LM_FUNC(ThinPlateQuilt,
        (heightAt)(addControlPoint)(getControlPoint)
        (numControlPoints)(removeControlPoint)
        (getRegularization)(addRegularization)
        (getBendingEnergy)(refresh)
        (clearControlPoints))
}

}}
