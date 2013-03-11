// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
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
#include <map>

#include "boost/intrusive_ptr.hpp"
#include "boost/functional/hash.hpp"
#include "boost/unordered_map.hpp"

#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LikeMagic { namespace Utility {

class AbstractTypeInfo;
typedef boost::intrusive_ptr<AbstractTypeInfo const> TypeInfoPtr;

class TypeInfoCache;

class TypeIndex
{
private:
    friend class TypeInfoCache;
    friend std::size_t hash_value(TypeIndex info);
    std::size_t id;
    std::size_t class_id;

public:
    TypeIndex() : id(-1), class_id(-1) {}
    explicit TypeIndex(std::size_t id_, std::size_t class_id_) : id(id_), class_id(class_id_) {}
    TypeIndex(TypeIndex const& that) : id(that.id), class_id(that.class_id) {}

    inline bool operator <(TypeIndex const& that) const
        { return this->id < that.id; }

    inline bool operator ==(TypeIndex const& that) const
        { return this->id == that.id; }

    inline TypeIndex class_type() const
        { return TypeIndex(class_id, class_id); }

    inline bool is_class_type() const
        { return id == class_id; }

    inline std::size_t get_id() const { return id; }
    inline std::size_t get_class_id() const { return class_id; }

    TypeInfoPtr get_info() const;
    std::string describe() const;
};

inline std::size_t hash_value(TypeIndex info)
{
    return boost::hash_value(info.id);
}

typedef std::vector<TypeIndex> TypeInfoList;

}}
