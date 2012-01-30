// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Interpreter/Bindings.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

//#include "Bindings/Irrlicht/Bindings.hpp"
//#include "Bindings/Bullet/Bindings.hpp"
//#include "Bindings/Custom/Bindings.hpp"
//#include "Bindings/DESteer/Bindings.hpp"

#ifdef USE_IRRKLANG
#include "Bindings/IrrKlang/Bindings.hpp"
#endif

#ifdef USE_RAKNET
#include "Bindings/RakNet/Bindings.hpp"
#include "Bindings/RakNet/Protos.hpp"
#endif

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Backends::Io;

namespace Interpreter{

void add_bindings(LikeMagic::RuntimeTypeSystem& type_sys)
{
    auto ns_bindings = Namespace::global(type_sys).subspace("Bindings");

    auto ns_irrlicht = ns_bindings.subspace("Irrlicht");
    //LM_STATIC_FUNC(ns_irrlicht, Bindings::Irrlicht, add_bindings)

    auto ns_bullet = ns_bindings.subspace("Bullet");
    //LM_STATIC_FUNC(ns_bullet, Bindings::Bullet, add_bindings)

    auto ns_custom = ns_bindings.subspace("Custom");
    //LM_STATIC_FUNC(ns_custom, Bindings::Custom, add_bindings)

    auto ns_desteer = ns_bindings.subspace("DESteer");
    //LM_STATIC_FUNC(ns_desteer, Bindings::DESteer, add_bindings)

#ifdef USE_IRRKLANG
    auto ns_irrklang = ns_bindings.subspace("IrrKlang");
    LM_STATIC_FUNC(ns_irrklang, Bindings::IrrKlang, add_bindings)
#endif

#ifdef USE_RAKNET
    //Bindings::RakNet::add_bindings(type_sys);
    auto ns_raknet = ns_bindings.subspace("RakNet");
    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_bindings)
    LM_STATIC_FUNC(ns_raknet, Bindings::RakNet, add_protos)
#endif

}

}
