#pragma once

#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/SFMO/Trampoline.hpp"
#include "LikeMagic/SFMO/NumberCachingTrampoline.hpp"

#include "boost/type_traits.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

template <typename From, typename To>
class NumberConvImpl
{
public:

    inline static To do_conv(From obj)
    {
        return static_cast<To>(obj);
    }
};

template <typename From, typename To>
class NumberConvImpl<From, To&>
{
public:

    // Return To as a non-reference here; depending on NumberCachingTrampoline to cache it as a value and return a reference for us.
    inline static To do_conv(From obj)
    {
        return static_cast<To>(obj);
    }
};

template <typename From, typename To>
class NumberConv : public ConvertibleTo<To>
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, NumberConvImpl<From, To>>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To>("NumberConv"); }

};

// When the destination type is a reference, we must cache the intermediate
// value (via CachingTrampoline) EVEN IF To-type is a CONST ref.  I would have
// thought the temporary would live long enough to provide a quick read-only
// reference in a function call, but in actual observation I've seen
// the args clobbered when I did this without using caching.
// Even if (especially if?) the source type is a reference, you must still cache it.
template <typename From, typename To>
class NumberConv<From, To&> : public ConvertibleTo<To&>
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return NumberCachingTrampoline<From, To&, NumberConvImpl<From, To&>>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To&>("NumberConv"); }

};

}}