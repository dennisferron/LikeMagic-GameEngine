// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LM {

union ValuePtr
{
    void const* as_const;
    void* as_nonconst;

    ValuePtr(void const* ptr) : as_const(ptr) {}
    ValuePtr(void* ptr) : as_nonconst(ptr) {}
    ValuePtr(std::nullptr_t ptr) : as_nonconst(ptr) {}
};

template <typename T>
struct GetValuePtr
{
    static void* value(ValuePtr ptr) { return ptr.as_nonconst; }
};

template <typename T>
struct GetValuePtr<T*>
{
    static void* value(ValuePtr ptr) { return ptr.as_nonconst; }
};

template <typename T>
struct GetValuePtr<T const>
{
    static void const* value(ValuePtr ptr) { return ptr.as_const; }
};

template <typename T>
struct GetValuePtr<T const*>
{
    static void const* value(ValuePtr ptr) { return ptr.as_const; }
};

}
