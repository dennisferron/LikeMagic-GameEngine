// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "LikeMagic/TypeConv/ConvImpl.hpp"

#include "boost/intrusive_ptr.hpp"

namespace LM {

class Expr;
typedef boost::intrusive_ptr<Expr> ExprPtr;

}

#include <string>

namespace LM {

class AbstractTypeConverter;
LIKEMAGIC_API void intrusive_ptr_add_ref(AbstractTypeConverter const* p);
LIKEMAGIC_API void intrusive_ptr_release(AbstractTypeConverter const* p);

class AbstractTypeConverter
{
private:
    friend LIKEMAGIC_API void intrusive_ptr_add_ref(AbstractTypeConverter const* p);
    friend LIKEMAGIC_API void intrusive_ptr_release(AbstractTypeConverter const* p);
    mutable int ref_count;

public:
    AbstractTypeConverter();
    virtual ~AbstractTypeConverter() = 0;
    virtual std::string description() const = 0;
    virtual ExprPtr wrap_expr(ExprPtr expr) const = 0;
    virtual float cost() const = 0;
};

inline AbstractTypeConverter::AbstractTypeConverter() : ref_count(0) {}
inline AbstractTypeConverter::~AbstractTypeConverter() {}

// Handy helper function
template <typename From, typename To>
std::string describe_converter(std::string converter_name)
{
    return
            converter_name +
            " from " + TypId<From>::get().description() +
            " to " + TypId<To>::get().description();
}

typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

}
