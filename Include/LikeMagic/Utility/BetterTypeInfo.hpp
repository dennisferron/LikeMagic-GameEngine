// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
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

namespace LikeMagic { namespace SFMO {
    template <typename T> class Expression;
}}

namespace LikeMagic { namespace Utility {

// Used for default constructed BetterTypeInfo with no type stored in it.
struct no_type {};

class BetterTypeInfo : public AbstractTypeInfo
{
private:
    BetterTypeInfo(std::type_info const* info_, std::type_info const* raw_info_, bool is_const_, bool is_ref_, bool is_ptr_, bool is_const_ptr_)
        : info(info_), raw_info(raw_info_), is_const(is_const_), is_ref(is_ref_), is_ptr(is_ptr_), is_const_ptr(is_const_ptr_) {}

    BetterTypeInfo() :
        info(&typeid(no_type)),
        raw_info(&typeid(no_type)),
        is_const(false), is_ref(false),
        is_ptr(false), is_const_ptr(false)
    {}

    BetterTypeInfo(BetterTypeInfo const& that) :
        info(that.info),
        raw_info(that.raw_info),
        is_const(that.is_const), is_ref(that.is_ref),
        is_ptr(that.is_ptr), is_const_ptr(that.is_const_ptr)
    {}

protected:

    virtual std::type_info const* comparator_typeid() const
    {
        return &typeid(this);
    }

    virtual bool less(const AbstractTypeInfo& other) const
    {
        // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
        // So static cast for better speed.  The base class is supposed to ensure we
        // never get called except when the other really is the same type.
        BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
        return
            is_const != that.is_const? is_const < that.is_const :
                is_ref != that.is_ref? is_ref < that.is_ref :
                    is_ptr != that.is_ptr? is_ptr < that.is_ptr :
                        is_const_ptr != that.is_const_ptr? is_const_ptr < that.is_const_ptr :
                            info->before(*that.info);
    }

    virtual bool equals(const AbstractTypeInfo& other) const
    {
        // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
        // So static cast for better speed.  The base class is supposed to ensure we
        // never get called except when the other really is the same type.
        BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
        return
            is_const == that.is_const &&
            is_ref == that.is_ref &&
            is_ptr == that.is_ptr &&
            is_const_ptr == that.is_const_ptr &&
            info == that.info;
    }

    virtual std::size_t calc_hash() const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, is_const);
        boost::hash_combine(seed, is_ref);
        boost::hash_combine(seed, is_ptr);
        boost::hash_combine(seed, is_const_ptr);
        boost::hash_combine(seed, info);
        return seed;
    }

public:

    std::type_info const* info;
    std::type_info const* raw_info;
    bool is_const;  // when type is pointer, this means the pointed-at object is const; to find if the bits of the pointer are const see is_const_ptr
    bool is_ref;
    bool is_ptr;
    bool is_const_ptr;  // this indicates the address stored in the pointer is unchangeable; the pointed at object may or may not be const!

    template <typename T>
    static TypeInfoPtr create()
    {
        typedef typename StripModifiers<T>::strip stripped;

        static TypeInfoPtr cached(
            new BetterTypeInfo(
                &typeid(typename stripped::type),
                &typeid(T),
                stripped::is_const,
                stripped::is_ref,
                stripped::is_ptr,
                stripped::is_const_ptr
            )
        );

        return cached;
    }

    virtual bool get_is_ptr() const { return is_ptr; }
    virtual bool get_is_ref() const { return is_ref; }

    virtual TypeInfoPtr bare_type() const
    {
        return TypeInfoPtr(new BetterTypeInfo(info, info, false, false, false, false));
    }

    TypeInfoPtr as_const_type() const
    {
        return TypeInfoPtr(new BetterTypeInfo(info, info, true, is_ref, is_ptr, is_const_ptr));
    }

    TypeInfoPtr as_nonconst_type() const
    {
        return TypeInfoPtr(new BetterTypeInfo(info, info, false, is_ref, is_ptr, is_const_ptr));
    }

    TypeInfoPtr remove_reference() const
    {
        return TypeInfoPtr(new BetterTypeInfo(info, info, is_const, false, is_ptr, is_const_ptr));
    }

    TypeInfoPtr as_ptr_to_const_type() const
    {
        if (!is_ptr)
            throw std::logic_error("Cannot convert type info " + describe() + " as pointer to const because source type is not a pointer.");

        return TypeInfoPtr(new BetterTypeInfo(info, info, is_const, is_ref, is_ptr, true));
    }

    TypeInfoPtr as_ptr_to_nonconst_type() const
    {
        if (!is_ptr)
            throw std::logic_error("Cannot convert type info " + describe() + " as pointer to nonconst because source type is not a pointer.");

        return TypeInfoPtr(new BetterTypeInfo(info, info, is_const, is_ref, is_ptr, false));
    }

    TypeInfoPtr remove_all_const() const
    {
        return TypeInfoPtr(new BetterTypeInfo(info, info, false, is_ref, is_ptr, false));
    }

    template <typename T>
    bool is_type()
    {
        return *this == BetterTypeInfo::create<T>();
    }

    virtual std::string describe() const
    {
        return std::string(demangle_name(info->name()))
                + (is_const? " const" : "")
                + (is_ptr? "*" : "")
                + (is_const_ptr? " const" : "")
                + (is_ref? "&" : "")
                /*+ " (raw typeid: " + raw_info->name() + ")" */
                ;
    }
};


}}
