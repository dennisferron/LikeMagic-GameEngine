#pragma once

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"
#include "boost/intrusive_ptr.hpp"

#include "LikeMagic/Interprocess/AbstractSharedArgMarshaller.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace SFMO {
    class AbstractExpression;
    typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;
    typedef std::vector<ExprPtr> ArgList;
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

    SharedArgTransporter(LikeMagic::AbstractTypeSystem& type_system_);

    template <template <typename T_> class Marshaller, typename T, typename... Args>
    void add_marshaller_by_type(Args && ... args)
    {
        TypeIndex index = LikeMagic::Utility::BetterTypeInfo::create_index<T>();
        auto marshaller = ArgMarshaller(new Marshaller<T>(std::forward<Args>(args)...));
        add_marshaller(index, marshaller);
    }

    void add_marshaller(TypeIndex type, ArgMarshaller marshaller);

    // TypeInfoList comes from
    // virtual LikeMagic::Utility::TypeInfoList AbstractCallTargetSelector::get_arg_types() const = 0;

    void write_args(TypeInfoList arg_types, void* buffer, ArgList args);
    void* write_value(TypeIndex arg_type, void* location, ExprPtr arg);

    ArgList read_args(TypeInfoList arg_types, void* buffer);
    std::pair<ExprPtr, void*> read_value(TypeIndex arg_type, void* location);
};

}}
