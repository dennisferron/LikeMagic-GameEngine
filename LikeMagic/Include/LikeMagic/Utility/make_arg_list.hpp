// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/TypePack.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

namespace LikeMagic { namespace Utility {

template <typename FirstArg, typename... Args>
TypeInfoList make_arg_list(TypePack<FirstArg, Args...> args)
{
    TypeInfoList list;
    list.push_back(BetterTypeInfo::create_index<FirstArg>());
    TypeInfoList others = make_arg_list(TypePack<Args...>());
    list.insert(list.end(), others.begin(), others.end());
    return list;
}

inline TypeInfoList make_arg_list(TypePack<> args)
{
    return TypeInfoList();
}

}}
