// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/type_traits.hpp"

#include <typeinfo>
#include <stdexcept>

#include "TypeDescr.hpp"
#include "StripModifiers.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"

namespace LM {

LIKEMAGIC_API TypeInfoPtr create_cpp_type_info(std::type_info const* info_, bool is_const_, bool is_ptr_);
LIKEMAGIC_API TypeIndex create_cpp_type_index(std::type_info const* info_, bool is_const_, bool is_ptr_);

// Value types - not const, not ptr
template <typename T>
struct TypId
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), false, false);
    }
};

// Const value - is const, not ptr
template <typename T>
struct TypId<T const>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), true, false);
    }
};

// Nonconst ptr - not const, is ptr
template <typename T>
struct TypId<T*>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), false, true);
    }
};

// ptr to const - is const, is ptr
template <typename T>
struct TypId<T const*>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), true, true);
    }
};

// nonconst ref marshals as nonconst ptr
template <typename T>
struct TypId<T&>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), false, true);
    }
};

// const ref marshals as const ptr
template <typename T>
struct TypId<T const&>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return create_cpp_type_index(&typeid(T), true, true);
    }
};

}
