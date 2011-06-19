// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

namespace LikeMagic { namespace Utility {


// Used to wrap up the types of a function pointer into a set of types.
template <typename... Types> struct TypePack
{
    /*
    template <typename T>
    struct Prepend
    {
        typedef TypePack<T, Types...> type;
    };
    */
};


}}
