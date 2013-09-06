#pragma once
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/controller/SimpleSteeringController.hpp"

//#define ScriptFunc(IsVoid, RType, FuncName, CONST, ArgTypes)
#include "LikeMagic/Utility/ScriptFunc.hpp"

namespace desteer {
namespace entity {

class ScriptedEntitySpace : virtual public LM::MarkableObjGraph, public IEntitySpace
{
public:
    ScriptFunc_R(irr::core::vector3df, SideVector,                     const,)
	ScriptFunc_void(SetSideVector,              /* not const */,    (irr::core::vector3df))
	ScriptFunc_R(irr::core::vector3df, ForwardVector,                  const,)
	ScriptFunc_void(SetForwardVector,           /* not const */,    (irr::core::vector3df))
    ScriptFunc_R(irr::core::vector3df, transformWorldVectToLocal,  /* not const */,    (irr::core::vector3df))
	ScriptFunc_R(irr::core::vector3df, transformLocalVectToWorld,  /* not const */,    (irr::core::vector3df))
};

}//end namespace entity
}//end namespace desteer
