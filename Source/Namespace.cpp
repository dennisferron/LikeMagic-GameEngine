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

void intrusive_ptr_add_ref(Namespace* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(Namespace* p)
{
    if (!--(p->ref_count))
        delete p;
}

Namespace::Namespace(RuntimeTypeSystem& type_system_)
    : ref_count(0), type_system(type_system_), parent(this), name("global") {}

Namespace::Namespace(RuntimeTypeSystem& type_system_, Namespace* parent_, std::string name_)
    : ref_count(0), type_system(type_system_), parent(parent_), name(name_) {}

NamespacePtr Namespace::global(RuntimeTypeSystem& type_system_) { return new Namespace(type_system_); }
NamespacePtr Namespace::subspace(std::string name) { return new Namespace(type_system, this, name); }

NamespacePtr Namespace::get_parent() const { return parent; }
bool Namespace::is_root() const { return parent == this; }
std::string Namespace::to_string() const { return (is_root()? "" : parent->to_string() + " ") + name; }
std::string Namespace::get_name() const { return name; }

StaticMethods& Namespace::register_functions()
{
    return type_system.register_functions(this);
}



}
