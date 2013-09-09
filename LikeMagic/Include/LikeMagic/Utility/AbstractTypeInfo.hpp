// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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

#include "boost/intrusive_ptr.hpp"
#include "boost/functional/hash.hpp"

#include "LikeMagic/Utility/TypeInfoCache.hpp"
#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LM {

class AbstractTypeInfo;
void intrusive_ptr_add_ref(AbstractTypeInfo const* p);
void intrusive_ptr_release(AbstractTypeInfo const* p);

class AbstractTypeInfo
{
public:
    typedef boost::intrusive_ptr<AbstractTypeInfo const> TypeInfoPtr;
    typedef KeyWrapper<AbstractTypeInfo const> TypeInfoKey;

private:
    friend void intrusive_ptr_add_ref(AbstractTypeInfo const* p);
    friend void intrusive_ptr_release(AbstractTypeInfo const* p);

    mutable int ref_count;
    mutable bool has_cached_hash;
    mutable std::size_t cached_hash;

protected:
    AbstractTypeInfo();
    virtual ~AbstractTypeInfo();

    virtual std::string get_system() const = 0;
    virtual bool less(const AbstractTypeInfo& that) const = 0;
    virtual bool equals(const AbstractTypeInfo& that) const = 0;
    virtual std::size_t calc_hash() const = 0;

public:

    bool operator <(const AbstractTypeInfo& that) const;
    bool operator ==(const AbstractTypeInfo& that) const;
    virtual bool get_is_const() const;
    virtual TypeInfoPtr as_const() const;
    virtual TypeInfoPtr as_nonconst() const;
    virtual TypeInfoPtr as_ptr() const;
    virtual TypeInfoPtr as_value() const;
    virtual TypeInfoPtr class_type() const;
    virtual std::string description() const = 0;
    std::size_t hash_value() const;
    TypeIndex get_index() const;
};

std::size_t hash_value(AbstractTypeInfo const& info);
std::size_t hash_value(TypeInfoPtr info_p);

typedef AbstractTypeInfo::TypeInfoKey TypeInfoKey;

}
