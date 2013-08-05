// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "Expression.hpp"

#include "../Utility/TypeDescr.hpp"
#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace Exprs {

class FalseExpr : public Expression<bool>
{
private:
    FalseExpr() {}

public:
    static boost::intrusive_ptr<Expression<bool>> create() { return new FalseExpr(); }

    inline virtual bool eval() { return false; }
    virtual boost::intrusive_ptr<Expression<bool>> clone() const { return new FalseExpr(); }
    virtual bool is_terminal() const { return true; }

    virtual std::string description() const
    {
        return std::string("false");
    }

    virtual void mark() const {}
};

}}
