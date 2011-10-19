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
using namespace boost;

using namespace Bindings::Custom;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;


MeshTools::PossibleVertex::PossibleVertex(irr::video::S3DVertex const& vert_)
    : vert(vert_)
{
}

MeshTools::PossibleVertex::PossibleVertex(irr::video::S3DVertex const& vLeft, irr::video::S3DVertex const& vRight, float scale)
{
    vert.TCoords = lerp(vLeft.TCoords, vRight.TCoords, scale);

    // This isn't really
    vert.Normal = lerp(vLeft.Normal, vRight.Normal, scale);
    vert.Normal.normalize();

    vert.Pos = lerp(vLeft.Pos, vRight.Pos, scale);

    // SColor doesn't define multiplication by a float, bummer.
    u32 a = lerp(vLeft.Color.getAlpha(), vRight.Color.getAlpha(), scale);
    u32 r = lerp(vLeft.Color.getRed(),   vRight.Color.getRed(), scale);
    u32 g = lerp(vLeft.Color.getGreen(), vRight.Color.getGreen(), scale);
    u32 b = lerp(vLeft.Color.getBlue(),  vRight.Color.getBlue(), scale);
    vert.Color.set(a, r, g, b);
}

int MeshTools::PossibleVertex::addToMeshBuf(irr::scene::SMeshBuffer* meshBuf)
{
    int index;
    auto existing = assignedIndices.find(meshBuf);

    // Get existing vertex or add a new vertex.
    if (existing != assignedIndices.end())
        index = existing->second;
    else
    {
        meshBuf->Vertices.push_back(vert);
        index = meshBuf->Vertices.size()-1;
        assignedIndices[meshBuf] = index;
    }

    meshBuf->Indices.push_back(index);

    return index;
}

float MeshTools::PossibleVertex::distSQ(PossibleVertex* other) const
{
    return vert.Pos.getDistanceFromSQ(other->vert.Pos);
}

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

MeshTools::LinkSplitter::LinkSplitter(IMeshBuffer* oldMeshBuf_, float zCut_)
    : oldMeshBuf(oldMeshBuf_), zCut(zCut_), existingVertices(oldMeshBuf_->getVertexCount())
{
    // All of the old mesh buffers vertex will go in at least one of the result meshes.
    for (u32 i=0; i<oldMeshBuf->getVertexCount(); ++i)
        existingVertices[i] = boost::shared_ptr<PossibleVertex>(new PossibleVertex(getBaseVertex(oldMeshBuf, i)));
}

// Adds point a, point b, and/or the midpoint between a and b
void MeshTools::LinkSplitter::processLink(std::vector<PossibleVertex*>& leftInd, std::vector<PossibleVertex*>& rightInd, int a, int b)
{
    int whichSideA = compareZ(a);
    int whichSideB = compareZ(b);

    // Add a to left side if it is left or in both
    if (whichSideA < 0 || whichSideA == 0)
        leftInd.push_back(getVert(a));

    // Add a to right side if it is right or in both
    if (whichSideA > 0 || whichSideA == 0)
        rightInd.push_back(getVert(a));

    // Link crosses like this:  a --|--> b
    if (whichSideA < 0 && whichSideB > 0)
    {
        auto mid = splitLink(a, b);
        leftInd.push_back(mid);
        rightInd.push_back(mid);
    }
    // Link crosses like this: b --|--> a
    else if (whichSideB < 0 && whichSideA > 0)
    {
        auto mid = splitLink(b, a);
        leftInd.push_back(mid);
        rightInd.push_back(mid);
    }

    // Add b to left side if it is left or in both
    if (whichSideB < 0 || whichSideB == 0)
        leftInd.push_back(getVert(b));

    // Add b to right side if it is right or in both
    if (whichSideB > 0 || whichSideB == 0)
        rightInd.push_back(getVert(b));
}

int MeshTools::LinkSplitter::compareZ(int index)
{
    S3DVertex& vert = getBaseVertex(oldMeshBuf, index);
    float z = vert.Pos.Z;
    if (irr::core::equals(z, zCut))
        return 0;
    else if (z < zCut)
        return -1;
    else
        return 1;
}


MeshTools::PossibleVertex* MeshTools::LinkSplitter::getVert(int oldIndex)
{
    return existingVertices[oldIndex].get();
}

MeshTools::PossibleVertex* MeshTools::LinkSplitter::splitLink(int oldIndexLeft, int oldIndexRight)
{
    auto iter = splitLinksMidpoints.find(make_pair(oldIndexLeft, oldIndexRight));
    if (iter != splitLinksMidpoints.end())
        return iter->second.get();
    else
    {
        S3DVertex& vLeft = getBaseVertex(oldMeshBuf, oldIndexLeft);
        S3DVertex& vRight = getBaseVertex(oldMeshBuf, oldIndexRight);

        float scale = (zCut - vLeft.Pos.Z) / (vRight.Pos.Z - vLeft.Pos.Z);

        // Test if scale is going all screwy due to a bad division result.
        if (! (scale >= 0-ROUNDING_ERROR_f32 && scale <= 1.0f+ROUNDING_ERROR_f32) )
        {
            throw std::runtime_error("Hit a bad division result while slicing a mesh.");
        }

        std::map<std::pair<int, int>, boost::shared_ptr<PossibleVertex>>::mapped_type result = boost::shared_ptr<PossibleVertex>(new PossibleVertex(vLeft, vRight, scale));
        splitLinksMidpoints.insert(make_pair(make_pair(oldIndexLeft, oldIndexRight), result));
        return result.get();
    }
}

