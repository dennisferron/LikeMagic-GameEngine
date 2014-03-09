// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/ThinPlateSpline/TPSValues.hpp"

#include "LikeMagic/BindingMacros.hpp"

using namespace std;
using namespace LM;

namespace Bindings { namespace ThinPlateSpline {

MESHTOOLS_BINDINGS_API void add_values()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_tps = register_namespace("TPS", global_ns);
}

}}

