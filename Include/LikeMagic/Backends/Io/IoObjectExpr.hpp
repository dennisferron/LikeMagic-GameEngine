
#pragma once

#include "LikeMagic/SFMO/Expression.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Backends/Io/API_Io.hpp"

#include <iostream>
#include <stdexcept>

struct IoObjectExprTag {};

namespace LikeMagic { namespace Backends { namespace Io {

class IoObjectExpr : public AbstractExpression
{
private:
    IoObject* io_object;

    IoObjectExpr(IoObject* io_object_);

public:
    static ExprPtr create(IoObject* io_object) { return new IoObjectExpr(io_object); }

    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual BetterTypeInfo get_type() const;
    virtual std::string description() const;
    virtual void mark() const;
};

}}}
