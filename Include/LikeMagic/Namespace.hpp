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

class Namespace;
typedef boost::intrusive_ptr<Namespace> NamespacePtr;

void intrusive_ptr_add_ref(Namespace* p);
void intrusive_ptr_release(Namespace* p);

class Namespace
{
private:
    int ref_count;

    friend void intrusive_ptr_add_ref(Namespace* p);
    friend void intrusive_ptr_release(Namespace* p);

private:

    RuntimeTypeSystem& type_system;
    NamespacePtr parent;
    std::string name;

    Namespace(RuntimeTypeSystem& type_system_);
    Namespace(RuntimeTypeSystem& type_system_, Namespace* parent_, std::string name_);

public:

    static NamespacePtr global(RuntimeTypeSystem& type_system_);
    NamespacePtr subspace(std::string name);

    NamespacePtr get_parent() const;
    bool is_root() const;
    std::string to_string() const;
    std::string get_name() const;

    template <typename T, bool is_copyable=!boost::is_abstract<T>::value>
    Class<T, is_copyable>& register_class(std::string name)
    {
        return type_system.register_class<T, is_copyable>(name, this);
    }

    template <typename T>
    Class<T, true>& register_enum(std::string name)
    {
        return type_system.register_enum<T>(name, this);
    }

    StaticMethods& register_functions();
};

}
