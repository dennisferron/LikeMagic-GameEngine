// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::Exprs;

template <typename From, typename To>
class PtrDerefConv : public ConvertibleTo<To>
{
public:
    inline static To do_conv(From obj)
    {
        if (!&*obj)
            throw std::logic_error("PtrDerefConv on null pointer! " + describe_converter<From, To>("PtrDerefConv"));

        return *obj;
    }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, PtrDerefConv>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string description() const { return describe_converter<From, To>("PtrDerefConv"); }

    // Don't want to use a detour via addr of / ptr deref where other conversion will do.
    virtual float cost() const { return 3.0f; }
};

}}
