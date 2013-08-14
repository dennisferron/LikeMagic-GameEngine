// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

namespace LikeMagic { namespace Exprs {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Utility::TypeIndex;

template <typename T>
class Expression : public AbstractExpression
{
private:
    Expression(Expression<T> const& other);

protected:
    Expression() {}

public:
    virtual ~Expression() {}
    virtual T eval() = 0;
    typedef T ReturnType;
    virtual TypeIndex get_type() const { return BetterTypeInfo::create_index<T>(); }
    virtual TypeIndex get_class_type() const { return get_type().class_type(); }
    virtual bool is_null() const { return false; }
    virtual bool disable_to_script_conv() const { return false; }
};

}}
