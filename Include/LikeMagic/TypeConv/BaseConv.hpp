#pragma once

#include "ConvertibleTo.hpp"
#include "../SFMO/Trampoline.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

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
        return LikeMagic::SFMO::Trampoline<From, To, BaseConv>::create(
            boost::intrusive_ptr<LikeMagic::SFMO::Expression<From>>(
                reinterpret_cast<LikeMagic::SFMO::Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To>("BaseConv") + " (inherits from " + ConvertibleTo<To>::describe() + ")"; }
};

}}