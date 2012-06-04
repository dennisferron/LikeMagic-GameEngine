// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Irrlicht/ScriptedSceneNode.hpp"
#include "Bindings/Irrlicht/ScriptedEventReceiver.hpp"

#include <irrlicht.h>

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace irr;
using namespace irr::scene;

namespace Bindings { namespace Irrlicht {

void add_bindings_custom(RuntimeTypeSystem& type_sys)
{
    add_bindings_orientation(type_sys);

    auto ns_irr_custom = Namespace::global(type_sys).subspace("irr").subspace("custom");

    LM_CLASS(ns_irr_custom, ISceneNode)

    LM_CLASS(ns_irr_custom, ScriptedSceneNode)
    LM_BASE(ScriptedSceneNode, ISceneNode)
    LM_CONSTR(ScriptedSceneNode, "new", scene::ISceneNode*, scene::ISceneManager*, s32)
    LM_FUNC(ScriptedSceneNode, (setOnRegisterSceneNode)(setOnRender)(setOnGetBoundingBox)(setOnGetMaterial)(setOnGetMaterialCount)
            (getExampleIndices)(getExampleVertices))

    LM_CLASS(ns_irr_custom, IEventReceiver)

    LM_CLASS(ns_irr_custom, ScriptedEventReceiver)
    LM_BASE(ScriptedEventReceiver, IEventReceiver)
    LM_CONSTR(ScriptedEventReceiver,, IoBlock)
    LM_FUNC(ScriptedEventReceiver, (setOnEvent)(OnEvent)(isKeyDown))
}

}}
