// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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


BetterTypeInfo::BetterTypeInfo(std::type_info const* info_, bool obj_is_const_, bool ptr_is_const_, bool is_ref_, bool is_ptr_)
    : info(info_), obj_is_const(obj_is_const_), ptr_is_const(ptr_is_const_), is_ref(is_ref_), is_ptr(is_ptr_)
{}

BetterTypeInfo::BetterTypeInfo() :
    info(&typeid(no_type)),
    obj_is_const(false),
    ptr_is_const(false),
    is_ref(false),
    is_ptr(false)
{}

BetterTypeInfo::BetterTypeInfo(BetterTypeInfo const& that) :
    info(that.info),
    obj_is_const(that.obj_is_const),
    ptr_is_const(that.ptr_is_const),
    is_ref(that.is_ref),
    is_ptr(that.is_ptr)
{}

bool BetterTypeInfo::equals(const AbstractTypeInfo& other) const
{
    // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
    // So static cast for better speed.  The base class is supposed to ensure we
    // never get called except when the other really is the same type.
    BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
    return
        obj_is_const == that.obj_is_const &&
        ptr_is_const == that.ptr_is_const &&
        is_ref == that.is_ref &&
        is_ptr == that.is_ptr &&
        (strcmp(info->name(), that.info->name()) == 0);
}

bool BetterTypeInfo::less(const AbstractTypeInfo& other) const
{
    // Dynamic cast is safer, but this function gets called A LOT (I profiled it).
    // So static cast for better speed.  The base class is supposed to ensure we
    // never get called except when the other really is the same type.
    BetterTypeInfo const& that = static_cast<BetterTypeInfo const&>(other);
    return
        obj_is_const != that.obj_is_const? obj_is_const < that.obj_is_const :
            ptr_is_const != that.ptr_is_const? ptr_is_const < that.ptr_is_const :
                is_ref != that.is_ref? is_ref < that.is_ref :
                    is_ptr != that.is_ptr? is_ptr < that.is_ptr :
                        (strcmp(info->name(), that.info->name()) < 0);
}

bool BetterTypeInfo::get_obj_is_const() const { return obj_is_const; }
bool BetterTypeInfo::get_ptr_is_const() const { return ptr_is_const; }
bool BetterTypeInfo::get_is_ptr() const { return is_ptr; }
bool BetterTypeInfo::get_is_ref() const { return is_ref; }

TypeInfoPtr BetterTypeInfo::bare_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, false, false, false));
}

TypeInfoPtr BetterTypeInfo::as_const_obj_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, true, ptr_is_const, is_ref, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_nonconst_obj_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, ptr_is_const, is_ref, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_const_ptr_type() const
{
    if (!is_ptr)
        throw std::logic_error("as_const_ptr_type:  source type is not a pointer.");

    return TypeInfoPtr(new BetterTypeInfo(info, obj_is_const, true, is_ref, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_nonconst_ptr_type() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, obj_is_const, false, is_ref, is_ptr));
}

TypeInfoPtr BetterTypeInfo::remove_reference() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, obj_is_const, ptr_is_const, false, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_ref() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, obj_is_const, ptr_is_const, true, is_ptr));
}

TypeInfoPtr BetterTypeInfo::as_ptr() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, obj_is_const, ptr_is_const, is_ref, true));
}


TypeInfoPtr BetterTypeInfo::remove_all_const() const
{
    return TypeInfoPtr(new BetterTypeInfo(info, false, false, is_ref, is_ptr));
}

std::string BetterTypeInfo::description() const
{
    return std::string(demangle_name(info->name()))
            + (obj_is_const? " const" : "")
            + (is_ptr? "*" : "")
            + (ptr_is_const? " const" : "")
            + (is_ref? "&" : "")
            ;
}

}}

