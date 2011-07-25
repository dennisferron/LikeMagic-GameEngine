// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/RakNet/Bindings.hpp"
#include "Bindings/RakNet/Protos.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"
using namespace LikeMagic;

namespace Bindings { namespace RakNet {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_raknet = Namespace::global(type_sys).subspace("Bindings").subspace("RakNet");

    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_bindings_raknet)
    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_bindings_serializers)
    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_bindings_replicas)

    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_protos)
}

}}
