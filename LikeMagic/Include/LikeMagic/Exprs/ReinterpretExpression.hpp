// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Utility::TypeIndex;

// To support casts, this expression wraps an inner expression

class ReinterpretExpression : public AbstractExpression
{
private:
    ExprPtr inner;
    TypeIndex cast_to_type;
    ReinterpretExpression(ExprPtr inner_, TypeIndex cast_to_type_) : inner(inner_) , cast_to_type(cast_to_type_) {}

public:
    static ExprPtr create(ExprPtr inner_, TypeIndex cast_to_type_) { return new ReinterpretExpression(inner_, cast_to_type_); }
    virtual TypeIndex get_type() const { return cast_to_type; }
};

}}
