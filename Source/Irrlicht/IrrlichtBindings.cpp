// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Irrlicht/IrrlichtValues.hpp"

namespace Bindings { namespace Irrlicht {

IRRLICHT_BINDINGS_API void add_bindings()
{
    add_bindings_irr();
    add_bindings_gui();
    add_bindings_video();
    add_bindings_scene();
    add_bindings_core();
    add_bindings_custom();
    add_bindings_irr_io();
    add_values();
}

}}
