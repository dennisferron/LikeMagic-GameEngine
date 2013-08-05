// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


// This is to disable the warning on the placement-new lines in a bullet header.
// I hate it when libraries don't compile without warnings.  Even worse when it's in a header!
#pragma GCC diagnostic ignored "-Wuninitialized"
#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btConstraintSolver(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btConstraintSolver)
    LM_CLASS(ns_bullet, btSequentialImpulseConstraintSolver)
    LM_BASE(btSequentialImpulseConstraintSolver, btConstraintSolver)
    LM_CONSTR(btSequentialImpulseConstraintSolver,,)
}

}}

