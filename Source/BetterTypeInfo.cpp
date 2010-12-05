// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include <cstring>

namespace LikeMagic { namespace Utility {

// Used for default constructed BetterTypeInfo with no type stored in it.
struct no_type {};

BetterTypeInfo::BetterTypeInfo(std::type_info const* info_, bool is_const_, bool is_ref_, bool is_ptr_, bool is_const_ptr_)
    : info(info_), is_const(is_const_), is_ref(is_ref_), is_ptr(is_ptr_), is_const_ptr(is_const_ptr_) {}

BetterTypeInfo::BetterTypeInfo() :
    info(&typeid(no_type)),
    is_const(false), is_ref(false),
    is_ptr(false), is_const_ptr(false)
{}

BetterTypeInfo::BetterTypeInfo(BetterTypeInfo const& that) :
    info(that.info),
    is_const(that.is_const), is_ref(that.is_ref),
    is_ptr(that.is_ptr), is_const_ptr(that.is_const_ptr)
{}

bool BetterTypeInfo::equals(const AbstractTypeInfo& other) const
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
        (strcmp(info->name(), that.info->name()) == 0);
}

bool BetterTypeInfo::less(const AbstractTypeInfo& other) const
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
                        (strcmp(info->name(), that.info->name()) < 0);
}

bool BetterTypeInfo::get_is_const() const { return is_const; }
bool BetterTypeInfo::get_is_ptr() const { return is_ptr; }
bool BetterTypeInfo::get_is_ref() const { return is_ref; }
bool BetterTypeInfo::get_is_const_ptr() const { return is_const_ptr; }

TypeInfoPtr BetterTypeInfo::bare_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, false, false, false));
}

TypeInfoPtr BetterTypeInfo::as_const_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, true, is_ref, is_ptr, is_const_ptr));
}

TypeInfoPtr BetterTypeInfo::as_nonconst_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, is_ref, is_ptr, is_const_ptr));
}

TypeInfoPtr BetterTypeInfo::remove_reference() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, is_const, false, is_ptr, is_const_ptr));
}

TypeInfoPtr BetterTypeInfo::as_ptr_to_const_type() const
{
    if (!is_ptr)
        throw std::logic_error("Cannot convert type info " + describe() + " as pointer to const because source type is not a pointer.");

    return TypeInfoPtr(new BetterTypeInfo(info, is_const, is_ref, is_ptr, true));
}

TypeInfoPtr BetterTypeInfo::as_ptr_to_nonconst_type() const
{
    if (!is_ptr)
        throw std::logic_error("Cannot convert type info " + describe() + " as pointer to nonconst because source type is not a pointer.");

    return TypeInfoPtr(new BetterTypeInfo(info, is_const, is_ref, is_ptr, false));
}

TypeInfoPtr BetterTypeInfo::remove_all_const() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, is_ref, is_ptr, false));
}

std::string BetterTypeInfo::describe() const
{
    return std::string(demangle_name(info->name()))
            + (is_const? " const" : "")
            + (is_ptr? "*" : "")
            + (is_const_ptr? " const" : "")
            + (is_ref? "&" : "")
            ;
}

}}

