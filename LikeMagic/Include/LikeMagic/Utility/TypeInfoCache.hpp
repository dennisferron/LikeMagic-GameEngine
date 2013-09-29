// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/KeyWrapper.hpp"

#ifdef BUILDING_DLL_STD_BINDINGS
    #define BUILDING_DLL
#endif
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class TypeInfoCache
{
private:
    std::map<KeyWrapper<AbstractTypeInfo>, TypeIndex> info_to_index;
    std::vector<TypeInfoPtr> index_to_info;

public:

    TypeIndex const& get_index(TypeInfoPtr candidate, TypeInfoPtr class_type);
    TypeIndex const& get_index(TypeInfoPtr candidate);
    TypeInfoPtr get_info(TypeIndex id) const;

    void debug_dump();
};

LIKEMAGIC_API extern TypeInfoCache* type_info_cache_instance;

}
