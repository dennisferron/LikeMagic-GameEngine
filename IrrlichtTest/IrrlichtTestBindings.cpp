// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/IrrlichtTest/Bindings.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

int runTest();

namespace Bindings { namespace IrrlichtTest {

DLL_PUBLIC void add_bindings(RuntimeTypeSystem& type_sys)
{
    // This needs to be done once in every DLL.
    LM_SET_TYPE_INFO(type_sys)

    auto ns_irrlicht_test = Namespace::global(type_sys).subspace("IrrlichtTest");

    LM_STATIC_FUNC(ns_irrlicht_test,, runTest)
}

}}
