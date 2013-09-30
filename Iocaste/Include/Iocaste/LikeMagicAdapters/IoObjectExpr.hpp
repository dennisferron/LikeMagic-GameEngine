// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"

#include <iostream>
#include <stdexcept>

namespace Iocaste { namespace LMAdapters {

using LM::ExprPtr;
using LM::Expr;
using LM::TypeIndex;

class IoObjectExpr : public IMarkable
{
private:
    IoObject* io_object;
    TypeIndex io_type;

    IoObjectExpr(IoObject* io_object_);

public:
    static ExprPtr create(IoObject* io_object);
    virtual std::string description() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}}
