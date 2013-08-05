// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <vector>
#include <string>

#include "LikeMagic/Utility/TypeIndex.hpp"

namespace LikeMagic {

// Namespace wraps RuntimeTypeSystem, but RuntimeTypeSystem needs to be passed a namespace path.
// Both use templates, so to resolve the mutual dependency problem I created a separate class called
// NamespacePath that holds just the path & doesn't call RuntimeTypesystem, so that Namespace can
// use NamespacePath to communicate back to RuntimeTypeSystem what namespace to use for bound objects.

class NamespacePath
{
private:

    std::vector<std::string> path;

    NamespacePath(std::vector<std::string> parent_path, std::string name);
    NamespacePath(std::vector<std::string> parent_path, int remove_amt);

public:

    static NamespacePath global();
    NamespacePath const subspace(std::string name) const;

    NamespacePath();
    NamespacePath(NamespacePath const& other);

    NamespacePath const get_parent() const;
    bool is_root() const;
    std::string to_string() const;
    std::string get_name() const;
    LikeMagic::Utility::TypeIndex get_type() const;
};

}
