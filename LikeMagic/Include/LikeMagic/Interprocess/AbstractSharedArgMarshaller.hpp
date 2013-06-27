#pragma once

#include "LikeMagic/SFMO/AbstractExpression.hpp"

namespace LikeMagic { namespace Interprocess {

using ExprPtr = LikeMagic::SFMO::ExprPtr;

struct AbstractSharedArgMarshaller
{
    virtual void write(void* location, ExprPtr arg) = 0;
    virtual ExprPtr read(void* location) = 0;
    virtual size_t size() const = 0;
};

}}
