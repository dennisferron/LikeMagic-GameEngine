// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"

namespace LM {

class CallTarget
{
protected:
    static Delegate* eval_as_target(ExprPtr target, TypeIndex actual_type, ExprPtr& target_ward);

public:
    virtual ~CallTarget() = 0;

    virtual ExprPtr call(ExprPtr target, ArgList args) const = 0;
    virtual LM::TypeInfoList const& get_arg_types() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const = 0;
};

inline CallTarget::~CallTarget() {}

}
