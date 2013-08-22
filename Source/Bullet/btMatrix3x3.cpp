// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace LM;

namespace Bindings { namespace Bullet {

void add_bindings_btMatrix3x3()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_bullet = register_namespace("Bullet", global_ns);

    LM_CLASS(ns_bullet, btMatrix3x3)
    LM_CONSTR(btMatrix3x3, "new")
    LM_STATIC_FUNC_OVERLOAD(btMatrix3x3_LM, "getIdentityMatrix", btMatrix3x3::getIdentity, btMatrix3x3 const&)

    LM_FUNC(btMatrix3x3, (absolute)(adjoint)(cofac)(deSerialize)(deSerializeDouble)(deSerializeFloat)(determinant)(diagonalize)(getColumn)
            (getEulerYPR)(getEulerZYX)(getOpenGLSubMatrix)(getRotation)(getRow)(inverse)(scaled)(serialize)(serializeFloat)(setEulerYPR)
            (setEulerZYX)(setFromOpenGLSubMatrix)(setIdentity)(setValue)(tdotx)(tdoty)(tdotz)(timesTranspose)(transpose)(transposeTimes))

}

}}

