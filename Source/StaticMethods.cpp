// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/StaticMethods.hpp"
#include "LikeMagic/Namespace.hpp"

namespace LikeMagic { namespace Marshaling {

std::string error() { throw "Namespace was null!"; }

StaticMethods::StaticMethods(AbstractTypeSystem& type_system_, NamespacePtr ns)
    : DummyClass<StaticMethods>(
        ns? NamespaceTypeInfo::create_index(ns->to_string()) : BetterTypeInfo::create_index<StaticMethod>(),
        ns? ns->to_string() : error(),
        type_system_, ns)
{
}



}}
