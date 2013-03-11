// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/StaticMethods.hpp"
#include "LikeMagic/SFMO/NamespaceProxy.hpp"

using namespace LikeMagic::SFMO;

namespace LikeMagic { namespace Marshaling {

StaticMethods::StaticMethods(AbstractTypeSystem& type_system_, NamespacePath const ns)
    : DummyClass<StaticMethods>(
        ns.get_type(),
        ns.get_name(),
        type_system_,
        ns.get_parent()
    ),
    static_method_type(BetterTypeInfo::create_index<StaticMethod>())
{
}


// Needs a custom class proxy creator to create namespaces as StaticMethods terms
// so that functions can be called off them.
AbstractCppObjProxy* StaticMethods::create_class_proxy() const
{
    return NamespaceProxy::create(this, type_system);
}



}}
