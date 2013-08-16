// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "ConvertibleTo.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::Exprs;

template <typename From, typename To>
class BaseConv : public ConvertibleTo<To>
{
public:
    inline static To do_conv(From obj) { return obj; }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        // Note:  The reinterpret cast here is not doing the conversion
        // (which would be unsafe if it were so);
        // it is merely converting the ExprPtr to its actual _FROM_ type.
        // The to-base _TO_ type conversion work is done implicitly by do_conv above.
        return LikeMagic::Exprs::Trampoline<From, To, BaseConv>::create(
            boost::intrusive_ptr<LikeMagic::Exprs::Expression<From>>(
                reinterpret_cast<LikeMagic::Exprs::Expression<From>*>(expr.get())));
    }

    virtual std::string description() const { return describe_converter<From, To>("BaseConv"); }
};

}}
