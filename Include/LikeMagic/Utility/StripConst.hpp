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


