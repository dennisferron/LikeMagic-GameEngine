// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/intrusive_ptr.hpp"
#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LM {

class AbstractTypeInfo
{
public:
    typedef std::shared_ptr<AbstractTypeInfo const> TypeInfoPtr;

    virtual std::string get_system() const = 0;
    virtual bool less(const AbstractTypeInfo& that) const = 0;
    virtual bool equals(const AbstractTypeInfo& that) const = 0;
    virtual std::size_t calc_hash() const = 0;

    virtual ~AbstractTypeInfo() = 0;

    virtual bool operator <(const AbstractTypeInfo& that) const = 0;
    virtual bool operator ==(const AbstractTypeInfo& that) const = 0;
    virtual bool get_is_const() const = 0;
    virtual TypeInfoPtr as_const() const = 0;
    virtual TypeInfoPtr as_nonconst() const = 0;
    virtual TypeInfoPtr as_ptr() const = 0;
    virtual TypeInfoPtr as_value() const = 0;
    virtual TypeInfoPtr class_type() const = 0;
    virtual std::string description() const = 0;
    virtual std::size_t hash_value() const = 0;
};

typedef std::shared_ptr<AbstractTypeInfo const> TypeInfoPtr;
typedef KeyWrapper<AbstractTypeInfo const> TypeInfoKey;

inline std::size_t hash_value(AbstractTypeInfo const& info)
{
    return info.hash_value();
}

inline std::size_t hash_value(TypeInfoPtr info_p)
{
    return info_p->hash_value();
}

}

// You need to define this once in each DLL that creates type_info objects.
#define LM_DEFINE_ABSTRACTTYPEINFO_DESTRUCTOR LM::AbstractTypeInfo::~AbstractTypeInfo() {}
