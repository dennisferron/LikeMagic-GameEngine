// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"

namespace LM {

class CallTarget
{
public:
    virtual ~CallTarget() = 0;

    virtual ExprPtr call(ExprPtr target, ArgList args) const = 0;
    virtual LM::TypeInfoList const& get_arg_types() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const = 0;
};

inline CallTarget::~CallTarget() {}

}