// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <string>
#include <typeinfo>

namespace LikeMagic { namespace Utility {

std::string demangle_name(std::string type_name);

template <typename U>
struct TypeDescr
{
    static std::string text() { return demangle_name(typeid(U).name()); }
};

template <>
struct TypeDescr<int> { static std::string text() { return "int"; } };

template <>
struct TypeDescr<void> { static std::string text() { return "void"; } };

template <typename U>
struct TypeDescr<const U> { static std::string text() { return "const " + TypeDescr<U>::text(); } };

template <typename U>
struct TypeDescr<U&> { static std::string text() { return TypeDescr<U>::text() + "&"; } };

template <typename U>
struct TypeDescr<U*> { static std::string text() { return TypeDescr<U>::text() + "*"; } };

template <typename U>
struct TypeDescr<U const *> { static std::string text() { return TypeDescr<U>::text() + " const*"; } };

template <typename U>
struct TypeDescr<U * const> { static std::string text() { return TypeDescr<U>::text() + " * const"; } };

template <typename U>
struct TypeDescr<U const * const> { static std::string text() { return TypeDescr<U>::text() + " const * const"; } };

}}
