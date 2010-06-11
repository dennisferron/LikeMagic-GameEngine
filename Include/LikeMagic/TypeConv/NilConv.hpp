#pragma once

#include "ConvertibleTo.hpp"
#include "../SFMO/Trampoline.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

class NilConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return NullExpr<void*>::create();
    }

    virtual std::string describe() const { return "NilConv"; }
};

}}
