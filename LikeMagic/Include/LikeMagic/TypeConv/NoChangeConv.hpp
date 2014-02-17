// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"

namespace LM {

class NoChangeConv : public AbstractTypeConverter
{
private:
    std::string name;

public:

    NoChangeConv(std::string name_) : name(name_) {}

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return expr;
    }

    virtual std::string description() const { return "NoChangeConv(" + name + ")"; }

    // A no-change conversion is virtually free.
    virtual float cost() const { return 0.01; }
};

}
