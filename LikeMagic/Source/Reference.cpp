// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/Term.hpp"

#include <iostream>

namespace LM {


Reference::Reference(ValuePtr value_, TypeIndex type_, ExprPtr storage_location_)
    : Expr(value_, type_), storage_location(storage_location_)
{
}

Reference::~Reference() {}

std::string Reference::description() const
{
    return std::string("Reference<" + Expr::description() + ">");
}

void Reference::mark() const
{
    Expr::mark();

    if (storage_location)
        storage_location->mark();
}

}
