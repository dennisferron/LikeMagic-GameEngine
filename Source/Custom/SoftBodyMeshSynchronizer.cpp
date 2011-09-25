// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/SoftBodyMeshSynchronizer.hpp"
#include "irrlicht.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace Bindings::Custom;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

SoftBodyMeshSynchronizer::SoftBodyMeshSynchronizer(btSoftBody* softBody_, IMeshBuffer* meshBuf_)
    : softBody(softBody_), meshBuf(meshBuf_)
{
    meshBuf->grab();

    // The vertices end up in a different order when you sync, which puts the
    // winding order backwards making the mesh invisible from the top.
    // This is a quick hack to fix the winding order until I make the irrlicht
    // vertex layout match the bullet softbody node layout.
    std::reverse(meshBuf->getIndices(), meshBuf->getIndices()+meshBuf->getIndexCount());
}

SoftBodyMeshSynchronizer::~SoftBodyMeshSynchronizer()
{
    meshBuf->drop();
}

void SoftBodyMeshSynchronizer::sync()
{
    // based on pseudocode from the bullet physics wiki

    /* Each soft body contain an array of vertices (nodes/particles_mass)   */
    btSoftBody::tNodeArray&   nodes(softBody->m_nodes);


    if ((size_t)nodes.size() != meshBuf->getVertexCount())
        throw std::runtime_error("Number of nodes in physics softbody must match number of vertices in graphics mesh.");

    /* Then, you can draw vertices...      */
    /* Node::m_x => position            */
    /* Node::m_n => normal (if meaningful)   */
    for(int j=0;j<nodes.size();++j)
    {
        btVector3 const& physPos = nodes[j].m_x;
        btVector3 const& physNorm = nodes[j].m_n;

        size_t vertexSize = 0;

        switch (meshBuf->getVertexType())
        {
            case EVT_TANGENTS:
                vertexSize = sizeof(S3DVertexTangents);
                break;
            case EVT_2TCOORDS:
                vertexSize = sizeof(S3DVertex2TCoords);
                break;
            case EVT_STANDARD:
            default:
                vertexSize = sizeof(S3DVertex);
        }

        void* vertPtr = (char*)meshBuf->getVertices() + j * vertexSize;
        S3DVertex& vert = *reinterpret_cast<irr::video::S3DVertex*>(vertPtr);

        vert.Pos.X  = physPos.getX();
        vert.Pos.Y  = physPos.getY();
        vert.Pos.Z  = physPos.getZ();

        vert.Normal.X  = physNorm.getX();
        vert.Normal.Y  = physNorm.getY();
        vert.Normal.Z  = physNorm.getZ();
    }

    meshBuf->setDirty(EBT_VERTEX);

    // Code for drawing other shapes.  May be useful later:

//    /* And edges (links/distances constraints)                        */
//    btSoftBody::tLinkArray&   links(softbody->m_links);
//
//    /* Or edges (for ropes)               */
//    /* Link::m_n[2] => pointers to nodes   */
//    for(int j=0;j<links.size();++j)
//    {
//        btSoftBody::Node*   node_0=links[j].m_n[0];
//        btSoftBody::Node*   node_1=links[j].m_n[1];
//        mygfx->DrawLine(node_0->m_x,node_1->m_x);
//
//        /* Or if you need indices...      */
//        const int indices[] =
//        {
//            int(node_0-&nodes[0]),
//            int(node_1-&nodes[0])
//        };
//    }
//
//    /* And finally, faces (triangles)                                 */
//    btSoftBody::tFaceArray&   faces(softbody->m_faces);
//
//    /* And even faces                  */
//    /* Face::m_n[3] -> pointers to nodes   */
//    for(int j=0;j<faces.size();++j)
//    {
//        btSoftBody::Node*   node_0=faces[j].m_n[0];
//        btSoftBody::Node*   node_1=faces[j].m_n[1];
//        btSoftBody::Node*   node_2=faces[j].m_n[2];
//        mygfx->DrawTriangle(node_0->m_x,node_1->m_x,node_2->m_x);
//        /* Or if you need indices...      */
//        const int         indices[]={   int(node_0-&nodes[0]),
//        int(node_1-&nodes[0]),
//        int(node_2-&nodes[0])};
//    }
}



