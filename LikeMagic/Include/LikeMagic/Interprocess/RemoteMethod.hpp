#pragma once

#include "LikeMagic/Marshaling/CallTarget.hpp"

namespace LM {

class RequestBroker;

class RemoteMethod : public CallTarget
{
private:
    RequestBroker& broker;

public:
    RemoteMethod(RequestBroker& broker_);
    virtual ~RemoteMethod();

    virtual LM::AbstractCppObjProxy* call
        (
            LM::AbstractCppObjProxy* target,
            LM::ArgList args
        ) const;

    virtual LM::TypeInfoList get_arg_types() const;
};

}
