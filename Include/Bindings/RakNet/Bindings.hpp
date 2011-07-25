// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace Bindings { namespace RakNet {

DLL_PUBLIC void add_bindings(LikeMagic::RuntimeTypeSystem& type_sys);
void add_bindings_raknet(LikeMagic::RuntimeTypeSystem& type_sys);
void add_bindings_serializers(LikeMagic::RuntimeTypeSystem& type_sys);
void add_bindings_replicas(LikeMagic::RuntimeTypeSystem& type_sys);

}}
