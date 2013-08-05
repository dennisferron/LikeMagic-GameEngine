// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "btBulletDynamicsCommon.h"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Bindings { namespace Bullet {

void add_bindings_btMatrix3x3(Namespace const& ns_bullet)
{
    LM_CLASS(ns_bullet, btMatrix3x3)
    LM_CONSTR(btMatrix3x3,,)
    LM_STATIC_FUNC_OVERLOAD(ns_bullet, btMatrix3x3, "getIdentityMatrix", getIdentity, btMatrix3x3 const&)
    LM_FUNC(btMatrix3x3, (absolute)(adjoint)(cofac)(deSerialize)(deSerializeDouble)(deSerializeFloat)(determinant)(diagonalize)(getColumn)
            (getEulerYPR)(getEulerZYX)(getOpenGLSubMatrix)(getRotation)(getRow)(inverse)(scaled)(serialize)(serializeFloat)(setEulerYPR)
            (setEulerZYX)(setFromOpenGLSubMatrix)(setIdentity)(setValue)(tdotx)(tdoty)(tdotz)(timesTranspose)(transpose)(transposeTimes))

}

}}

