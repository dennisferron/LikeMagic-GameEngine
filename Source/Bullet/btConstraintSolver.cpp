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

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btConstraintSolver()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btConstraintSolver)
    LM_CLASS(ns_bullet, btSequentialImpulseConstraintSolver)
    LM_BASE(btSequentialImpulseConstraintSolver, btConstraintSolver)
    LM_CONSTR(btSequentialImpulseConstraintSolver,"new")
}

}}

