// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

namespace Bindings { namespace Irrlicht {

using Iocaste::LikeMagicAdapters::IoBlock;
using namespace irr;

class ScriptedSceneNode : public scene::ISceneNode, public LikeMagic::IMarkable
{
private:
    core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[4];
    video::SMaterial Material;
    IoBlock on_register;
    IoBlock on_render;
    IoBlock on_get_box;
    IoBlock on_get_material;
    IoBlock on_get_material_count;

public:

    virtual void mark() const;

    ScriptedSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);

    void setOnRegisterSceneNode(IoBlock block);
    void setOnRender(IoBlock block);
    void setOnGetBoundingBox (IoBlock block);
    void setOnGetMaterial(IoBlock block);
    void setOnGetMaterialCount(IoBlock block);

    video::S3DVertex const* getExampleVertices() const;
    u16 const* getExampleIndices() const;

    virtual void OnRegisterSceneNode();
    virtual void render();
    virtual const core::aabbox3d<f32>& getBoundingBox() const;
    virtual u32 getMaterialCount() const;
    virtual video::SMaterial& getMaterial(u32 i);
};

}}
