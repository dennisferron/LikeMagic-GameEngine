// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Irrlicht/ScriptedDataSerializer.hpp"

#include <irrlicht.h>

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;
using namespace irr;
using namespace irr::io;

namespace Bindings { namespace Irrlicht {

void add_bindings_irr_io()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_irr = register_namespace("irr", global_ns);
    TypeMirror& ns_irr_io = register_namespace("io", ns_irr);

    LM_CLASS(ns_irr_io, IAttributes)

    LM_CLASS(ns_irr_io, ISceneUserDataSerializer)
    LM_FUNC(ISceneUserDataSerializer, (OnCreateNode)(OnReadUserData)(createUserData))

    LM_CLASS(ns_irr_io, ScriptedDataSerializer)
    LM_BASE(ScriptedDataSerializer, ISceneUserDataSerializer)
    LM_FIELD(ScriptedDataSerializer, (on_OnCreateNode)(on_OnReadUserData)(on_createUserData))


}

}}
