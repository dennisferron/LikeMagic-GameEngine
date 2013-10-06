// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Interpreter/Bindings.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/IrrKlang/Bindings.hpp"
#include "Bindings/Bullet/Bindings.hpp"
#include "Bindings/Custom/Bindings.hpp"
#include "Bindings/DESteer/Bindings.hpp"
#include "Bindings/ThinPlateSpline/Bindings.hpp"

#ifdef IRR_1_8
//#include "Bindings/IrrlichtTest/Bindings.hpp"
#endif

#ifdef USE_IRRKLANG
#include "Bindings/IrrKlang/Bindings.hpp"
#endif

#ifdef USE_RAKNET
#include "Bindings/RakNet/Bindings.hpp"
#include "Bindings/RakNet/Protos.hpp"
#endif

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Interpreter{

void add_bindings()
{
    Bindings::Irrlicht::add_bindings();
    Bindings::IrrKlang::add_bindings();
    Bindings::Bullet::add_bindings();
    Bindings::Custom::add_bindings();
    Bindings::DESteer::add_bindings();
    Bindings::ThinPlateSpline::add_bindings();
}

}
