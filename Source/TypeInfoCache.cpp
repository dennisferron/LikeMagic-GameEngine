// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"

namespace LikeMagic { namespace Utility {

TypeInfoCache* TypeInfoCache::instance = NULL;

TypeInfoPtr TypeIndex::get_info() const
{
    return TypeInfoCache::get_instance()->get_info(*this);
}

std::string TypeIndex::describe() const
{
    return get_info()->describe();
}

void TypeInfoCache::set_instance(TypeInfoCache* instance_)
{
    if (instance != NULL)
        throw std::logic_error("Error: TypeInfoCache already exists.");

    instance = instance_;
}

TypeInfoCache* TypeInfoCache::get_instance()
{
    if (!instance)
        throw std::logic_error("Error:  TypeInfoCache instance has not been created yet!");

    return instance;
}



TypeIndex TypeInfoCache::get_index(TypeInfoPtr candidate)
{
    auto iter = info_to_index.find(candidate);

    if (iter == info_to_index.end())
    {
        add(candidate);
        iter = info_to_index.find(candidate);
    }

    return iter->second;
}

TypeInfoPtr TypeInfoCache::get_info(TypeIndex id) const
{
    return index_to_info[id.id];
}

void TypeInfoCache::add(TypeInfoPtr candidate)
{
    info_to_index[candidate] = TypeIndex(index_to_info.size());
    index_to_info.push_back(candidate);
}


}}
