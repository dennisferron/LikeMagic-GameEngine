// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Exprs/BottomPtrExpr.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Exprs/BottomPtrExpr.hpp"
#include "LikeMagic/Exprs/NullExpr.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

class BottomPtrTarget : public CallTarget
{
public:

    BottomPtrTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return BottomPtrExpr::create(try_conv<void*>(target.get()));
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};

}}
