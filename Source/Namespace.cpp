// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/Namespace.hpp"

#include <stdexcept>

namespace LikeMagic {

Namespace::Namespace(RuntimeTypeSystem& type_system_)
    : type_system(type_system_), path(NamespacePath::global()) {}

Namespace::Namespace(RuntimeTypeSystem& type_system_, NamespacePath const path_)
    : type_system(type_system_), path(path_) {}

Namespace const Namespace::global(RuntimeTypeSystem& type_system_)
{
    return Namespace(type_system_);
}

Namespace const Namespace::subspace(std::string name) const
{
    return Namespace(type_system, path.subspace(name));
}

Namespace const Namespace::get_parent() const
{
    return Namespace(type_system, path.get_parent());
}

bool Namespace::is_root() const
{
    return path.is_root();
}

std::string Namespace::to_string() const
{
    return path.to_string();
}

std::string Namespace::get_name() const
{
    return path.get_name();
}

StaticMethods& Namespace::register_functions() const
{
    return type_system.register_functions(path);
}



}
