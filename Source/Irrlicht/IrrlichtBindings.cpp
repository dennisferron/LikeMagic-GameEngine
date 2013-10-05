// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"

using namespace LM;

namespace Bindings { namespace Irrlicht {

void add_bindings()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bindings = register_namespace("Bindings", global_ns);
    TypeMirror& ns_irrlicht = register_namespace("Irrlicht", ns_bindings);

    LM_STATIC_FUNC_NAME(ns_irrlicht, "add_values_irr", Bindings::Irrlicht::add_values_irr)

    add_bindings_irr();
    add_bindings_gui();
    add_bindings_video();
    add_bindings_scene();
    add_bindings_core();
    add_bindings_custom();
    add_bindings_irr_io();
}

}}
