// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "boost/shared_ptr.hpp"
#include <stdexcept>

namespace LM {


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
    std::shared_ptr<T const> key;

    KeyWrapper() {}
    KeyWrapper(T const* key_) : key(key_) {}
    KeyWrapper(std::shared_ptr<T const> key_) : key(key_) {}

    inline bool operator <(KeyWrapper<T> const& that) const
    {
        if (this->key == nullptr)
            throw std::logic_error("this->key is null");

        if (that.key == nullptr)
            throw std::logic_error("this->key is null");

        std::cout << "this->key->get_system() " << this->key->get_system() << std::endl;
        std::cout << "that.key->get_system() " << that.key->get_system() << std::endl;

        return *this->key < *that.key;
    }

    inline bool operator ==(KeyWrapper<T> const& that) const
    {
        if (this->key == nullptr)
            throw std::logic_error("this->key is null");

        if (that.key == nullptr)
            throw std::logic_error("this->key is null");

        std::cout << "this->key->get_system() " << this->key->get_system() << std::endl;
        std::cout << "that.key->get_system() " << that.key->get_system() << std::endl;

        return *this->key == *that.key;
    }
};

// Convenience function.
template <typename T>
KeyWrapper<T> make_key_wrapper(std::shared_ptr<T> key) { return KeyWrapper<T>(key); }

template <typename T>
inline std::size_t hash_value(KeyWrapper<T> const& kw) { return kw.key->hash_value(); }

}
