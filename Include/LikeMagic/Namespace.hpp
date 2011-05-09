// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/RuntimeTypeSystem.hpp"

namespace LikeMagic {

using namespace LikeMagic::Marshaling;

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::EnumHelper;

// Namespace wraps RuntimeTypeSystem, but RuntimeTypeSystem needs to be passed a namespace path.
// Both use templates, so to resolve the mutual dependency problem I created a separate class called
// NamespacePath that holds just the path & doesn't call RuntimeTypesystem, so that Namespace can
// use NamespacePath to communicate back to RuntimeTypeSystem what namespace to use for bound objects.

class Namespace
{
private:

    RuntimeTypeSystem& type_system;
    NamespacePath const path;

    Namespace(RuntimeTypeSystem& type_system_);
    Namespace(RuntimeTypeSystem& type_system_, NamespacePath const path_);

public:

    static Namespace const global(RuntimeTypeSystem& type_system_);
    Namespace const subspace(std::string name) const;

    Namespace const get_parent() const;
    bool is_root() const;
    std::string to_string() const;
    std::string get_name() const;

    template <typename T, bool is_copyable=!boost::is_abstract<T>::value>
    Class<T, is_copyable>& register_class(std::string name) const
    {
        return type_system.register_class<T, is_copyable>(name, path);
    }

    template <typename T>
    Class<T, true>& register_enum(std::string name) const
    {
        return type_system.register_enum<T>(name, path);
    }

    StaticMethods& register_functions() const;
};

}
