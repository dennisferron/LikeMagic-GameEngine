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
    bool is_const;
    bool is_ptr;

    BetterTypeInfo(std::type_info const* info_, bool is_const_, bool is_ptr_);
    BetterTypeInfo();
    BetterTypeInfo(BetterTypeInfo const& that);

protected:

    virtual std::string get_system() const;
    virtual bool less(const AbstractTypeInfo& other) const;
    virtual bool equals(const AbstractTypeInfo& other) const;
    virtual std::size_t calc_hash() const;

public:

    virtual bool get_is_const() const;
    virtual TypeInfoPtr as_const() const;
    virtual TypeInfoPtr as_nonconst() const;
    virtual TypeInfoPtr as_ptr() const;
    virtual TypeInfoPtr as_value() const;
    virtual TypeInfoPtr class_type() const;
    virtual std::string description() const;
};

// Value types - not const, not ptr
template <typename T>
struct TypId
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
            new BetterTypeInfo(&typeid(T), false, false));
    }
};

// Const value - is const, not ptr
template <typename T>
struct TypId<T const>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
            new BetterTypeInfo(&typeid(T), true, false));
    }
};

// Nonconst ptr - not const, is ptr
template <typename T>
struct TypId<T*>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
            new BetterTypeInfo(&typeid(T), false, true));
    }
};

// ptr to const - is const, is ptr
template <typename T>
struct TypId<T const*>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
                new BetterTypeInfo(&typeid(T), true, true));
    }
};

// nonconst ref marshals as nonconst ptr
template <typename T>
struct TypId<T&>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
                new BetterTypeInfo(&typeid(T), false, true));
    }
};

// const ref marshals as const ptr
template <typename T>
struct TypId<T const&>
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex get()
    {
        return TypeInfoCache::get_instance()->get_index(
                new BetterTypeInfo(&typeid(T), true, true));
    }
};

}
