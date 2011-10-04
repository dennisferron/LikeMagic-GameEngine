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
#include <vector>
using namespace std;

using namespace Bindings::Custom;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

SoftBodyMeshSynchronizer::SoftBodyMeshSynchronizer(btSoftBody* softBody_)
    : softBody(softBody_)
{
}

SoftBodyMeshSynchronizer::~SoftBodyMeshSynchronizer()
{
}

IMesh* SoftBodyMeshSynchronizer::createMeshFromSoftBody(btSoftBody* softBody) const
{
	SMeshBuffer* buffer = new SMeshBuffer();
	video::S3DVertex vtx;
	vtx.Color.set(255,255,255,255);

    /* Each soft body contain an array of vertices (nodes/particles_mass)   */
    btSoftBody::tNodeArray&   nodes(softBody->m_nodes);

    // Convert bullet nodes to vertices
    for(int i=0;i<nodes.size();++i)
    {
        const btSoftBody::Node&	n=nodes[i];
        const btVector3 normal=n.m_n;
        const btVector3 pos=n.m_x;

        vtx.Pos.set(pos.getX(), pos.getY(), pos.getZ());
		vtx.Normal.set(normal.getX(), normal.getY(), normal.getZ());

        // TODO: calculate texture coords
        //vtx.TCoords.set(tsx, tsy);

        buffer->Vertices.push_back(vtx);
    }

    // Convert triangles of the softbody to an index list
    for(int i=0;i<softBody->m_faces.size();++i)
    {
        const btSoftBody::Face&	f=psb->m_faces[i];

        btSoftBody::Node*   node_0=faces[j].m_n[0];
        btSoftBody::Node*   node_1=faces[j].m_n[1];
        btSoftBody::Node*   node_2=faces[j].m_n[2];

        const int indices[] =
        {
            int(node_0-&nodes[0]),
            int(node_1-&nodes[0]),
            int(node_2-&nodes[0])
        };

        for(int j=0;j<3;++j)
            buffer->Indices.push_back(indices[j]);
    }

	if (material)
		buffer->Material = *material;

	buffer->recalculateBoundingBox();

	// Default the mesh to stream because most likely we will be updating
	// the vertex positions every frame to deal with softbody movement.
	buffer->setHardwareMappingHint(EHM_STREAM);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();
	return mesh;
}

btSoftBody* SoftBodyMeshSynchronizer::createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, IMesh* mesh) const
{
	IMeshBuffer* buffer = mesh->getMeshBuffer(0);

	vector<btScalar> vertices;
	for (int i=0; i < buffer->getVertexCount(); ++i)
	    vertices.push_back(getBaseVertex(buffer, i));

    vector<int> triangles;
    for (int i=0; i < buffer->getIndexCount(); ++i)
        triangles.push_back(buffer->getIndices()[i]);

    return btSoftBodyHelpers::CreateFromTriMesh(worldInfo, &vertices[0], &triangles[0], buffer->getIndexCount()/3, false);
}

S3DVertex* SoftBodyMeshSynchronizer::getBaseVertex(IMeshBuffer* meshBuf, int n)
{
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

    // They all inherit from S3DVertex but have different sizes.
    return reinterpret_cast<irr::video::S3DVertex*>(vertPtr);
}

void SoftBodyMeshSynchronizer::animateNode(irr::scene::ISceneNode* sceneNode, irr::u32 timeMs);
{
    irr::scene::IMeshBuffer* meshBuf = sceneNode->getMesh();
    btSoftBody::tNodeArray&   nodes(softBody->m_nodes);

    if ((size_t)nodes.size() != meshBuf->getVertexCount())
        throw std::runtime_error("Number of nodes in physics softbody must exactly match number of vertices in graphics mesh.  Use SoftBodyMeshSynchronizer::createMeshFromSoftBody or btSoftBodyHelpers::CreateFromTriMesh.");

    for(int j=0;j<nodes.size();++j)
    {
        btVector3 const& physPos = nodes[j].m_x;
        btVector3 const& physNorm = nodes[j].m_n;

        S3DVertex& vert = getBaseVertex(meshBuf, j);

        vert.Pos.set(pos.getX(), pos.getY(), pos.getZ());
		vert.Normal.set(normal.getX(), normal.getY(), normal.getZ());
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


IMesh* SoftBodyMeshSynchronizer::sliceMesh(IMesh* mesh, aabbox3df bounds)
{
    IMeshBuffer* oldMeshBuf = mesh->getMeshBuffer(0);
    int oldInd[] = oldMeshBuf->getIndices();
	SMeshBuffer* newMeshBuf = new SMeshBuffer();
    LinkSplitter linkSplitter(oldMeshBuf, newMeshBuf, bounds);

    for (int i=0; i < oldMeshBuf->getIndexCount(); i += 3)
    {
        vector<int> newInd;
        for (int j=0; j<3; ++j)
            linkSplitter.processCorner(
                newInd,
                oldInd[i+(j+0)%3],
                oldInd[i+(j+1)%3],
                oldInd[i+(j+2)%3]);

        switch (newInd.size())
        {
            case 3:  // link split left triangle
                for (int j=0; j<3; ++j)
                    newMeshBuf->Indices.push_back(newInd[j]);
                break;
            case 4:  // link split left quad, make two triangles
                int A=newInd[0], B=newInd[1], C=newInd[2], D=newInd[3];
                int twoTris[2][3] = linkSplitter.distSQ(A,C) < linkSplitter.distSQ(B,D) ?
                    { {A,B,C}, {A,C,D} } : { {B,C,D}, {B,D,A} };
                for (int j=0; j<2; ++j)
                    for (int k=0; k<2; ++k)
                        newMeshBuf->Indices.push_back(twoTris[j][k]);
        }
    }

	SMesh* mesh = new SMesh();
	newMeshBuf->recalculateBoundingBox();
	newMeshBuf->setHardwareMappingHint(EHM_STATIC);
	mesh->addMeshBuffer(newMeshBuf);
	mesh->recalculateBoundingBox();
	newMeshBuf->drop();
	return mesh;
}


