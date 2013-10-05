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

class ScriptedSceneNode : public scene::ISceneNode, public LM::IMarkable
{
private:
    core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[4];
    video::SMaterial Material;
    BlockPtr on_register;
    BlockPtr on_render;
    BlockPtr on_get_box;
    BlockPtr on_get_material;
    BlockPtr on_get_material_count;

public:

    virtual void mark() const;

    ScriptedSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);

    void setOnRegisterSceneNode(BlockPtr block);
    void setOnRender(BlockPtr block);
    void setOnGetBoundingBox (BlockPtr block);
    void setOnGetMaterial(BlockPtr block);
    void setOnGetMaterialCount(BlockPtr block);

    video::S3DVertex const* getExampleVertices() const;
    u16 const* getExampleIndices() const;

    virtual void OnRegisterSceneNode();
    virtual void render();
    virtual const core::aabbox3d<f32>& getBoundingBox() const;
    virtual u32 getMaterialCount() const;
    virtual video::SMaterial& getMaterial(u32 i);
};

}}
