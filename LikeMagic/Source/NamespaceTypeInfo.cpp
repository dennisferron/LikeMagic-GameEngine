// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/NamespaceTypeInfo.hpp"

using namespace LM;

NamespaceTypeInfo::NamespaceTypeInfo(std::string namespace_name_) : namespace_name(namespace_name_) {}

std::string NamespaceTypeInfo::get_system() const
{
    return "namespace";
}

bool NamespaceTypeInfo::less(const AbstractTypeInfo& other) const
{
    NamespaceTypeInfo const& that = static_cast<NamespaceTypeInfo const&>(other);
    return this->namespace_name < that.namespace_name;
}

bool NamespaceTypeInfo::equals(const AbstractTypeInfo& other) const
{
    NamespaceTypeInfo const& that = static_cast<NamespaceTypeInfo const&>(other);
    return this->namespace_name == that.namespace_name;
}

std::size_t NamespaceTypeInfo::calc_hash() const
{
    std::size_t seed = 0;
    boost::hash_combine(seed, namespace_name);
    return seed;
}

TypeInfoPtr NamespaceTypeInfo::create(std::string namespace_name) { return new NamespaceTypeInfo(namespace_name); }

TypeIndex NamespaceTypeInfo::create_index(std::string namespace_name)
{
    TypeInfoPtr info = create(namespace_name);
    return type_info_cache_instance->get_index(info, info);
}

std::string NamespaceTypeInfo::description() const
{
    return "namespace-typeinfo '" + namespace_name + "'";
}

std::string NamespaceTypeInfo::get_namespace_name() const
{
    return namespace_name;
}

TypeInfoPtr NamespaceTypeInfo::as_const() const
{
    return this;
}

TypeInfoPtr NamespaceTypeInfo::as_nonconst() const
{
    return this;
}

TypeInfoPtr NamespaceTypeInfo::as_ptr() const
{
    return this;
}

TypeInfoPtr NamespaceTypeInfo::as_value() const
{
    return this;
}

TypeInfoPtr NamespaceTypeInfo::class_type() const
{
    return this;
}
