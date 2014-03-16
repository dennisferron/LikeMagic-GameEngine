// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"
#include <string>

namespace LM {

enum class PtrType
{
    NotPtr,
    PtrToNonconst,
    PtrToConst
};

enum class RefType
{
    ValueNonconst,
    ValueConst,
    RefToNonconst,
    RefToConst,
    Metaclass
};

struct TypeInfo
{
private:

    inline static RefType as_const(RefType ref_type)
    {
        switch (ref_type)
        {
            case RefType::ValueNonconst: return RefType::ValueConst;
            case RefType::RefToNonconst: return RefType::RefToConst;
            case RefType::Metaclass: return RefType::ValueConst;
            default: return ref_type; // already const so no change
        };
    }

    inline static RefType as_nonconst(RefType ref_type)
    {
        switch (ref_type)
        {
            case RefType::ValueConst: return RefType::ValueNonconst;
            case RefType::RefToConst: return RefType::RefToNonconst;
            case RefType::Metaclass: return RefType::ValueNonconst;
            default: return ref_type; // already nonconst so no change
        };
    }

    inline static RefType as_not_meta(RefType ref_type)
    {
        switch (ref_type)
        {
            case RefType::Metaclass: return RefType::ValueNonconst;
            default: return ref_type; // already nonconst so no change
        };
    }

public:
    std::string system;
    std::string name;
    PtrType ptr_type;
    RefType ref_type;
    bool is_restricted;

    inline bool operator ==(const TypeInfo& that) const
        { return system==that.system && name==that.name
            && ptr_type==that.ptr_type
            && ref_type==that.ref_type
            && is_restricted==that.is_restricted; }

    inline TypeInfo as_const_value() const
    {
        return { system, name, ptr_type, as_const(ref_type), is_restricted };
    }

    inline TypeInfo as_nonconst_value() const
    {
        return { system, name, ptr_type, as_nonconst(ref_type), is_restricted };
    }

    inline TypeInfo as_ptr_to_const() const
    {
        return { system, name, PtrType::PtrToConst, as_not_meta(ref_type), is_restricted };
    }

    inline TypeInfo as_ptr_to_nonconst() const
    {
        return { system, name, PtrType::PtrToNonconst, as_not_meta(ref_type), is_restricted };
    }

    inline TypeInfo as_ref_to_nonconst() const
    {
        return { system, name, ptr_type, RefType::RefToNonconst, is_restricted };
    }

    inline TypeInfo as_ref_to_const() const
    {
        return { system, name, ptr_type, RefType::RefToConst, is_restricted };
    }

    inline TypeInfo as_restricted() const { return { system, name, ptr_type, ref_type, true }; }

    inline TypeInfo class_type() const { return { system, name, PtrType::NotPtr, RefType::Metaclass, false }; }

    inline std::string description() const
        { return
              (ref_type == RefType::Metaclass? "(metaclass) ":"")
            + system + " " + name
            + (ptr_type == PtrType::PtrToConst?" const":"") + (ptr_type != PtrType::NotPtr?"*":"")
            + (ref_type == RefType::ValueConst || ref_type == RefType::RefToConst? " const" : "")
            + (ref_type == RefType::RefToNonconst || ref_type == RefType::RefToConst? "&":"")
            + (is_restricted? " (end)" : ""); }
};

LIKEMAGIC_API TypeInfo create_namespace_type_info(std::string namespace_name);
LIKEMAGIC_API TypeInfo create_bottom_ptr_type_info();
LIKEMAGIC_API TypeInfo create_cpp_type_info(std::type_info const* info_, PtrType ptr_type_, RefType ref_type_, bool is_restricted_);

}
