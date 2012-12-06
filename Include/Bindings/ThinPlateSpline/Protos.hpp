// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LikeMagic { class RuntimeTypeSystem; }

namespace Iocaste { namespace LikeMagicAdapters {
    class IoVM;
}}

namespace Bindings { namespace Irrlicht {

DLL_PUBLIC void add_protos(Iocaste::LikeMagicAdapters::IoVM&, LikeMagic::RuntimeTypeSystem&);

}}
