// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/BottomPtrExpr.hpp"

namespace LM {

// When IoNil is encountered, it is marshaled as a NullExpr object.
// The type can be converted to any other pointer in TypeConvGraph.
class NullExpr : public BottomPtrExpr
{
private:
    NullExpr() {}

public:
    static ExprPtr create() { return new NullExpr(); }

    virtual bool is_terminal() const { return true; }

    virtual std::string description() const
    {
        return std::string("NULL");
    }

    virtual void mark() const {}
};

}
