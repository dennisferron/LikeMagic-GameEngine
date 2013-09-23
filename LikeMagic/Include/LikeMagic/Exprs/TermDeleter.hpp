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

struct AbstractTermDeleter
{
    virtual void delete_if_possible(void const* value) const = 0;
};

template <typename T>
struct TermDeleter : public AbstractTermDeleter
{
    virtual void delete_if_possible(void const* value) const
    {
        delete reinterpret_cast<T const*>(value);
    }
};

template <>
struct TermDeleter<void> : public AbstractTermDeleter
{
    virtual void delete_if_possible(void const* value) const
    {
        throw std::logic_error("Cannot auto-delete void*.");
    }
};

template <>
struct TermDeleter<const void> : public AbstractTermDeleter
{
    virtual void delete_if_possible(const void* value) const
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
    template <> struct TermDeleter<type const> : public AbstractTermDeleter \
        { virtual void delete_if_possible(void const* value) const {impl;} }; }
