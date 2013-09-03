#pragma once

#include "LikeMagic/Exprs/Expr.hpp"

namespace LM {

struct AbstractSharedArgMarshaller
{
    virtual ~AbstractSharedArgMarshaller();
    virtual void write(void* location, ExprPtr arg) = 0;
    virtual ExprPtr read(void* location) = 0;
    virtual size_t size() const = 0;
};

}
