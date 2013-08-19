// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LikeMagic { class RuntimeTypeSystem; }

namespace Iocaste { namespace LikeMagicAdapters {
}}


namespace Bindings { namespace Irrlicht {

void add_bindings();

void add_bindings_irr();
void add_bindings_gui();
void add_bindings_video();
void add_bindings_scene();
void add_bindings_core();
void add_bindings_custom();
void add_bindings_irr_io();

void add_bindings_orientation();

void add_protos_irr(Iocaste::LikeMagicAdapters::IoVM& vm);

}}
