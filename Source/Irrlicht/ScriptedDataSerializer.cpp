// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/ScriptedDataSerializer.hpp"

using namespace Bindings::Irrlicht;
using namespace irr;
using namespace irr::io;

void ScriptedDataSerializer::OnCreateNode(ISceneNode* node)
{
    if (!on_OnCreateNode.empty())
        on_OnCreateNode(node);
}

void ScriptedDataSerializer::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
    if (!on_OnReadUserData.empty())
        on_OnReadUserData(forSceneNode, userData);
}

io::IAttributes* ScriptedDataSerializer::createUserData(ISceneNode* forSceneNode)
{
    if (!on_createUserData.empty())
        return on_createUserData.eval<io::IAttributes*>(forSceneNode);
    else
        return 0;
}
