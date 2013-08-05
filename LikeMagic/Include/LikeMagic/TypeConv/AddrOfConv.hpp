// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "ConvertibleTo.hpp"
#include "../Exprs/Trampoline.hpp"

#include "boost/type_traits/is_reference.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::Exprs;

template <typename From, typename To>
class AddrOfConv : public ConvertibleTo<To>
{
    static_assert(boost::is_reference<From>::value,
            "From type must be a reference.  Cannot convert a value arg to pointer because the temporary copy is lost when do_conv returns.");

public:
    inline static To do_conv(From obj) { return &obj; }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, AddrOfConv>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To>("AddrOfConv"); }

    // Don't want to use a detour via addr of / ptr deref where other conversion will do.
    virtual float cost() const { return 3.0f; }
};

}}
