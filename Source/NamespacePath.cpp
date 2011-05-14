// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/NamespacePath.hpp"

namespace LikeMagic {

NamespacePath::NamespacePath()
{
}

NamespacePath::NamespacePath(NamespacePath const& other)
    : path(other.path)
{
}


NamespacePath::NamespacePath(std::vector<std::string> parent_path, std::string name)
    : path(parent_path)
{
    path.push_back(name);
}

NamespacePath::NamespacePath(std::vector<std::string> parent_path, int remove_amt)
    : path(parent_path)
{
    path.erase(path.end()+remove_amt, path.end());
}

NamespacePath NamespacePath::global()
{
    return NamespacePath();
}

NamespacePath const NamespacePath::subspace(std::string name) const
{
    return NamespacePath(this->path, name);
}

NamespacePath const NamespacePath::get_parent() const
{
    return NamespacePath(this->path, -1);
}

bool NamespacePath::is_root() const
{
    return path.empty();
}

std::string NamespacePath::to_string() const
{
    return (is_root()? "" : get_parent().to_string() + "::") + get_name();
}

std::string NamespacePath::get_name() const
{
    return is_root()? "namespace" : path.back();
}




}
