// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

namespace LikeMagic { class TypeSystem; }

namespace LikeMagic { namespace StdBindings {

// You don't call this directly; you call create_typesystem and it calls this.
// Static member function create_typesystem is DLL_PUBLIC instead of this function.
void add_bindings();

}}
