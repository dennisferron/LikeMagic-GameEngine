// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/OrientationHelperSceneNode.hpp"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

namespace Bindings { namespace Irrlicht {

void add_bindings_orientation()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_irr = register_namespace("irr", global_ns);
    TypeMirror& ns_irr_scene = register_namespace("scene", ns_irr);

    LM_CLASS(ns_irr_scene, ISceneNode)

    TypeMirror& ns_irr_custom = register_namespace("custom", ns_irr);

    LM_CLASS(ns_irr_custom, OrientationHelperSceneNode)
    LM_BASE(OrientationHelperSceneNode, ISceneNode)
    LM_CONSTR(OrientationHelperSceneNode, "new", f32,scene::ISceneNode*, scene::ISceneManager*, s32)
    LM_FUNC_OVERLOAD(OrientationHelperSceneNode, "rotateZToDirectionVectorVector", rotateZToDirection,
        void, const core::vector3df &, const core::vector3df &
    )
    LM_FUNC_OVERLOAD(OrientationHelperSceneNode, "rotateZToDirectionCameraVector", rotateZToDirection,
        void, const scene::ICameraSceneNode *, const core::vector3df &
	)
    LM_FUNC_OVERLOAD(OrientationHelperSceneNode, "rotateZToDirectionCamera", rotateZToDirection,
        void, const scene::ICameraSceneNode *
    )
}

}}

