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
#include "LikeMagic/Utility/TypeInfo.hpp"

namespace LM {

/*
template <typename FirstArg, typename... Args>
TypeInfoList make_arg_list(TypePack<FirstArg, Args...> args)
{
    TypeInfoList list;
    list.push_back(TypId<FirstArg>::get());
    TypeInfoList others = make_arg_list(TypePack<Args...>());
    list.insert(list.end(), others.begin(), others.end());
    return list;
}

template <typename FirstArg>
TypeInfoList make_arg_list(TypePack<> args)
{
    return TypeInfoList();
}
*/

template <typename... Args>
struct MakeArgList;

template <>
struct MakeArgList<>
{
    MakeArgList() = delete;

    static TypeInfoList value()
    {
        return TypeInfoList();
    }
};

template <typename FirstArg, typename... Args>
struct MakeArgList<FirstArg, Args...>
{
    MakeArgList() = delete;

    static TypeInfoList value()
    {
        TypeInfoList result = MakeArgList<Args...>::value();
        result.insert(result.begin(), TypId<FirstArg>::restricted());
        return result;
    }
};

}
