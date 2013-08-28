// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include <stdexcept>

namespace LM {

template <typename T>
struct TermDeleter
{
    static void delete_if_possible(T const * const& value) { delete value; }
};

template <>
struct TermDeleter<void>
{
    static void delete_if_possible(void* value)
    {
        throw std::logic_error("Cannot auto-delete void*.");
    }
};

template <>
struct TermDeleter<const void>
{
    static void delete_if_possible(const void* value)
    {
        throw std::logic_error("Cannot auto-delete void*.");
    }
};

}

// Most pointer types can be deleted, but there may be situations
// (such as if a class has a private delete operator) when you need to
// override the definition of delete for a particular type.
#define LM_CUSTOM_DELETER(type, impl) \
namespace LM { \
    template <> struct TermDeleter<type const> \
        { static void delete_if_possible(type const*const& value) {impl;} }; }
