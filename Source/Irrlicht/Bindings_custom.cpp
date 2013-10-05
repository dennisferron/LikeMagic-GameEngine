// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Irrlicht/ScriptedSceneNode.hpp"
#include "Bindings/Irrlicht/ScriptedEventReceiver.hpp"

#include <irrlicht.h>

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;
using namespace irr;
using namespace irr::scene;

namespace Bindings { namespace Irrlicht {

void add_bindings_custom()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_irr = register_namespace("irr", global_ns);
    TypeMirror& ns_irr_custom = register_namespace("custom", ns_irr);

    add_bindings_orientation();

    LM_CLASS(ns_irr_custom, ISceneNode)

    LM_CLASS(ns_irr_custom, ScriptedSceneNode)
    LM_BASE(ScriptedSceneNode, ISceneNode)
    LM_CONSTR(ScriptedSceneNode, "new", scene::ISceneNode*, scene::ISceneManager*, s32)
    LM_FUNC(ScriptedSceneNode, (setOnRegisterSceneNode)(setOnRender)(setOnGetBoundingBox)(setOnGetMaterial)(setOnGetMaterialCount)
            (getExampleIndices)(getExampleVertices))

    LM_CLASS(ns_irr_custom, IEventReceiver)

    LM_CLASS(ns_irr_custom, ScriptedEventReceiver)
    LM_BASE(ScriptedEventReceiver, IEventReceiver)
    LM_CONSTR(ScriptedEventReceiver, "new", BlockPtr)
    LM_FUNC(ScriptedEventReceiver, (setOnEvent)(OnEvent)(isKeyDown))
}

}}
