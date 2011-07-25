// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btCollisionConfiguration(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btCollisionConfiguration)
    LM_CLASS(ns_bullet, btDefaultCollisionConfiguration)
    LM_BASE(btDefaultCollisionConfiguration, btCollisionConfiguration)
    LM_CONSTR(btDefaultCollisionConfiguration,,)
}

}}