void MeshTools::LinkSplitter::addQuadOrTriangle(vector<PossibleVertex*> const& newShape, irr::scene::SMeshBuffer* newMeshBuf)
{
    switch (newShape.size())
    {
        case 0:
            // Nothing touches
            break; // no triangle
        case 1:
            // Only a corner touches
            break; // incomplete triangle
        case 2:
            // Only a side touches
            break; // incomplete triangle
        case 3:  // add 1 triangle
            for (int j=0; j<3; ++j)
                newShape[j]->addToMeshBuf(newMeshBuf);
            break;
        case 4:  // add quad, need to make two triangles
        {
            // If you don't have the braces around the variable declarations here, gcc gives the cryptic error "jump to case label".
            // The GCC maintainers closed someone's bug report about this problem saying that's expected behavior, you should just know
            // that the problem is the variables escape scope to the next label (even though I'm not actually using any of them there).
            // Really GCC guys?  Really?  "jump to case label" - you think that's an acceptable error message?  F*** you.
            PossibleVertex *A=newShape[0], *B=newShape[1], *C=newShape[2], *D=newShape[3];
            PossibleVertex* acTris[] = { A,B,C , A,C,D };
            PossibleVertex* bdTris[] = { B,C,D , B,D,A };
            PossibleVertex** twoTris = A->distSQ(C) < B->distSQ(D) ? acTris : bdTris;
            for (int j=0; j<6; ++j)
                newShape[j]->addToMeshBuf(newMeshBuf);
            break;
        }
        default:
            throw std::logic_error("Something went wrong in splitMeshZ; LinkSplitter::addQuadOrTriangle was passed more than 4 points.");
    }
}

std::pair<irr::scene::IMesh*, irr::scene::IMesh*> MeshTools::splitMeshZ(IMesh* oldMesh, float zCut)
{
    IMeshBuffer* oldMeshBuf = oldMesh->getMeshBuffer(0);
    u16* oldInd = oldMeshBuf->getIndices();
	SMeshBuffer* leftMeshBuf = new SMeshBuffer();
	SMeshBuffer* rightMeshBuf = new SMeshBuffer();
    LinkSplitter linkSplitter(oldMeshBuf, zCut);

    for (u32 i=0; i < oldMeshBuf->getIndexCount(); i += 3)
    {
        // Calling these shapes instead of triangles because they could be triangle or a quad after slice,
        // (it could also be a degenerate case of a line or a point - those will be discarded by addQuadOrTriangle)
        vector<PossibleVertex*> leftShape;
        vector<PossibleVertex*> rightShape;

        for (u32 j=0; j<3; ++j)
        {
            linkSplitter.processLink(
                leftShape, rightShape,
                oldInd[i+(j+0)%3],
                oldInd[i+(j+1)%3]);
        }

        linkSplitter.addQuadOrTriangle(leftShape, leftMeshBuf);
        linkSplitter.addQuadOrTriangle(rightShape, rightMeshBuf);
    }

	SMesh* leftMesh = new SMesh();
	leftMeshBuf->recalculateBoundingBox();
	leftMeshBuf->setHardwareMappingHint(EHM_STATIC);
    leftMesh->addMeshBuffer(leftMeshBuf);
	leftMesh->recalculateBoundingBox();
	leftMeshBuf->drop();  // we drop the buf, mesh obj has it now

	SMesh* rightMesh = new SMesh();
	rightMeshBuf->recalculateBoundingBox();
	rightMeshBuf->setHardwareMappingHint(EHM_STATIC);
    rightMesh->addMeshBuffer(rightMeshBuf);
	rightMesh->recalculateBoundingBox();
	rightMeshBuf->drop();  // we drop the buf, mesh obj has it now

	return make_pair(leftMesh, rightMesh);
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
    for (u32 i=0; i < newToNew.size(); ++i)
        newToNew[i] = i;

    vector<int> oldToOld(oldMesh->getVertexCount());
    for (u32 i=0; i < oldToOld.size(); ++i)
        oldToOld[i] = i;

    for (u32 o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        auto const& newVertex = MeshTools::getBaseVertex(newMesh, o);
        for (u32 n=0; n < newMesh->getVertexCount(); ++n)
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
    for (u32 o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        for (u32 n=0; n < newMesh->getVertexCount(); ++n)
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

    for (u32 o=0; o<oldMesh->getVertexCount(); ++o)
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
