// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "FuncPtrTraits.hpp"

namespace LikeMagic { namespace Utility {

template <typename T, typename F, typename... ArgTypes, int... Indices>
void call_void(T t, F f, std::tuple<boost::intrusive_ptr<LikeMagic::Exprs::Expression<ArgTypes>>...> args, IndexPack<Indices...>)
{
    (t.*f)(std::get<Indices>(args)->eval()...);
}

template <typename T, typename F, typename... ArgTypes, int... Indices>
typename FuncPtrTraits<F>::R
call_nonvoid(T t, F f, std::tuple<boost::intrusive_ptr<LikeMagic::Exprs::Expression<ArgTypes>>...> args, IndexPack<Indices...>)
{
    return (t.*f)(std::get<Indices>(args)->eval()...);
}

template <typename F, typename... ArgTypes, int... Indices>
void call_static_void(F f, std::tuple<boost::intrusive_ptr<LikeMagic::Exprs::Expression<ArgTypes>>...> args, IndexPack<Indices...>)
{
    (*f)(std::get<Indices>(args)->eval()...);
}

template <typename F, typename... ArgTypes, int... Indices>
typename FuncPtrTraits<F>::R
call_static_nonvoid(F f, std::tuple<boost::intrusive_ptr<LikeMagic::Exprs::Expression<ArgTypes>>...> args, IndexPack<Indices...>)
{
    return (*f)(std::get<Indices>(args)->eval()...);
}


}}
