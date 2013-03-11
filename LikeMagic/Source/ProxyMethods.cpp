// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/ProxyMethods.hpp"
#include "LikeMagic/SFMO/NamespaceProxy.hpp"

namespace LikeMagic { namespace Marshaling {

std::string error() { throw "Namespace was null!"; }

ProxyMethods::ProxyMethods(TypeIndex type_, std::string name_, AbstractTypeSystem& type_system_, NamespacePath const namespace_)
    : DummyClass<ProxyMethods>(type_, name_, type_system_, namespace_)
{
}


AbstractCppObjProxy* ProxyMethods::create_class_proxy() const
{
    // LikeMagic requires a proxy of some sort to be attached to script objects
    // if you want to call LikeMagic methods such as lm_get_type on them.
    return NamespaceProxy::create(this, type_system);
}



}}
