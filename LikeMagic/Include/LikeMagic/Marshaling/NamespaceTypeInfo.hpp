// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once


#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;

class NamespaceTypeInfo : public AbstractTypeInfo
{
private:
    std::string namespace_name;

    NamespaceTypeInfo(std::string namespace_name_) : namespace_name(namespace_name_) {}

protected:

    virtual std::string get_system() const
    {
        return "namespace";
    }

    virtual bool less(const AbstractTypeInfo& other) const
    {
        NamespaceTypeInfo const& that = static_cast<NamespaceTypeInfo const&>(other);
        return this->namespace_name < that.namespace_name;
    }

    virtual bool equals(const AbstractTypeInfo& other) const
    {
        NamespaceTypeInfo const& that = static_cast<NamespaceTypeInfo const&>(other);
        return this->namespace_name == that.namespace_name;
    }

    virtual std::size_t calc_hash() const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, namespace_name);
        return seed;
    }

public:

    static TypeInfoPtr create(std::string namespace_name) { return new NamespaceTypeInfo(namespace_name); }

    static TypeIndex create_index(std::string namespace_name)
    {
        TypeInfoPtr info = create(namespace_name);
        return TypeInfoCache::get_instance()->get_index(
                info, info
        );
    }

    virtual std::string describe() const
    {
        return "namespace-typeinfo '" + namespace_name + "'";
    }
};


}}
