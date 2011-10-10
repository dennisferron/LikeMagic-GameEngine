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
#include <cassert>
#include <tuple>
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
	for (unsigned int i=0; i < buffer->getVertexCount(); ++i)
	{
	    vector3df p = getBaseVertex(buffer, i).Pos;
	    vertices.push_back(p.X);
	    vertices.push_back(p.Y);
	    vertices.push_back(p.Z);
	}

    vector<int> triangles;
    for (unsigned int i=0; i < buffer->getIndexCount(); ++i)
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

MeshTools::LinkSplitter::LinkSplitter(IMeshBuffer* oldMeshBuf_, SMeshBuffer* newMeshBuf_, aabbox3df box_)
    : oldMeshBuf(oldMeshBuf_), newMeshBuf(newMeshBuf_), box(box_)
{

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
    // A link from itself to itself means don't split it.
    if (index == other)
    {
        newMeshBuf->Vertices.push_back(getBaseVertex(oldMeshBuf, index));
        return newMeshBuf->Vertices.size()-1;
    }

    // The vertex outside the box - the one being generated new.
    S3DVertex& vOut = getBaseVertex(oldMeshBuf, index);

    // The vertex inside the box - not being changed.
    S3DVertex& vIn = getBaseVertex(oldMeshBuf, other);

    line3df originalLine(vOut.Pos, vIn.Pos);
    line3df lineAfterCut = cutLine(originalLine, box);

    float originalLen = originalLine.getLength();
    float afterCutLen = lineAfterCut.getLength();
    float scale = afterCutLen / originalLen;

    S3DVertex vNew;

    // TODO: Scale texture coords
    vNew.TCoords = vOut.TCoords;
    //vNew.TCoords = scaledAverage(scale, vOut.TCoords, vIn.TCoords);

    // I want to create a sharp dividing line between meshes, so using the normal of the
    // internal vertex so that the lighting won't smooth over the crease.
    // TODO: Might want to make this a parameter, maybe a functor to calculate the normal.
    vNew.Normal = vIn.Normal;

    // TODO:  scale
    vNew.Pos = scaledAverage(scale, vOut.Pos, vIn.Pos);
    //vNew.Pos = 0.5f * (vOut.Pos + vIn.Pos);

    u32 a = scaledAverage(scale, vOut.Color.getAlpha(), vIn.Color.getAlpha());
    u32 r = scaledAverage(scale, vOut.Color.getRed(),   vIn.Color.getRed());
    u32 g = scaledAverage(scale, vOut.Color.getGreen(), vIn.Color.getGreen());
    u32 b = scaledAverage(scale, vOut.Color.getBlue(),  vIn.Color.getBlue());
    vNew.Color.set(a, r, g, b);

    newMeshBuf->Vertices.push_back(vNew);
    return newMeshBuf->Vertices.size()-1;
}

