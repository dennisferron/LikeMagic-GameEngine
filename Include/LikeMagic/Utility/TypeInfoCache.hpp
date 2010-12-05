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

class TypeToken
{
private:
    friend class TypeInfoCache;
    friend std::size_t hash_value(TypeToken info);
    std::size_t id;

    TypeToken(std::size_t id_) : id(id_) {}

public:
    TypeToken(TypeToken const& that) : id(that.id) {}

    inline bool operator <(TypeToken const& that) const
        { return this->id < that.id; }

    inline bool operator ==(TypeToken const& that) const
        { return this->id == that.id; }

    TypeInfoPtr get_info() const;
};

inline std::size_t hash_value(TypeToken info)
{
    return hash_value(info.id);
}

class TypeInfoCache
{
private:
    static TypeInfoCache* instance;
    std::vector<std::pair<TypeToken, TypeInfoPtr>> cache;

public:

    TypeToken get_token(std::auto_ptr<AbstractTypeInfo const> candidate);

    TypeInfoPtr get_info(TypeToken tok);

    static TypeInfoCache* get_instance()
    {
        if (!instance)
            throw std::logic_error("No TypeInfoCache singleton exists!");

        return instance;
    }

    static void set_instance(TypeInfoCache* instance_) { instance = instance_; }
};


}}
