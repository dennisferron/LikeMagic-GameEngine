// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

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


IMesh* MeshTools::createMeshFromSoftBody(btSoftBody* softBody)
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
        auto	faces = softBody->m_faces;

        btSoftBody::Node*   node_0=faces[i].m_n[0];
        btSoftBody::Node*   node_1=faces[i].m_n[1];
        btSoftBody::Node*   node_2=faces[i].m_n[2];

        const int indices[] =
        {
            int(node_0-&nodes[0]),
            int(node_1-&nodes[0]),
            int(node_2-&nodes[0])
        };

        for(int j=0;j<3;++j)
            buffer->Indices.push_back(indices[j]);
    }

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

btSoftBody* MeshTools::createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, IMesh* mesh)
{
	IMeshBuffer* buffer = mesh->getMeshBuffer(0);

	vector<btScalar> vertices;
	for (int i=0; i < buffer->getVertexCount(); ++i)
	{
	    vector3df p = getBaseVertex(buffer, i).Pos;
	    vertices.push_back(p.X);
	    vertices.push_back(p.Y);
	    vertices.push_back(p.Z);
	}

    vector<int> triangles;
    for (int i=0; i < buffer->getIndexCount(); ++i)
        triangles.push_back(buffer->getIndices()[i]);

    return btSoftBodyHelpers::CreateFromTriMesh(worldInfo, &vertices[0], &triangles[0], buffer->getIndexCount()/3, false);
}

S3DVertex& MeshTools::getBaseVertex(IMeshBuffer* meshBuf, int n)
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

    void* vertPtr = (char*)meshBuf->getVertices() + n * vertexSize;

    // They all inherit from S3DVertex
    return *reinterpret_cast<irr::video::S3DVertex*>(vertPtr);
}


// Adds point b based on links to adjacent points a and c
void MeshTools::LinkSplitter::processCorner(vector<int>& newInd, int a, int b, int c)
{
    // Add b itself if it's in the box
    if (inBox(b))
        newInd.push_back(addLink(b, b));
    else
    {
        // If a is in the box interpolate to a
        if (inBox(a))
            newInd.push_back(addLink(b, a));

        // If c is in the box interpolate to c
        if (inBox(c))
            newInd.push_back(addLink(b, c));
    }
}

bool MeshTools::LinkSplitter::inBox(int index)
{
    S3DVertex& vert = getBaseVertex(oldMeshBuf, index);
    return box.isPointInside(vert.Pos);
}

int MeshTools::LinkSplitter::addLink(int index, int other)
{
    auto iter = oldLinksToNewIndices.find(make_pair(index, other));
    if (iter != oldLinksToNewIndices.end())
        return iter->second;
    else
        return oldLinksToNewIndices[make_pair(index, other)]
            = splitLink(index, other);
}

int MeshTools::LinkSplitter::splitLink(int index, int other)
{
    // The vertex outside the box - the one being generated new.
    S3DVertex& vOut = getBaseVertex(oldMeshBuf, index);

    // The vertex inside the box - not being changed.
    S3DVertex& vIn = getBaseVertex(oldMeshBuf, other);

    line3df originalLine(vOut.Pos, vIn.Pos);
    line3df lineAfterCut = cutLine(originalLine, box);

    float scale = lineAfterCut.getLength() / originalLine.getLength();

    S3DVertex vNew;

    vNew.TCoords = scaledAverage(scale, vOut.TCoords, vIn.TCoords);

    // I don't think this keeps the normal normalized nor is necessarily a good way to combine them.
    vNew.Normal = scaledAverage(scale, vOut.Normal, vIn.Normal);

    u32 a = scaledAverage(scale, vOut.Color.getAlpha(), vIn.Color.getAlpha());
    u32 r = scaledAverage(scale, vOut.Color.getRed(),   vIn.Color.getRed());
    u32 g = scaledAverage(scale, vOut.Color.getGreen(), vIn.Color.getGreen());
    u32 b = scaledAverage(scale, vOut.Color.getBlue(),  vIn.Color.getBlue());
    vNew.Color.set(a, r, g, b);

    newMeshBuf->Vertices.push_back(vNew);
    return newMeshBuf->Vertices.size();
}

// Given a line in which the endpoint is in the box and the start point is outside it,
// returns the point on the line where the box cuts it.
line3df MeshTools::cutLine(line3df line, aabbox3df box)
{
    /*
        If you think of the bounding box as the intersection of 6 axis-aligned planes that slice 3d space,
        it is quite simple to ask where does each plane cut the line on just one axis.
        However as the picture below shows, there might be a difference between where the plane cuts
        and the side of the bare box that would cut it.  To get the correct plane intersection,
        we choose the cut is farthest along the line.

              xmin  xmax
                |    |
        ymax    |    |
        --------+----+------
                |   o|
                |  / |
        --------+----+------
        ymin    |/   |
                |    |
               /|    |
              x |    |

    */

    vector3df xCut = cutLineX(line, box.MinEdge.X, box.MaxEdge.X);
    vector3df yCut = cutLineY(line, box.MinEdge.Y, box.MaxEdge.Y);
    vector3df zCut = cutLineZ(line, box.MinEdge.Z, box.MaxEdge.Z);

    vector3df bestCut = xCut;

    if (line(line.start, bestCut).getLengthSQ() < line(line.start, yCut).getLengthSQ())
        bestCut = yCut;

    if (line(line.start, bestCut).getLengthSQ() < line(line.start, zCut).getLengthSQ())
        bestCut = zCut;

    return line3df(bestCut, line.end);
}

vector3df MeshTools::cutLineX(line3df const& line, float xMin, float xMax)
{
    vector3df vect = line.getVector();

    if (vect.X > 0)
    {
        float yPerX = vect.Y / vect.X;
        float zPerX = vect.Z / vect.X;

        float xDist = 0;

        if (line.start.X < xMin)
            xDist = (xMin - line.start.X);
        else if (line.start.X > xMax)
            xDist = (line.start.X - xMax);
        else
            return line.start;

        float newY = vect.start.Y + xDist * yPerX;
        float newZ = vect.start.Z + yDist * yPerZ;

        return vector3df(x, newY, newZ);
    }
    else
        return line.start;
}

vector3df MeshTools::cutLineY(line3df const& line, float yMin, float yMax)
{
    return rotateVector(rotateVector(
        cutLineX(
            line3df(
                rotateVector(line.start),
                rotateVector(line.end)
            ),
            yMin, yMax
        )
    ));
}

vector3df MeshTools::cutLineZ(line3df const& line, float zMin, float zMax)
{
    return rotateVector(
        cutLineX(
            line3df(
                rotateVector(rotateVector(line.start)),
                rotateVector(rotateVector(line.end))
            ),
            zMin, zMax
        )
    );
}


IMesh* MeshTools::sliceMesh(IMesh* mesh, aabbox3df bounds)
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


