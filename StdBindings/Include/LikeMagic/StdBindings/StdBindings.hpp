// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace StdBindings {

// You don't call this directly; you call RuntimeTypeSystem::create and it calls this.
// Static member function RuntimeTypeSystem::create is DLL_PUBLIC instead of this function.
void add_bindings(LikeMagic::RuntimeTypeSystem& type_sys);

}}
