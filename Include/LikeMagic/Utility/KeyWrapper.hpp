// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "boost/shared_ptr.hpp"

namespace LikeMagic { namespace Utility {


// Used to wrap a polymorphic type that has an abstract < operator
// so it can be used as a key in a std::map or std::set.
// (Standard containers require keys to be a value type, but
// C++ polymorphism works properly only with references and pointers.
// Attempting to put a polymorphic key into a standard container
// would slice it (google "C++ slicing problem") and be VERY BAD.
// Hence this wrapper, which can itself be a value type while
// still holding a polymorphic type by pointer.)
template <typename T>
struct KeyWrapper
{
    boost::intrusive_ptr<T const> key;

    KeyWrapper() {}
    KeyWrapper(T const* key_) : key(key_) {}
    KeyWrapper(boost::intrusive_ptr<T const> key_) : key(key_) {}

    inline bool operator <(KeyWrapper<T> const& that) const
        { return *this->key < *that.key; }

    inline bool operator ==(KeyWrapper<T> const& that) const
        { return *this->key == *that.key; }
};

// Convenience function.
template <typename T>
KeyWrapper<T> make_key_wrapper(boost::intrusive_ptr<T> key) { return KeyWrapper<T>(key); }

template <typename T>
inline std::size_t hash_value(KeyWrapper<T> const& kw) { return kw.key->hash_value(); }

}}
