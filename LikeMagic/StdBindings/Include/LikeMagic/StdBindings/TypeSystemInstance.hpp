// LikeMagic C++ Binding Library
// Copyright 2008-2012 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"

namespace LikeMagic { namespace StdBindings {

// Use this function to create the RuntimeTypesystem object.  I put it in the StdBindings project
// to reduce the size of the LikeMagic static library when using DLL-based build.
TypeSystem* create_typesystem();

// I extended the inheritance hierarchy of TypeSystem->TypeSystem to TypeSystemInstance
// just to break the circular dependency between the LikeMagic core library and StdBindings.
// It allows class TypeSystem in libLikeMagic to be "complete" for the purposes of linking, while
// still wrapping implementation details of the initialization of TypeSystem within StdBindings.
class TypeSystemInstance : public TypeSystem
{
private:
    TypeSystemInstance();
    friend TypeSystem* create_typesystem();
};

}}
