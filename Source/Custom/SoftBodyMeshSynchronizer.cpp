// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/SoftBodyMeshSynchronizer.hpp"
#include "Bindings/Custom/MeshTools.hpp"
#include "irrlicht.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
using namespace std;

using namespace Bindings::Custom;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

SoftBodyMeshSynchronizer::SoftBodyMeshSynchronizer(btSoftBody* softBody_, irr::scene::IMeshBuffer* meshBuf_)
    : softBody(softBody_), meshBuf(meshBuf_)
{
}

SoftBodyMeshSynchronizer::~SoftBodyMeshSynchronizer()
{
}

void SoftBodyMeshSynchronizer::sync()
{
    btSoftBody::tNodeArray&   nodes(softBody->m_nodes);

    if ((size_t)nodes.size() != meshBuf->getVertexCount())
        throw std::runtime_error("Number of nodes in physics softbody must exactly match number of vertices in graphics mesh.  Use MeshTools::createMeshFromSoftBody or MeshTools::createSoftBodyFromMesh.");

    for(int j=0;j<nodes.size();++j)
    {
        btVector3 const& physPos = nodes[j].m_x;
        btVector3 const& physNorm = nodes[j].m_n;

        S3DVertex& vert = MeshTools::getBaseVertex(meshBuf, j);

        vert.Pos.set(physPos.getX(), physPos.getY(), physPos.getZ());
		vert.Normal.set(physNorm.getX(), physNorm.getY(), physNorm.getZ());
    }

    meshBuf->setDirty(EBT_VERTEX);

    // TODO:  Get the code for update / reset and make it into a separate function
    // to use for resetting softbody link stresses and face areas.
    // Calling this every frame makes the mesh act like taffy, but rounding errors grow too.
    // We could avoid accumulating rounding errors making the mesh grow in weird ways by
    // reducing down the link len and areas slightly so that the mesh would tend to pull back
    // together over a long period of time.
    //softBody->m_bUpdateRtCst = true;
}

