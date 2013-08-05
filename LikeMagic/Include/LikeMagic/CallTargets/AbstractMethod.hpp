// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/DebugInfo.hpp"
#include "LikeMagic/Exprs/AbstractExpression.hpp"

namespace LikeMagic { namespace Exprs {
    class AbstractCppObjProxy;
}}

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace CallTargets {

using ExprPtr = LikeMagic::Exprs::ExprPtr;
using ArgList = LikeMagic::Exprs::ArgList;

class AbstractMethod
{
public:
    virtual ~AbstractMethod() = 0;

    virtual ExprPtr call(ExprPtr target, ArgList args) const = 0;
    virtual LikeMagic::Utility::TypeInfoList get_arg_types() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return true; }
};

}}
