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

void add_bindings_btBroadphaseProxy(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btBroadphaseProxy)

    typedef btBroadphaseProxy::CollisionFilterGroups CollisionFilterGroups;
    LM_CLASS(ns_bullet, CollisionFilterGroups)
    ns_bullet.get_type_system().add_conv<CollisionFilterGroups, short, LikeMagic::TypeConv::NumberConv>();

}

}}

