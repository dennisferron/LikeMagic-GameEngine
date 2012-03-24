// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Irrlicht {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_irrlicht = Namespace::global(type_sys).subspace("Bindings").subspace("Irrlicht");

    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_irr)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_gui)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_video)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_scene)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_core)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_custom)
    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings_irr_io)

    LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_protos_irr)
}

}}
