// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Expression.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Backends/Io/API_Io.hpp"
#include "LikeMagic/Backends/Io/FromIoTypeInfo.hpp"

#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace Backends { namespace Io {

using LikeMagic::SFMO::ExprPtr;
using LikeMagic::SFMO::Expression;
using LikeMagic::Utility::AbstractTypeInfo;

class IoObjectExpr : public Expression<IoObject*>
{
private:
    IoObject* io_object;
    FromIoTypeInfo type_info;

    IoObjectExpr(IoObject* io_object_);

public:
    static ExprPtr create(IoObject* io_object) { return new IoObjectExpr(io_object); }

    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual AbstractTypeInfo const& get_type() const;
    virtual std::string description() const;
    virtual void mark();
    virtual IoObject* eval() { return io_object; }

    virtual boost::intrusive_ptr<Expression<IoObject*>> clone() const
    {
        throw std::logic_error("clone for IoObjectExpr not implemented yet (but should not be hard to implement!)");
    }

};

}}}
