// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic { namespace Utility {

template <typename T>
struct StripConst
{
    typedef T type;
};


template <typename T>
struct StripConst<T const&>
{
    typedef typename StripConst<T&>::type type;
};


template <typename T>
struct StripConst<T const>
{
    typedef typename StripConst<T>::type type;
};

template <typename T>
struct StripConst<T const*>
{
    typedef T* type;
};



}}


