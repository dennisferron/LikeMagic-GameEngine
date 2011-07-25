// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/ScriptedSceneNode.hpp"

using namespace Bindings::Irrlicht;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

void ScriptedSceneNode::mark() const
{
    on_register.mark();
    on_render.mark();
    on_get_box.mark();
    on_get_material.mark();
    on_get_material_count.mark();
}

void ScriptedSceneNode::setOnRegisterSceneNode(IoBlock block) { on_register = block; }
void ScriptedSceneNode::setOnRender(IoBlock block) { on_render = block; }
void ScriptedSceneNode::setOnGetBoundingBox (IoBlock block) { on_get_box = block; }
void ScriptedSceneNode::setOnGetMaterial(IoBlock block) { on_get_material = block; }
void ScriptedSceneNode::setOnGetMaterialCount(IoBlock block) { on_get_material_count = block; }


ScriptedSceneNode::ScriptedSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
    : scene::ISceneNode(parent, mgr, id)
{

    Material.Wireframe = true;
    Material.Lighting = false;

    Vertices[0] = video::S3DVertex(0,0,100, 1,1,0,
                    video::SColor(255,0,255,255), 0, 1);
    Vertices[1] = video::S3DVertex(100,0,-100, 1,0,0,
                    video::SColor(255,255,0,255), 1, 1);
    Vertices[2] = video::S3DVertex(0,200,0, 0,1,1,
                    video::SColor(255,255,255,0), 1, 0);
    Vertices[3] = video::S3DVertex(-100,0,-100, 0,0,1,
                    video::SColor(255,0,255,0), 0, 0);

    /*
    The Irrlicht Engine needs to know the bounding box of a scene node.
    It will use it for automatic culling and other things. Hence, we
    need to create a bounding box from the 4 vertices we use.
    If you do not want the engine to use the box for automatic culling,
    and/or don't want to create the box, you could also call
    irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
    */
    Box.reset(Vertices[0].Pos);
    for (s32 i=1; i<4; ++i)
            Box.addInternalPoint(Vertices[i].Pos);
}


/*
Before it is drawn, the irr::scene::ISceneNode::OnRegisterSceneNode()
method of every scene node in the scene is called by the scene manager.
If the scene node wishes to draw itself, it may register itself in the
scene manager to be drawn. This is necessary to tell the scene manager
when it should call irr::scene::ISceneNode::render(). For
example, normal scene nodes render their content one after another,
while stencil buffer shadows would like to be drawn after all other
scene nodes. And camera or light scene nodes need to be rendered before
all other scene nodes (if at all). So here we simply register the
scene node to render normally. If we would like to let it be rendered
like cameras or light, we would have to call
SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
After this, we call the actual
irr::scene::ISceneNode::OnRegisterSceneNode() method of the base class,
which simply lets also all the child scene nodes of this node register
themselves.
*/
void ScriptedSceneNode::OnRegisterSceneNode()
{
        if (IsVisible)
                SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();
}

/*
In the render() method most of the interesting stuff happens: The
Scene node renders itself. We override this method and draw the
tetraeder.
*/
void ScriptedSceneNode::render()
{
    on_render();

    //u16 indices[] = {	0,2,3, 2,1,3, 1,0,3, 2,0,1	};
    //video::IVideoDriver* driver = SceneManager->getVideoDriver();

    //driver->setMaterial(getMaterial(0));
    //driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    //driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 4);
}

S3DVertex const* ScriptedSceneNode::getExampleVertices() const
{
    return &Vertices[0];
}

u16 const* ScriptedSceneNode::getExampleIndices() const
{
    static u16 indices[] = {	0,2,3, 2,1,3, 1,0,3, 2,0,1  };
    return &indices[0];
}

/*
And finally we create three small additional methods.
irr::scene::ISceneNode::getBoundingBox() returns the bounding box of
this scene node, irr::scene::ISceneNode::getMaterialCount() returns the
amount of materials in this scene node (our tetraeder only has one
material), and irr::scene::ISceneNode::getMaterial() returns the
material at an index. Because we have only one material here, we can
return the only one material, assuming that no one ever calls
getMaterial() with an index greater than 0.
*/
const core::aabbox3d<f32>& ScriptedSceneNode::getBoundingBox() const
{
    if (on_get_box.empty())
        return Box;
    else
        return on_get_box.eval<aabbox3df&>();
}

u32 ScriptedSceneNode::getMaterialCount() const
{
    if (on_get_material_count.empty())
        return 1;
    else
        return static_cast<u32>(on_get_material_count.eval<double&>());
}

video::SMaterial& ScriptedSceneNode::getMaterial(u32 i)
{
    if (on_get_material.empty())
        return Material;
    else
        return on_get_material.eval<video::SMaterial&>();
}



