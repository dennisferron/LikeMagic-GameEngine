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
class PtrCastConv : public ConvertibleTo<To>
{
public:

    inline static To do_conv(From obj)
    {
        return reinterpret_cast<To>(obj);
    }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, PtrCastConv>::create(
            boost::intrusive_ptr<Expression<From>>(
                static_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string description() const { return describe_converter<From, To>("PtrCastConv"); }

    // Pointer cast is not expensive in terms of CPU cycles, but
    // we don't want to use ptr cast when something else will do.
    virtual float cost() const { return 10.0; }
};

}}
