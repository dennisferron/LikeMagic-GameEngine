// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"

#include <cstring>
#include <sstream>

namespace LM {

LIKEMAGIC_API TypeInfo create_cpp_type_info(std::type_info const* info_, PtrType ptr_type_, RefType ref_type_, bool is_end_)
{
    return TypeInfo { "C++", demangle_name(info_->name()), ptr_type_, ref_type_, is_end_ };
}

LIKEMAGIC_API TypeIndex create_cpp_type_index(std::type_info const* info_, PtrType ptr_type_, RefType ref_type_, bool is_end_)
{
    return get_index(create_cpp_type_info(info_, ptr_type_, ref_type_, is_end_));
}

LIKEMAGIC_API TypeInfo create_namespace_type_info(std::string namespace_name)
{
    return TypeInfo { "namespace", namespace_name, PtrType::NotPtr, RefType::ValueNonconst, false };
}

LIKEMAGIC_API TypeIndex create_namespace_type_index(std::string namespace_name)
{
    return get_index(create_namespace_type_info(namespace_name));
}

LIKEMAGIC_API TypeInfo create_bottom_ptr_type_info()
{
    return TypeInfo { "bottom ptr system", "", PtrType::NotPtr, RefType::ValueNonconst, false };
}

LIKEMAGIC_API TypeIndex create_bottom_ptr_type_index()
{
    return get_index(create_bottom_ptr_type_info());
}

}
