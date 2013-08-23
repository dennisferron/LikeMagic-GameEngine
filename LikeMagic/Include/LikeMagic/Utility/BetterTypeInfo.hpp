// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/type_traits.hpp"

#include <typeinfo>
#include <stdexcept>

#include "TypeDescr.hpp"
#include "StripModifiers.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LM {

template <typename T>
class TypId;

class BetterTypeInfo : public AbstractTypeInfo
{
private:
    template <typename T> friend class TypId;

    std::type_info const* info;
    bool obj_is_const;
    bool ptr_is_const;
    bool is_ref;
    bool is_ptr;

    BetterTypeInfo(std::type_info const* info_, bool obj_is_const_, bool ptr_is_const_, bool is_ref_, bool is_ptr_);
    BetterTypeInfo();
    BetterTypeInfo(BetterTypeInfo const& that);

protected:

    virtual std::string get_system() const;
    virtual bool less(const AbstractTypeInfo& other) const;
    virtual bool equals(const AbstractTypeInfo& other) const;
    virtual std::size_t calc_hash() const;

public:

    bool get_obj_is_const() const;
    bool get_ptr_is_const() const;
    bool get_is_ptr() const;
    bool get_is_ref() const;

    TypeInfoPtr bare_type() const;
    TypeInfoPtr as_ref() const;
    TypeInfoPtr as_ptr() const;
    TypeInfoPtr as_const_obj_type() const;
    TypeInfoPtr as_nonconst_obj_type() const;
    TypeInfoPtr as_const_ptr_type() const;
    TypeInfoPtr as_nonconst_ptr_type() const;
    TypeInfoPtr remove_reference() const;
    TypeInfoPtr remove_all_const() const;

    virtual std::string description() const;
};

template <typename T>
class TypId
{
private:

    TypId() = delete;
    TypId(TypId const&) = delete;
    ~TypId() = delete;

public:
    static TypeIndex get()
    {
        typedef StripModifiers<T> stripped;
        static TypeIndex id = TypeInfoCache::get_instance()->get_index(
                new BetterTypeInfo(
                    &typeid(typename stripped::type),
                    stripped::obj_is_const,
                    stripped::ptr_is_const,
                    stripped::is_ref,
                    stripped::is_ptr
                ));
        return id;
    }
};

}
