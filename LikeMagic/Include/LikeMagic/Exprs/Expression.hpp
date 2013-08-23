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

namespace LM {

using LM::BetterTypeInfo;
using LM::TypeIndex;

template <typename T>
class Expression : public AbstractExpression
{
public:
    virtual T eval() = 0;
    typedef T ReturnType;
    virtual TypeIndex get_type() const { return TypId<T>::get(); }
};

}
