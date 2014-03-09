// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#if defined(USE_DLL_BUILD) && (defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__)
  #ifdef BUILDING_STD_BINDINGS_DLL
    #ifdef __GNUC__
      #define STD_BINDINGS_API __attribute__((dllexport))
    #else
      #define STD_BINDINGS_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define STD_BINDINGS_API __attribute__((dllimport))
    #else
      #define STD_BINDINGS_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
#else
    #define STD_BINDINGS_API
#endif

#pragma once

namespace LM {

class TypeSystem;

// You don't call this directly; you call create_typesystem and it calls this.
// Static member function create_typesystem is DLL_PUBLIC instead of this function.
STD_BINDINGS_API void add_bindings();

}
