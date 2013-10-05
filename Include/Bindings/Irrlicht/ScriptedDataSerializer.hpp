// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"


namespace Bindings { namespace Irrlicht {

using LM::BlockPtr;
using namespace irr;
using namespace irr::io;
using namespace irr::scene;

class ScriptedDataSerializer : public ISceneUserDataSerializer, public LM::MarkableObjGraph
{
public:
    BlockPtr on_OnCreateNode;
    BlockPtr on_OnReadUserData;
    BlockPtr on_createUserData;

    virtual void OnCreateNode(ISceneNode* node);
    virtual void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);
    virtual io::IAttributes* createUserData(ISceneNode* forSceneNode);
};

}}
