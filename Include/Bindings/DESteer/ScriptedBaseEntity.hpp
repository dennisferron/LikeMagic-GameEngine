#pragma once
#include "desteer/entity/IBaseEntity.hpp"

//#define ScriptFunc(IsVoid, RType, FuncName, CONST, ArgTypes)
#include "LikeMagic/Utility/ScriptFunc.hpp"

namespace desteer{
namespace entity {

class ScriptedBaseEntity : virtual public LM::MarkableObjGraph, public IBaseEntity
{
public:

    ScriptFunc_R(irr::core::vector3df, Position,           const,          )
    ScriptFunc_void(SetPosition,    /* not const */,    (irr::core::vector3df))
    ScriptFunc_R(float,                Radius,             const,          )
    ScriptFunc_void(Update,         /* not const */,    (float))
};

}//end namespace entity
}//end namespace desteer

