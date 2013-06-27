#pragma once

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

#include "LikeMagic/Interprocess/AbstractSharedArgMarshaller.hpp"

namespace LikeMagic { namespace Utility {
    class ArgList;
}}

namespace LikeMagic { namespace Interprocess {

using TypeIndex = LikeMagic::Utility::TypeIndex;
using TypeInfoList = LikeMagic::Utility::TypeInfoList;
using ArgList = LikeMagic::SFMO::ArgList;

class SharedArgTransporter
{
public:
    typedef boost::shared_ptr<AbstractSharedArgMarshaller> ArgMarshaller;

private:
    boost::unordered_map<TypeIndex, ArgMarshaller> how_marshal;

    AbstractSharedArgMarshaller& get_marshaller(TypeIndex arg_type) const;

public:

    void add_marshaller(TypeIndex type, ArgMarshaller marshaller);

    // TypeInfoList comes from
    // virtual LikeMagic::Utility::TypeInfoList AbstractCallTargetSelector::get_arg_types() const = 0;

    virtual void write_args(TypeInfoList arg_types, void* buffer, ExprPtr arg);
    virtual ArgList read_args(TypeInfoList arg_types, void* buffer);
};

}}
