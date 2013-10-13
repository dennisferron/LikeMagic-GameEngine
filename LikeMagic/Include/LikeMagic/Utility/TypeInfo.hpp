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

struct TypeInfo
{
    std::string system;
    std::string name;
    bool is_const;
    bool is_ptr;

    inline bool operator ==(const TypeInfo& that) const
        { return system==that.system && name==that.name && is_const==that.is_const && is_ptr==that.is_ptr; }
    inline bool get_is_const() const { return is_const; }
    inline TypeInfo as_const() const { return { system, name, true, is_ptr }; }
    inline TypeInfo as_nonconst() const { return { system, name, false, is_ptr }; }
    inline TypeInfo as_ptr() const { return { system, name, is_const, true }; }
    inline TypeInfo as_value() const { return { system, name, is_const, false }; }
    inline TypeInfo class_type() const { return { system, name, false, false }; }
    inline std::string description() const
        { return system + " " + name + (is_const?" const":"") + (is_ptr?"*":""); }
};

LIKEMAGIC_API TypeInfo create_namespace_type_info(std::string namespace_name);
LIKEMAGIC_API TypeInfo create_bottom_ptr_type_info();
LIKEMAGIC_API TypeInfo create_cpp_type_info(std::type_info const* info_, bool is_const_, bool is_ptr_);


}
