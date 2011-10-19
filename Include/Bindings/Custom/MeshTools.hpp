// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"

#include "boost/shared_ptr.hpp"
#include <map>
#include <vector>

class btSoftBody;
class btSoftBodyWorldInfo;

namespace irr { namespace video {
    class SColor;
}}

namespace Bindings { namespace Custom {

class MeshTools
{
public:
    class PossibleVertex
    {
    private:
        irr::video::S3DVertex vert;
        std::map<irr::scene::SMeshBuffer*, int> assignedIndices;

    public:
        PossibleVertex(irr::video::S3DVertex const& vert_);

        // lerps the vertex between two others
        PossibleVertex(irr::video::S3DVertex const& vLeft, irr::video::S3DVertex const& vRight, float scale);

        // Adds the vertex at most once per meshbuffer.
        // Adds an index on each call; 3 calls to add a triangle.
        int addToMeshBuf(irr::scene::SMeshBuffer* meshBuf);

        float distSQ(PossibleVertex* other) const;
    };

    class LinkSplitter
    {
    private:
        irr::scene::IMeshBuffer* oldMeshBuf;
        float zCut;

        std::map<std::pair<int, int>, boost::shared_ptr<PossibleVertex>> splitLinksMidpoints;
        std::vector<boost::shared_ptr<PossibleVertex>> existingVertices;

        PossibleVertex* getVert(int oldIndex);
        PossibleVertex* splitLink(int oldIndexLeft, int oldIndexRight);
        int compareZ(int oldIndex);
    public:
        LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, float zCut_);
        void processLink(std::vector<PossibleVertex*>& left, std::vector<PossibleVertex*>& right, int a, int b);
        void addQuadOrTriangle(std::vector<PossibleVertex*> const& newShape, irr::scene::SMeshBuffer* newMeshBuf);
    };

    static irr::scene::IMesh* createMeshFromSoftBody(btSoftBody* softBody);
    static btSoftBody* createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, irr::scene::IMesh* mesh);
    static irr::video::S3DVertex& getBaseVertex(irr::scene::IMeshBuffer* meshBuf, int n);
    static std::pair<irr::scene::IMesh*, irr::scene::IMesh*> splitMeshZ(irr::scene::IMesh* mesh, float zCut);

    static irr::core::vector3df cutLineZ(irr::core::line3df line, float zCut);
    // Given a line in which the endpoint is in the box and the start point is outside it,
    // returns the point on the line where the box cuts it.

    static bool compareMeshBuffers(irr::scene::IMeshBuffer* oldMesh, irr::scene::IMeshBuffer* newMesh);
};

}}
