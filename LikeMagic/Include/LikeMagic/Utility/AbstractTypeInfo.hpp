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

#include "LikeMagic/Utility/KeyWrapper.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class AbstractTypeInfo;
typedef boost::intrusive_ptr<AbstractTypeInfo const> TypeInfoPtr;
LIKEMAGIC_API void intrusive_ptr_add_ref(AbstractTypeInfo const* p);
LIKEMAGIC_API void intrusive_ptr_release(AbstractTypeInfo const* p);

class AbstractTypeInfo
{
public:
    typedef boost::intrusive_ptr<AbstractTypeInfo const> TypeInfoPtr;
    typedef KeyWrapper<AbstractTypeInfo const> TypeInfoKey;

private:
    friend LIKEMAGIC_API void intrusive_ptr_add_ref(AbstractTypeInfo const* p);
    friend LIKEMAGIC_API void intrusive_ptr_release(AbstractTypeInfo const* p);

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
    virtual TypeInfoPtr as_const() const = 0;
    virtual TypeInfoPtr as_nonconst() const = 0;
    virtual TypeInfoPtr as_ptr() const = 0;
    virtual TypeInfoPtr as_value() const = 0;
    virtual TypeInfoPtr class_type() const = 0;
    virtual std::string description() const = 0;
    virtual std::size_t hash_value() const;
};

std::size_t hash_value(AbstractTypeInfo const& info);
std::size_t hash_value(TypeInfoPtr info_p);

typedef AbstractTypeInfo::TypeInfoKey TypeInfoKey;

}
