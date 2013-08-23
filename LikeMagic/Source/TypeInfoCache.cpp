// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"

namespace LM {

TypeInfoCache* TypeInfoCache::instance = NULL;

TypeInfoPtr TypeIndex::get_info() const
{
    return TypeInfoCache::get_instance()->get_info(*this);
}

std::string TypeIndex::description() const
{
    return get_info()->description();
}

void TypeInfoCache::set_instance(TypeInfoCache* instance_)
{
    bool is_null = (instance == NULL);
    bool is_same = ((void*)instance == (void*)instance_);

    if (!is_null && !is_same)
        throw std::logic_error("Error: TypeInfoCache already exists.");

    instance = instance_;
}

TypeInfoCache* TypeInfoCache::get_instance()
{
    if (!instance)
        throw std::logic_error("Error:  TypeInfoCache instance has not been created yet!  Use the user macro LM_SET_TYPE_INFO to set the type info object once in each DLL.");

    return instance;
}

TypeIndex TypeInfoCache::get_index(TypeInfoPtr candidate)
{
    return get_index(candidate, candidate->bare_type());
}

TypeIndex TypeInfoCache::get_index(TypeInfoPtr candidate, TypeInfoPtr class_type)
{
    TypeIndex index;
    TypeIndex class_index;
    auto iter = info_to_index.find(KeyWrapper<AbstractTypeInfo>(candidate));

    if (iter != info_to_index.end())
        index = iter->second;
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
            index = class_index;
        else
        {
            index = TypeIndex(index_to_info.size(), class_index.id);
            info_to_index[candidate] = index;
            index_to_info.push_back(candidate);
        }
    }

    return index;
}

TypeInfoPtr TypeInfoCache::get_info(TypeIndex id) const
{
    return index_to_info[id.id];
}


}
