#pragma once

#include "LikeMagic/Marshaling/AbstractCallTargetSelector.hpp"

namespace LikeMagic { namespace Interprocess {

class RequestBroker;

class RemoteMethod : public AbstractCallTargetSelector
{
private:
    RequestBroker& broker;

public:
    RemoteMethod(RequestBroker& broker_);
    virtual ~RemoteMethod();

    virtual LikeMagic::SFMO::AbstractCppObjProxy* call
        (
            LikeMagic::SFMO::AbstractCppObjProxy* target,
            LikeMagic::SFMO::ArgList args
        ) const;

    virtual LikeMagic::Utility::TypeInfoList get_arg_types() const;
};

}}
