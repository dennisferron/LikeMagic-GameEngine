// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#ifdef BUILDING_DLL_STD_BINDINGS
    #define BUILDING_DLL
#endif
#include "LikeMagic/Utility/DLLHelper.hpp"

#pragma once

namespace LM {

class TypeSystem;

// You don't call this directly; you call create_typesystem and it calls this.
// Static member function create_typesystem is DLL_PUBLIC instead of this function.
DLL_PUBLIC void add_bindings();

}
