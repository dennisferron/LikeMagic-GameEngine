// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/ProxyMethods.hpp"

namespace LikeMagic { namespace Marshaling {

std::string error() { throw "Namespace was null!"; }

ProxyMethods::ProxyMethods(TypeIndex type_, std::string name_, AbstractTypeSystem& type_system_, NamespacePath const namespace_)
    : DummyClass<ProxyMethods>(type_, name_, type_system_, namespace_)
{
}

AbstractCppObjProxy* ProxyMethods::create_class_proxy() const
{
    // ProxyMethods is not a class to be instantiated/called directly,
    // so do not return anything for its class proxy.  Script needs to
    // check for null/nil.
    return 0;
}


}}
