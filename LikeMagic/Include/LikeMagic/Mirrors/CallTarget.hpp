// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"

namespace LM {

class CallTarget : public IMarkable
{
public:
    virtual ~CallTarget() = 0;

    virtual ExprPtr call(ExprPtr target, ArgList args) const = 0;
    virtual TypeInfoList const& get_arg_types() const = 0;
    virtual TypeIndex get_return_type() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const = 0;
};

inline CallTarget::~CallTarget() {}

LIKEMAGIC_API Delegate& eval_as_nonconst_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward);
LIKEMAGIC_API Delegate const& eval_as_const_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward);

}