// Note: the ints are new meshbuf indicies
float MeshTools::LinkSplitter::distSQ(int a, int b) const
{
    S3DVertex& va = getBaseVertex(newMeshBuf, a);
    S3DVertex& vb = getBaseVertex(newMeshBuf, b);
    return line3df(va.Pos, vb.Pos).getLengthSQ();
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

    if (line3df(line.start, bestCut).getLengthSQ() < line3df(line.start, yCut).getLengthSQ())
        bestCut = yCut;

    if (line3df(line.start, bestCut).getLengthSQ() < line3df(line.start, zCut).getLengthSQ())
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

        float newX = line.start.X + xDist;
        float newY = line.start.Y + vect.X * yPerX;
        float newZ = line.start.Z + vect.X * zPerX;

        return vector3df(newX, newY, newZ);
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

bool MeshTools::compareMeshBuffers(IMeshBuffer* oldMesh, IMeshBuffer* newMesh)
{
    if (oldMesh->getVertexCount() != newMesh->getVertexCount())
    {
        cout << "unequal vertex counts" << std::endl;
        return false;
    }

    if (oldMesh->getIndexCount() != newMesh->getIndexCount())
    {
        cout << "unequal index counts" << endl;
        return false;
    }

    cout << "Checking for duplicate vertexes in " << oldMesh->getVertexCount() << " vertices." << endl;

    // To handle duplicates we'll map instances of duplicates onto their first occurrence

    vector<int> newToNew(newMesh->getVertexCount());
    for (int i=0; i < newToNew.size(); ++i)
        newToNew[i] = i;

    vector<int> oldToOld(oldMesh->getVertexCount());
    for (int i=0; i < oldToOld.size(); ++i)
        oldToOld[i] = i;

    for (int o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        auto const& newVertex = MeshTools::getBaseVertex(newMesh, o);
        for (int n=0; n < newMesh->getVertexCount(); ++n)
        {
            if (o==n)
                continue;

            auto const& otherOldVertex = MeshTools::getBaseVertex(oldMesh, n);
            auto const& otherNewVertex = MeshTools::getBaseVertex(newMesh, n);
            if (oldVertex.Pos == otherOldVertex.Pos && oldVertex.TCoords == otherOldVertex.TCoords)
            {
                oldToOld[n] = o;
            }
            if (newVertex.Pos == otherNewVertex.Pos && newVertex.TCoords == otherNewVertex.TCoords)
            {
                newToNew[n] = o;
            }
        }
    }

    // The reason this loop can handle duplicates is because there is no downside to mapping multiple
    // old vertices onto the same new vertex.  Since we find the first match and exit the loop early
    // with the break, we always get the first n of a duplicate never the others.

    vector<int> oldToNew(oldMesh->getVertexCount(), -1);

    cout << "Building vertex equivalence table for " << oldToNew.size() << " vertices." << endl;
    for (int o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        for (int n=0; n < newMesh->getVertexCount(); ++n)
        {
            auto const& newVertex = MeshTools::getBaseVertex(newMesh, n);
            if (oldVertex.Pos == newVertex.Pos && oldVertex.TCoords == newVertex.TCoords)
            {
                oldToNew[o] = n;
                break;
            }
        }
    }

    cout << "Checking vertex equivalence table" << endl;

    for (int o=0; o<oldMesh->getVertexCount(); ++o)
    {
        if (oldToNew[o] == -1)
        {
            cout << "old vertex " << o << " has no equivalent in new mesh." << endl;
            return false;
        }
    }

    cout << "Building triangle lists" << endl;

    auto mktuple = [](int a, int b, int c) { if (c<b) std::swap(c,b); if (b<a) std::swap(b,a); if (b>c) std::swap(b,c); return make_tuple(a, b, c); };
    int triangleCount = oldMesh->getIndexCount() / 3;
    vector<tuple<int, int, int>> oldToNewTris(triangleCount);
    vector<tuple<int, int, int>> newToNewTris(triangleCount);

    u16 const* oldInd = oldMesh->getIndices();
    for (int o=0; o < triangleCount; ++o)
        oldToNewTris[o] = mktuple(oldToNew[oldToOld[oldInd[3*o]]], oldToNew[oldToOld[oldInd[3*o+1]]], oldToNew[oldToOld[oldInd[3*o+2]]] );

    u16 const* newInd = newMesh->getIndices();
    for (int n=0; n < triangleCount; ++n)
        newToNewTris[n] = mktuple(newToNew[newInd[3*n]], newToNew[newInd[3*n+1]], newToNew[newInd[3*n+2]] );

    cout << "Sorting triangle lists" << endl;

    sort(oldToNewTris.begin(), oldToNewTris.end());
    sort(newToNewTris.begin(), newToNewTris.end());

    cout << "Comparing triangle lists" << endl;

    for (int i=0; i<triangleCount; ++i)
    {
        if (oldToNewTris[i] != newToNewTris[i])
        {
            cout << "unequal triangles:" << endl;
            auto oldT = oldToNewTris[i];
            cout << "old: " << get<0>(oldT) << "," << get<1>(oldT) << "," << get<2>(oldT) << endl;
            auto newT = newToNewTris[i];
            cout << "new: " << get<0>(newT) << "," << get<1>(newT) << "," << get<2>(newT) << endl;
            return false;
        }
    }

    return true;
}

IMesh* MeshTools::sliceMesh(IMesh* oldMesh, aabbox3df bounds)
{
    IMeshBuffer* oldMeshBuf = oldMesh->getMeshBuffer(0);
    u16* oldInd = oldMeshBuf->getIndices();
	SMeshBuffer* newMeshBuf = new SMeshBuffer();
    LinkSplitter linkSplitter(oldMeshBuf, newMeshBuf, bounds);

    for (u32 i=0; i < oldMeshBuf->getIndexCount(); i += 3)
    {
        vector<int> newInd;

        for (u32 j=0; j<3; ++j)
        {
            linkSplitter.processCorner(
                newInd,
                oldInd[i+(j+2)%3],
                oldInd[i+(j+0)%3],
                oldInd[i+(j+1)%3]);
        }

        switch (newInd.size())
        {
            case 3:  // link split left triangle
                for (int j=0; j<3; ++j)
                    newMeshBuf->Indices.push_back(newInd[j]);
                break;
            case 4:  // link split left quad, make two triangles
                int A=newInd[0], B=newInd[1], C=newInd[2], D=newInd[3];
                int const acTris[] = { A,B,C , A,C,D };
                int const bdTris[] = { B,C,D , B,D,A };
                int const* twoTris = linkSplitter.distSQ(A,C) < linkSplitter.distSQ(B,D) ? acTris : bdTris;
                for (int j=0; j<6; ++j)
                    newMeshBuf->Indices.push_back(twoTris[j]);
        }
    }

    //compareMeshBuffers(oldMeshBuf, newMeshBuf);

	SMesh* mesh = new SMesh();
	newMeshBuf->recalculateBoundingBox();
	newMeshBuf->setHardwareMappingHint(EHM_STATIC);
    mesh->addMeshBuffer(newMeshBuf);
	mesh->recalculateBoundingBox();
	newMeshBuf->drop();
	return mesh;
}

