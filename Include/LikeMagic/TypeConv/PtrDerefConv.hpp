#pragma once

#include "ConvertibleTo.hpp"
#include "../SFMO/Trampoline.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

template <typename From, typename To>
class PtrDerefConv : public ConvertibleTo<To>
{
public:
    inline static To do_conv(From obj) { return *obj; }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, PtrDerefConv>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To>("PtrDerefConv") + " (inherits from " + ConvertibleTo<To>::describe() + ")"; }
};

}}
