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
#include <memory>
#include <map>

#include "boost/intrusive_ptr.hpp"
#include "boost/functional/hash.hpp"
#include "boost/unordered_map.hpp"

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class TypeIndex;

LIKEMAGIC_API TypeInfo get_info(TypeIndex const& index);

class TypeIndex
{
private:
    std::size_t id;

public:
    TypeIndex() : id(0) {}
    explicit TypeIndex(std::size_t id_) : id(id_) {}
    TypeIndex(TypeIndex const& that) : id(that.id) {}

    inline bool is_initialized() const { return id != 0; }

    inline bool operator <(TypeIndex const& that) const
        { return this->id < that.id; }

    inline bool operator ==(TypeIndex const& that) const
        { return this->id == that.id; }

    inline std::size_t get_id() const { return id; }
    inline TypeInfo get_info() const { return LM::get_info(*this); }
    inline std::string description() const { return get_info().description(); }
};

LIKEMAGIC_API TypeIndex get_index(TypeInfo const& type);
LIKEMAGIC_API TypeIndex get_class_index(TypeIndex index);

typedef std::vector<TypeIndex> TypeInfoList;
LIKEMAGIC_API extern const TypeInfoList& empty_arg_list;

LIKEMAGIC_API TypeIndex create_cpp_type_index(std::type_info const* info_, PtrType ptr_type_, RefType ref_type_, bool is_end_);
LIKEMAGIC_API TypeIndex create_bottom_ptr_type_index();
LIKEMAGIC_API TypeIndex create_namespace_type_index(std::string namespace_name);

// Value types - not const, not ptr, not ref
template <typename T>
struct TypId
{
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete;
    static TypeIndex liberal()
    {
        return create_cpp_type_index(&typeid(T), PtrType::NotPtr, RefType::ValueNonconst, false);
    }
    static TypeIndex restricted()
    {
        return create_cpp_type_index(&typeid(T), PtrType::NotPtr, RefType::ValueNonconst, true);
    }
};

#define TYPID_SPEC(type, ptrtype, reftype) \
template <typename T> \
struct TypId<type> \
{ \
    TypId() = delete; TypId(TypId const&) = delete; ~TypId() = delete; \
    static TypeIndex liberal() \
    { \
        return create_cpp_type_index(&typeid(T), ptrtype, reftype, false); \
    } \
    static TypeIndex restricted() \
    { \
        return create_cpp_type_index(&typeid(T), ptrtype, reftype, true); \
    } \
};

//TYPID_SPEC(T,             PtrType::NotPtr,        RefType::ValueNonconst)
TYPID_SPEC(T const,         PtrType::NotPtr,        RefType::ValueConst)
TYPID_SPEC(T&,              PtrType::NotPtr,        RefType::RefToNonconst)
TYPID_SPEC(T const&,        PtrType::NotPtr,        RefType::RefToConst)

TYPID_SPEC(T*,              PtrType::PtrToNonconst, RefType::ValueNonconst)
TYPID_SPEC(T* const,        PtrType::PtrToNonconst, RefType::ValueConst)
TYPID_SPEC(T*&,             PtrType::PtrToNonconst, RefType::RefToNonconst)
TYPID_SPEC(T* const&,       PtrType::PtrToNonconst, RefType::RefToConst)

TYPID_SPEC(T const*,        PtrType::PtrToConst,    RefType::ValueNonconst)
TYPID_SPEC(T const* const,  PtrType::PtrToConst,    RefType::ValueConst)
TYPID_SPEC(T const*&,       PtrType::PtrToConst,    RefType::RefToNonconst)
TYPID_SPEC(T const* const&, PtrType::PtrToConst,    RefType::RefToConst)

}
