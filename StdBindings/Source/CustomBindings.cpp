// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/StdBindings/Bindings.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#include <boost/preprocessor/repetition/repeat.hpp>

#include "IoObject.h"

using namespace LikeMagic;

namespace Bindings { namespace Custom {

// Extension methods

IoObject* at(std::map<s32, IoObject*> const& self, s32 key)
{
    auto result = self.find(key);
    if (result == self.end())
        return NULL;
    else
        return result->second;
}

IoObject* atPut(std::map<s32, IoObject*>& self, s32 key, IoObject* value)
{
    return self[key] = value;
}

void removeAt(std::map<s32, IoObject*>& self, s32 key)
{
    self.erase(key);
}

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_std = Namespace::global(type_sys).subspace("std");

    typedef std::map<irr::s32, IoObject*> map_of_s32_IoObject;
    LM_CLASS(ns_std, map_of_s32_IoObject)
    LM_CONSTR(map_of_s32_IoObject,,)
    LM_EXTENSION_METHOD(map_of_s32_IoObject, (at)(atPut)(removeAt))

}

}}

