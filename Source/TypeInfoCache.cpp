// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"

namespace LikeMagic { namespace Utility {

TypeInfoCache* TypeInfoCache::instance = new TypeInfoCache;


void TypeInfoCache::set_instance(TypeInfoCache* instance_)
{
    if (instance->index_to_info.size())
        throw std::logic_error("Error: While replacing type info cache, discovered the old type info cache is not empty.  This means there is a problem related to DLLs or the RuntimeTypeSystem object.");

    instance = instance_;
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

TypeInfoPtr TypeInfoCache::get_info(TypeIndex tok)
{
    return index_to_info[tok.id];
}

void TypeInfoCache::add(TypeInfoPtr candidate)
{
    info_to_index[candidate] = index_to_info.size();
    index_to_info.push_back(candidate);
}


}}
