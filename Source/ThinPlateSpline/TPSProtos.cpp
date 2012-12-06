// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/ThinPlateSpline/Protos.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"


using namespace std;
using namespace Iocaste::LikeMagicAdapters;

namespace Bindings { namespace ThinPlateSpline {

DLL_PUBLIC void add_protos(IoVM& vm)
{
    auto ns_path = LikeMagic::NamespacePath::global().subspace("TPS");
}

}}

