// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include <iostream>


namespace LikeMagic { namespace SFMO {

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
    virtual boost::intrusive_ptr<Expression<T>> clone() const = 0;
    typedef T ReturnType;
    virtual TypeIndex get_type() const { return BetterTypeInfo::create_index<T>(); }
};

}}
