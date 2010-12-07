// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>

#include "boost/intrusive_ptr.hpp"
#include "boost/functional/hash.hpp"
#include "boost/unordered_map.hpp"

#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LikeMagic { namespace Utility {

class AbstractTypeInfo;
typedef boost::intrusive_ptr<AbstractTypeInfo const> TypeInfoPtr;
typedef std::vector<TypeInfoPtr> TypeInfoList;

class TypeInfoCache;

class TypeIndex
{
private:
    friend class TypeInfoCache;
    friend std::size_t hash_value(TypeIndex info);
    std::size_t id;

    TypeIndex(std::size_t id_) : id(id_) {}

public:
    TypeIndex() : id(-1) {}
    TypeIndex(TypeIndex const& that) : id(that.id) {}

    inline bool operator <(TypeIndex const& that) const
        { return this->id < that.id; }

    inline bool operator ==(TypeIndex const& that) const
        { return this->id == that.id; }

    TypeInfoPtr get_info() const;
};

inline std::size_t hash_value(TypeIndex info)
{
    return hash_value(info.id);
}

class TypeInfoCache
{
private:
    static TypeInfoCache* instance;
    boost::unordered_map<TypeInfoPtr, TypeIndex> info_to_index;
    std::vector<TypeInfoPtr> index_to_info;

    void add(TypeInfoPtr candidate);

public:

    TypeIndex get_index(TypeInfoPtr candidate);
    TypeInfoPtr get_info(TypeIndex tok);

    // I'm not a fan of singletons but in this case it makes sense.
    static TypeInfoCache* get_instance()
    {
        if (!instance)
            throw std::logic_error("Error:  TypeInfoCache instance has not been created yet!");

        return instance;
    }

    static void set_instance(TypeInfoCache* instance_);
};


}}
