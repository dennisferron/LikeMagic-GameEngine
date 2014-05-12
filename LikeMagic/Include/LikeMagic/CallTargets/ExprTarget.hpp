// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/TypePack.hpp"
#include "LikeMagic/Utility/make_arg_list.hpp"

namespace LM {

class ExprTarget : public CallTarget
{
private:
    ExprPtr expr;

public:

    ExprTarget(ExprPtr expr_);
    virtual ExprPtr call(ExprPtr target, ArgList args) const;
    virtual TypeInfoList const& get_arg_types() const;
    virtual bool is_inherited() const { return true; }
    virtual void mark() const { expr->mark(); }
    virtual TypeIndex get_return_type() const;
};

}
