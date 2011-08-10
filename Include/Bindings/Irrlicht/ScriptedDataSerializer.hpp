// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"


namespace Bindings { namespace Irrlicht {

using LikeMagic::Backends::Io::IoBlock;
using namespace irr;
using namespace irr::io;
using namespace irr::scene;

class ScriptedDataSerializer : public ISceneUserDataSerializer, public LikeMagic::MarkableObjGraph
{
public:
    IoBlock on_OnCreateNode;
    IoBlock on_OnReadUserData;
    IoBlock on_createUserData;

    virtual void OnCreateNode(ISceneNode* node);
    virtual void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);
    virtual io::IAttributes* createUserData(ISceneNode* forSceneNode);
};

}}
