#pragma once

#include "LikeMagic/Marshaling/CallTarget.hpp"

namespace LikeMagic { namespace Interprocess {

class RequestBroker;

class RemoteMethod : public CallTarget
{
private:
    RequestBroker& broker;

public:
    RemoteMethod(RequestBroker& broker_);
    virtual ~RemoteMethod();

    virtual LikeMagic::Exprs::AbstractCppObjProxy* call
        (
            LikeMagic::Exprs::AbstractCppObjProxy* target,
            LikeMagic::Exprs::ArgList args
        ) const;

    virtual LikeMagic::Utility::TypeInfoList get_arg_types() const;
};

}}
