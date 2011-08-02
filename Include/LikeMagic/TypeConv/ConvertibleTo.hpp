// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "AbstractTypeConverter.hpp"
#include "boost/intrusive_ptr.hpp"

// Forward declarations.
namespace LikeMagic { namespace SFMO {

class AbstractExpression;

template <typename To>
class Expression;

typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;

}}

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

template <typename To>
class ConvertibleTo : public virtual AbstractTypeConverter
{
public:
    virtual std::string describe() const { return BetterTypeInfo::create_index<decltype(this)>().describe(); }
};

}}
