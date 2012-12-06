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

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace TPS;

namespace Bindings { namespace ThinPlateSpline {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_tps = Namespace::global(type_sys).subspace("TPS");

    LM_CLASS(ns_tps, Vec)
    LM_FIELD(Vec, (x)(y)(z))
    LM_CONSTR(Vec,,)
    LM_CONSTR(Vec,,float,float,float)
    LM_CONSTR(Vec,,Vec const&)
    LM_FUNC(Vec,(norm)(len))
    LM_OP(Vec,(+=)(+)(-=)(*=)(*)(/=)(/)(==))
    LM_OP_OVERLOAD(Vec, const, -, Vec)
    LM_OP_OVERLOAD(Vec, const, -, Vec, Vec const&)

    LM_CLASS(ns_tps, ControlPoint)
    LM_CONSTR(ControlPoint,, Vec const&)
    LM_FIELD(ControlPoint,(pos))

    LM_CLASS(ns_tps, ControlPointPtr)
    LM_FUNC(ControlPointPtr, (get))

    typedef ::TPS::ThinPlateSpline ThinPlateSpline;
    LM_CLASS(ns_tps, ThinPlateSpline)

    LM_CLASS(ns_tps, ThinPlateQuilt)
    LM_CONSTR(ThinPlateQuilt,,int,int,Vec,Vec)
    LM_FUNC(ThinPlateQuilt,
        (heightAt)(addControlPoint)(getControlPoint)
        (numControlPoints)(removeControlPoint)
        (getRegularization)(addRegularization)
        (getBendingEnergy)(refresh)
        (clearControlPoints))
}

}}
