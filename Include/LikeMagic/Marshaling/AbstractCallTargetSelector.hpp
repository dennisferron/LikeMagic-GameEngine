
#pragma once

#include "LikeMagic/Utility/BetterTypeInfo.hpp"

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
    virtual std::vector<BetterTypeInfo> get_arg_types() const = 0;
};

}}
