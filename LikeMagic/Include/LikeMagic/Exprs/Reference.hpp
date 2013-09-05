// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expr.hpp"

#include <iostream>

namespace LM {

class Reference : public Expr
{
private:

    ExprPtr storage_location;

public:

    Reference(ValuePtr value_, TypeIndex type_, ExprPtr storage_location_);
    virtual ~Reference();
    virtual std::string description() const;
    virtual void mark() const;
};


}
