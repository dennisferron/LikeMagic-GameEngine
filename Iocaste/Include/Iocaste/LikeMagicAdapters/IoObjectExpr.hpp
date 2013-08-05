// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expression.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"

#include <iostream>
#include <stdexcept>

namespace Iocaste { namespace LikeMagicAdapters {

using LikeMagic::Exprs::ExprPtr;
using LikeMagic::Exprs::Expression;
using LikeMagic::Utility::TypeIndex;

class IoObjectExpr : public Expression<IoObject*>
{
private:
    IoObject* io_object;
    TypeIndex type_info;

    IoObjectExpr(IoObject* io_object_);

public:
    static ExprPtr create(IoObject* io_object) { return new IoObjectExpr(io_object); }

    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual TypeIndex get_type() const;
    virtual std::string description() const;
    virtual void mark() const;
    virtual IoObject* eval() { return io_object; }

    virtual boost::intrusive_ptr<Expression<IoObject*>> clone() const
    {
        throw std::logic_error("clone for IoObjectExpr not implemented yet (but should not be hard to implement!)");
    }

};

}}
