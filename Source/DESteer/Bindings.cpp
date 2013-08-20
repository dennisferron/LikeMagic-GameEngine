// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/DESteer/Bindings.hpp"
#include "Bindings/DESteer/Protos.hpp"

#include "LikeMagic/BindingMacros.hpp"

#include "Bindings/DESteer/ScriptedBaseEntity.hpp"
#include "Bindings/DESteer/ScriptedMobileEntity.hpp"

#include "desteer/Types.hpp"
#include "desteer/entity/IMobileEntity.hpp"
#include "desteer/controller/SimpleSteeringController.hpp"

using namespace LikeMagic;

using namespace desteer;
using namespace desteer::entity;
using namespace desteer::controller;
using namespace desteer::behavior;

#include "LikeMagic/TypeConv/NumberConv.hpp"

namespace Bindings { namespace DESteer {

void add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bindings = register_namespace("Bindings", global_ns);
    TypeMirror& ns_bindings_desteer = register_namespace("desteer", ns_bindings);

    LM_STATIC_FUNC_NAME(ns_bindings, "add_protos", Bindings::DESteer::add_protos)

    TypeMirror& ns_desteer = register_namespace("desteer", global_ns);

    LM_CLASS(ns_desteer, BehaviorGroup)
    LM_CLASS(ns_desteer, BehaviorIterator)
    LM_CLASS(ns_desteer, MobGroup)
    LM_CLASS(ns_desteer, MobIterator)

    LM_CLASS(ns_desteer, EntityGroup)
    LM_CONSTR(EntityGroup, "new")
    LM_FUNC(EntityGroup, (size)(clear))
    LM_FUNC_OVERLOAD(EntityGroup, "push_back", push_back, void, EntityGroup::value_type const&)
    LM_FUNC_OVERLOAD_BOTH(EntityGroup, at, IBaseEntity*&, EntityGroup::size_type)

    LM_CLASS(ns_desteer, EntityIterator)
    LM_OP_OVERLOAD(EntityIterator, , ++, EntityIterator, int) // Can only overload postfix ++ in Io)
    //LM_FUNC_OVERLOAD(EntityIterator, "next" , operator ++, EntityIterator) // So overload the prefix ++ as a "next" method.

    auto& ns_entity = register_namespace("entity", ns_desteer);

    LM_CLASS(ns_entity, IBaseEntity)

    LM_FUNC(IBaseEntity,
        (Position)
        (SetPosition)
        (Radius)
        (Update)
    )

    LM_CLASS(ns_entity, IEntitySpace)

    LM_FUNC(IEntitySpace,
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)
    )

    LM_CLASS(ns_entity, IMobileEntity)
    LM_BASE(IMobileEntity, IBaseEntity)
    LM_BASE(IMobileEntity, IEntitySpace)

    LM_FUNC(IMobileEntity,
        (SetSteering)
        (Mass)
        (SetMass)
        (MaxForce)
        (SetMaxForce)
        (MaxSpeed)
        (SetMaxSpeed)
        (Velocity)
    )

    LM_CLASS(ns_entity, ScriptedBaseEntity)
    LM_BASE(ScriptedBaseEntity, IBaseEntity)
    LM_CONSTR(ScriptedBaseEntity, "new")

    LM_BLOCK(ScriptedBaseEntity,
        (Position)
        (SetPosition)
        (Radius)
        (Update)
    )

    LM_CLASS(ns_entity, ScriptedEntitySpace)
    LM_BASE(ScriptedEntitySpace, IEntitySpace)
    LM_CONSTR(ScriptedEntitySpace, "new")

    LM_BLOCK(ScriptedEntitySpace,
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)
    )

    LM_CLASS(global_ns, MarkableObjGraph)

    LM_CLASS(ns_entity, ScriptedMobileEntity)
    LM_BASE(ScriptedMobileEntity, IMobileEntity)
    LM_BASE(ScriptedMobileEntity, IBaseEntity)
    LM_BASE(ScriptedMobileEntity, MarkableObjGraph)
    LM_CONSTR(ScriptedMobileEntity, "new")

    LM_FUNC(ScriptedMobileEntity,
        (Position)
    )

    // There's something strange about the conversion from
    // ScriptedMobileEntity*& to IBaseEntity* const&.
    // I would expect the conversion path to be automatically discovered
    // but it is not.  It might have something to do with the fact
    // that when you try to code the conversion directly you get
    // a warning about returning a reference to a temporary.
    // Apparently casting ScriptedMobileEntity to its base
    // creates a temporary pointer value (probably because of
    // the multiple inheritance in its inheritance tree).
    // To avoid the warning, I'm using NumberConv which
    // caches the temporary copy of the value so there
    // will be something persistent for the reference to refer to.
    add_conv<ScriptedMobileEntity*&, IBaseEntity* const&, LikeMagic::TypeConv::NumberConv>();

    LM_BLOCK(ScriptedMobileEntity,

        // IBaseEntity
        (Position)
        (SetPosition)
        (Radius)
        (Update)

        // IEntitySpace
        (SideVector)
        (SetSideVector)
        (ForwardVector)
        (SetForwardVector)
        (transformWorldVectToLocal)
        (transformLocalVectToWorld)

        // IMobileEntity
        (SetSteering)
        (Mass)
        (SetMass)
        (MaxForce)
        (SetMaxForce)
        (MaxSpeed)
        (SetMaxSpeed)
        (Velocity)
    )

    auto& ns_controller = register_namespace("controller", ns_desteer);

    LM_CLASS(ns_controller, ISteeringController)
    LM_FUNC(ISteeringController, (Calculate))

    LM_CLASS(ns_controller, SimpleSteeringController)
    LM_BASE(SimpleSteeringController, ISteeringController)
    LM_CONSTR(SimpleSteeringController, "new", entity::IMobileEntity*)

    LM_FUNC(SimpleSteeringController,
        (SetBehaviorFlag)
        (SetSeekTarget)
        (SetArriveTarget)
        (SetHideTarget)
        (SetPursuitTarget)
        (SetObstacles)
    )

    // Values of the enum are defined in protos
    LM_ENUM(ns_controller, EBEHAVIOR_FLAG)

    auto& ns_behavior = register_namespace("behavior", ns_desteer);

}

}}
