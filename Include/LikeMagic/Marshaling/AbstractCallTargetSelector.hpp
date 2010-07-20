// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LikeMagic { namespace Marshaling {

class AbstractFunctionoid;

class AbstractCallTargetSelector
{
public:
    virtual ~AbstractCallTargetSelector() {}
    virtual AbstractCppObjProxy* call
        (
            AbstractCppObjProxy* target,
            std::vector<boost::intrusive_ptr<AbstractExpression>> args
        ) const = 0;
    virtual TypeInfoList get_arg_types() const = 0;
};

}}
