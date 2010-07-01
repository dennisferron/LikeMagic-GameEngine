// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "FuncPtrTraits.hpp"

namespace LikeMagic { namespace Utility {

template <typename T>
struct MakeCall
{

    template <typename F, typename... ArgTypes, int... Indices>
    static void call_void(T t, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        (t.*f)(std::get<Indices>(args)->eval()...);
    }

    template <typename F, typename... ArgTypes, int... Indices>
    static typename FuncPtrTraits<F>::R
    call_nonvoid(T t, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        return (t.*f)(std::get<Indices>(args)->eval()...);
    }

};

/*
// Call by pointer
template <typename T>
struct MakeCall<T*>
{

    template <typename F, typename... ArgTypes, int... Indices>
    static void call_void(T* t, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        (t->*f)(std::get<Indices>(args)->eval()...);
    }

    template <typename F, typename... ArgTypes, int... Indices>
    static typename FuncPtrTraits<F>::R
    call_nonvoid(T* t, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        return (t->*f)(std::get<Indices>(args)->eval()...);
    }

};
*/

template <>
struct MakeCall<StaticMethod>
{

    template <typename F, typename... ArgTypes, int... Indices>
    static void call_void(StaticMethod dummy_obj, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        (*f)(std::get<Indices>(args)->eval()...);
    }

    template <typename F, typename... ArgTypes, int... Indices>
    static typename FuncPtrTraits<F>::R
    call_nonvoid(StaticMethod dummy_obj, F f, std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> args, IndexPack<Indices...>)
    {
        return (*f)(std::get<Indices>(args)->eval()...);
    }

};

}}
