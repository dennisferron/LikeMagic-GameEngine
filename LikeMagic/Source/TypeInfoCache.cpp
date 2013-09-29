// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"

#ifdef BUILDING_DLL_STD_BINDINGS
    #define BUILDING_DLL
#endif
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

LIKEMAGIC_API TypeInfoCache* type_info_cache_instance = NULL;

TypeIndex const& TypeInfoCache::get_index(TypeInfoPtr candidate)
{
    return get_index(candidate, candidate->class_type());
}

TypeIndex const& TypeInfoCache::get_index(TypeInfoPtr candidate, TypeInfoPtr class_type)
{
    TypeIndex const* index;
    TypeIndex class_index;
    auto iter = info_to_index.find(KeyWrapper<AbstractTypeInfo>(candidate));

    if (iter != info_to_index.end())
        index = &(iter->second);
    else
    {
        auto class_iter = info_to_index.find(KeyWrapper<AbstractTypeInfo>(class_type));

        if (class_iter != info_to_index.end())
            class_index = class_iter->second;
        else
        {
            class_index = TypeIndex(index_to_info.size(), index_to_info.size());
            info_to_index[class_type] = class_index;
            index_to_info.push_back(class_type);
        }

        if (*candidate == *class_type)
            index = &(info_to_index[class_type]);
        else
        {
            info_to_index[candidate] = TypeIndex(index_to_info.size(), class_index.id);
            index = &(info_to_index[candidate]);
            index_to_info.push_back(candidate);
        }
    }

    return *index;
}

TypeInfoPtr TypeInfoCache::get_info(TypeIndex id) const
{
    return index_to_info[id.id];
}

void TypeInfoCache::debug_dump()
{
    for (size_t i=0; i<index_to_info.size(); i++)
        std::cout << "index_to_info " << i << ": " << index_to_info[i]->description() << std::endl;

    for (auto& kv : info_to_index)
        std::cout << "info_to_index " << kv.first.key->description() << " => " << kv.second.description() << std::endl;
}

}
