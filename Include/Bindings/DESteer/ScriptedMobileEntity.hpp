#pragma once

#include "desteer/entity/IMobileEntity.hpp"
#include "Bindings/DESteer/ScriptedBaseEntity.hpp"
#include "Bindings/DESteer/ScriptedEntitySpace.hpp"

//#define ScriptFunc(IsVoid, RType, FuncName, CONST, ArgTypes)
#include "LikeMagic/Utility/ScriptFunc.hpp"

namespace desteer {
namespace entity {

class ScriptedMobileEntity : public IMobileEntity, public LM::MarkableObjGraph
{
public:

    // For some reason deriving from ScriptedBaseEntity and ScriptedMobile entity did
    // not count as an implementation of the abstract functions in the interfaces
    // those two implement.  It's a C++ quirk I wasn't aware of.  Rather than
    // fight it it is just easier to define all the interface functions here:

    // IBaseEntity Functions
    ScriptFunc_R(irr::core::vector3df, Position,           const,          )
    ScriptFunc_void(                 SetPosition,    /* not const */,    (irr::core::vector3df))
    ScriptFunc_R(float,                Radius,             const,          )
    ScriptFunc_void(                 Update,         /* not const */,    (float))

    // IEntitySpace Functions
    ScriptFunc_R(irr::core::vector3df, SideVector,                     const,)
	ScriptFunc_void(                 SetSideVector,              /* not const */,    (irr::core::vector3df))
	ScriptFunc_R(irr::core::vector3df, ForwardVector,                  const,)
	ScriptFunc_void(                 SetForwardVector,           /* not const */,    (irr::core::vector3df))
    ScriptFunc_R(irr::core::vector3df, transformWorldVectToLocal,  /* not const */,    (irr::core::vector3df))
	ScriptFunc_R(irr::core::vector3df, transformLocalVectToWorld,  /* not const */,    (irr::core::vector3df))

    // IMobile Entity Functions
	ScriptFunc_void(                 SetSteering,                /* not const */,    (controller::ISteeringController*) )
    ScriptFunc_R(float,                Mass,                           const, )
	ScriptFunc_void(                 SetMass,                    /* not const */,    (float) )
	ScriptFunc_R(float,                MaxForce,                       const, )
	ScriptFunc_void(                 SetMaxForce,                /* not const */,    (float) )
	ScriptFunc_R(float,                MaxSpeed,                       const, )
	ScriptFunc_void(                 SetMaxSpeed,                /* not const */,    (float) )
    ScriptFunc_R(irr::core::vector3df, Velocity,                       const,  )
};

}//end namespace entity
}//end namespace desteer
