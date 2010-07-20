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

#include "boost/intrusive_ptr.hpp"
#include "boost/functional/hash.hpp"

#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LikeMagic { namespace Utility {

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
    AbstractTypeInfo() : ref_count(0), has_cached_hash(false) {}

    virtual std::type_info const* comparator_typeid() const = 0;
    virtual bool less(const AbstractTypeInfo& that) const = 0;
    virtual bool equals(const AbstractTypeInfo& that) const = 0;
    virtual std::size_t calc_hash() const = 0;

public:

    bool operator <(const AbstractTypeInfo& that) const
    {
        if (this->comparator_typeid() < that.comparator_typeid())
            return true;
        else if (that.comparator_typeid() < this->comparator_typeid())
            return false;
        else
            return this->less(that);
    }

    bool operator ==(const AbstractTypeInfo& that) const
    {
        if (this->comparator_typeid() != that.comparator_typeid())
            return false;
        else
            return this->equals(that);
    }

    virtual bool get_is_ref() const { return false; }

    virtual bool get_is_ptr() const { return false; }

    virtual TypeInfoPtr bare_type() const
    {
        return this;
    }

    virtual TypeInfoPtr as_const_type() const
    {
        throw std::logic_error("Type variation as_const_type undefined on " + describe());
    }

    virtual TypeInfoPtr as_nonconst_type() const
    {
        throw std::logic_error("Type variation as_nonconst_type undefined on " + describe());
    }

    virtual TypeInfoPtr remove_reference() const
    {
        throw std::logic_error("Type variation remove_reference undefined on " + describe());
    }

    virtual TypeInfoPtr as_ptr_to_const_type() const
    {
        throw std::logic_error("Type variation as_ptr_to_const_type undefined on " + describe());
    }

    virtual TypeInfoPtr as_ptr_to_nonconst_type() const
    {
        throw std::logic_error("Type variation as_ptr_to_nonconst_type undefined on " + describe());
    }

    virtual TypeInfoPtr remove_all_const() const
    {
        throw std::logic_error("Type variation remove_all_const undefined on " + describe());
    }

    virtual std::string describe() const = 0;

    std::size_t hash_value() const
    {
//        static int hits = 0;
//        static int misses = 0;
//        static int count = 0;

        if (!has_cached_hash)
        {
//            ++misses;
            cached_hash = 0;
            boost::hash_combine(cached_hash, comparator_typeid());
            boost::hash_combine(cached_hash, calc_hash());
            has_cached_hash = true;
        }
//        else
//        {
//            ++hits;
//        }

//        if (++count % 100 == 0)
//            std::cout << "hits: " << hits << " misses: " << misses << " hit%: " << (1000.0*hits)/(count*10.0) << std::endl;

        return cached_hash;
    }

};

inline std::size_t hash_value(AbstractTypeInfo const& info)
{
    return info.hash_value();
}

typedef AbstractTypeInfo::TypeInfoPtr TypeInfoPtr;
typedef AbstractTypeInfo::TypeInfoKey TypeInfoKey;
typedef std::vector<TypeInfoPtr> TypeInfoList;

}}
