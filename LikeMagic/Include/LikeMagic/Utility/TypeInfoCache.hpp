// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"
#include "boost/unordered_map.hpp"

namespace LM {

inline std::size_t hash_value(TypeInfo const& info)
{
    std::size_t seed = 0;
    boost::hash_combine(seed, info.system);
    boost::hash_combine(seed, info.name);
    boost::hash_combine(seed, info.is_const);
    boost::hash_combine(seed, info.is_ptr);
    return seed;
}

class TypeInfoCache
{
private:
    boost::unordered_map<TypeInfo, TypeIndex> info_to_index;
    std::vector<TypeInfo> index_to_info;
    std::vector<TypeIndex> index_to_class;

public:

    TypeIndex const& get_index(TypeInfo candidate, TypeInfo class_type);
    TypeIndex const& get_index(TypeInfo candidate);
    TypeInfo get_info(TypeIndex id) const;

    void debug_dump();
};

}
