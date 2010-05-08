#pragma once

#include "ConvertibleTo.hpp"
#include "../SFMO/Trampoline.hpp"

#include "boost/type_traits/is_reference.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

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

    virtual std::string describe() const { return describe_converter<From, To>("AddrOfConv") + " (inherits from " + ConvertibleTo<To>::describe() + ")"; }
};

}}