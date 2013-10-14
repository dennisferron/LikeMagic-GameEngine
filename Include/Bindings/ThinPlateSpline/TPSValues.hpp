// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Bindings/Custom/MeshToolsBindingsDLL.hpp"

namespace LM { class RuntimeTypeSystem; }

namespace LM {
    class LangInterpreter;
}

namespace Bindings { namespace Irrlicht {

MESHTOOLS_BINDINGS_API void add_values(LM::LangInterpreter&, LM::RuntimeTypeSystem&);

}}
