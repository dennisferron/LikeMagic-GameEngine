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

namespace LikeMagic { namespace Utility {

class TypeInfoCache
{
private:
    static TypeInfoCache* instance;
    //boost::unordered_map<TypeInfoPtr, TypeIndex> info_to_index;
    std::map<KeyWrapper<AbstractTypeInfo>, TypeIndex> info_to_index;
    std::vector<TypeInfoPtr> index_to_info;

public:

    TypeIndex get_index(TypeInfoPtr candidate, TypeInfoPtr class_type);
    TypeInfoPtr get_info(TypeIndex id) const;

    // I'm not a fan of singletons but in this case it makes sense.
    static TypeInfoCache* get_instance();
    static void set_instance(TypeInfoCache* instance_);
};


}}
