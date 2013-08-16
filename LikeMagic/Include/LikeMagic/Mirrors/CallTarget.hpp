// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Exprs/AbstractExpression.hpp"

namespace LikeMagic { namespace Exprs {
    class AbstractCppObjProxy;
}}

namespace LikeMagic {
    class TypeSystem;
}

namespace LikeMagic { namespace Mirrors {

using ExprPtr = LikeMagic::Exprs::ExprPtr;
using ArgList = LikeMagic::Exprs::ArgList;

class CallTarget
{
public:
    virtual ~CallTarget() = 0;

    virtual ExprPtr call(ExprPtr target, ArgList args) const = 0;
    virtual LikeMagic::Utility::TypeInfoList const& get_arg_types() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const;
};

}}
