// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"
#include "boost/unordered_map.hpp"
#include <vector>

namespace LM
{
    class TypeInfoCache;
    TypeInfoCache* type_info_cache_instance = NULL;
}

namespace LM {

inline std::size_t hash_value(TypeInfo const& info)
{
    std::size_t seed = 0;
    boost::hash_combine(seed, info.system);
    boost::hash_combine(seed, info.name);
    boost::hash_combine(seed, info.ptr_type);
    boost::hash_combine(seed, info.ref_type);
    boost::hash_combine(seed, info.is_restricted);
    return seed;
}

class TypeInfoCache
{
private:
    boost::unordered_map<TypeInfo, TypeIndex> info_to_index;
    std::vector<TypeInfo> index_to_info;
    std::vector<TypeIndex> index_to_class;
    TypeIndex get_index_simple(TypeInfo candidate);

public:

    TypeIndex get_index(TypeInfo candidate);
    TypeInfo get_info(TypeIndex id) const;
    TypeIndex get_class_index(TypeIndex id) const;

    void debug_dump();
};

void create_type_info_cache()
{
    type_info_cache_instance = new TypeInfoCache();
}

void delete_type_info_cache()
{
    delete type_info_cache_instance;
}

TypeIndex TypeInfoCache::get_index_simple(TypeInfo candidate)
{
    TypeIndex index;

    auto iter = info_to_index.find(TypeInfo(candidate));

    if (iter != info_to_index.end())
        index = iter->second;
    else
    {
        info_to_index[candidate] = TypeIndex(index_to_info.size());
        index = info_to_index[candidate];
        index_to_info.push_back(candidate);
        index_to_class.push_back(index);
    }

    return index;
}

TypeIndex TypeInfoCache::get_index(TypeInfo candidate)
{
    TypeInfo class_type = candidate.class_type();
    TypeIndex class_index = get_index_simple(class_type);
    TypeIndex result = get_index_simple(candidate);
    index_to_class[result.get_id()] = class_index;
    return result;
}

TypeInfo TypeInfoCache::get_info(TypeIndex id) const
{
    size_t pos = id.get_id();

    if (pos >= index_to_info.size())
        throw std::out_of_range("Type index is out of range.");

    return index_to_info[pos];
}

TypeIndex TypeInfoCache::get_class_index(TypeIndex id) const
{
    size_t pos = id.get_id();

    if (pos >= index_to_info.size())
        throw std::out_of_range("Type index is out of range.");

    return index_to_class[id.get_id()];
}

void TypeInfoCache::debug_dump()
{
    for (size_t i=0; i<index_to_info.size(); i++)
        std::cout << "index_to_info " << i << ": " << index_to_info[i].description() << std::endl;

    for (auto& kv : info_to_index)
        std::cout << "info_to_index " << kv.first.description() << " => " << kv.second.description() << std::endl;
}

const TypeInfoList empty_arg_list_obj;
LIKEMAGIC_API const TypeInfoList& empty_arg_list = empty_arg_list_obj;

LIKEMAGIC_API TypeIndex get_index(TypeInfo const& type)
{
    return type_info_cache_instance->get_index(type);
}

LIKEMAGIC_API TypeInfo get_info(TypeIndex const& index)
{
    return type_info_cache_instance->get_info(index);
}

LIKEMAGIC_API TypeIndex get_class_index(TypeIndex index)
{
    return type_info_cache_instance->get_class_index(index);
}

}
