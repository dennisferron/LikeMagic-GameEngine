// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include <cstring>

namespace LM {

// Used for default constructed BetterTypeInfo with no type stored in it.
struct no_type {};


BetterTypeInfo::BetterTypeInfo(std::type_info const* info_, bool is_const_, bool is_ptr_)
    : info(info_), is_const(is_const_), is_ptr(is_ptr_)
{}

BetterTypeInfo::BetterTypeInfo() :
    info(&typeid(no_type)),
    is_const(false), is_ptr(false)
{}

BetterTypeInfo::BetterTypeInfo(BetterTypeInfo const& that) :
    info(that.info),
    is_const(that.is_const), is_ptr(that.is_ptr)
{}

bool BetterTypeInfo::equals(const AbstractTypeInfo& other) const
{
    // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
    // So static cast for better speed.  The base class is supposed to ensure we
    // never get called except when the other really is the same type.
    BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
    return
        is_const == that.is_const &&
        is_ptr == that.is_ptr &&
        (strcmp(info->name(), that.info->name()) == 0);
}

bool BetterTypeInfo::less(const AbstractTypeInfo& other) const
{
    // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
    // So static cast for better speed.  The base class is supposed to ensure we
    // never get called except when the other really is the same type.
    BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
    return is_const != that.is_const? is_const < that.is_const :
        is_ptr != that.is_ptr? is_ptr < that.is_ptr :
            (strcmp(info->name(), that.info->name()) < 0);
}

bool BetterTypeInfo::get_is_const() const { return is_const; }

TypeInfoPtr BetterTypeInfo::as_const() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, true, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_nonconst() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_ptr() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, is_const, true));
}

TypeInfoPtr BetterTypeInfo::as_value() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, is_const, false));
}

TypeInfoPtr BetterTypeInfo::class_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, false));
}

std::string BetterTypeInfo::get_system() const
{
    return "C++";
}

std::size_t BetterTypeInfo::calc_hash() const
{
    std::size_t seed = 0;
    boost::hash_combine(seed, is_const);
    boost::hash_combine(seed, std::string(info->name()));
    return seed;
}

std::string BetterTypeInfo::description() const
{
    return std::string(demangle_name(info->name()))
            + (is_const? " const" : "");
}

}

