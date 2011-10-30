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
private:
    // Implementation detail of createMeshFromHeightmap
    // Error: 'u32 in irr::core does not name a type' WTF?  I have include irrlicht.h in this same header.
    static unsigned int getIndex(irr::core::dimension2du tileSize, unsigned int x, unsigned int y);

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

        float distSQ(boost::shared_ptr<PossibleVertex> other) const;
    };

    class LinkSplitter
    {
    private:
        irr::scene::IMeshBuffer* oldMeshBuf;
        float zCut;

        std::map<std::pair<int, int>, boost::shared_ptr<PossibleVertex>> splitLinksMidpoints;
        std::vector<boost::shared_ptr<PossibleVertex>> existingVertices;

        boost::shared_ptr<PossibleVertex> getVert(int oldIndex);
        boost::shared_ptr<PossibleVertex> splitLink(int oldIndexLeft, int oldIndexRight);
        int compareZ(int oldIndex);
    public:
        LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, float zCut_);
        void processLink(std::vector<boost::shared_ptr<PossibleVertex>>& left, std::vector<boost::shared_ptr<PossibleVertex>>& right, int a, int b);
        void addQuadOrTriangle(std::vector<boost::shared_ptr<PossibleVertex>> const& newShape, irr::scene::SMeshBuffer* newMeshBuf);
    };

    static irr::scene::IMesh* createMeshFromSoftBody(btSoftBody* softBody);
    static btSoftBody* createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, irr::scene::IMesh* mesh);
    static irr::video::S3DVertex& getBaseVertex(irr::scene::IMeshBuffer* meshBuf, int n);
    static std::pair<irr::scene::IMesh*, irr::scene::IMesh*> splitMeshZ(irr::scene::IMesh* mesh, float zCut);

    static irr::core::vector3df cutLineZ(irr::core::line3df line, float zCut);
    // Given a line in which the endpoint is in the box and the start point is outside it,
    // returns the point on the line where the box cuts it.

    static bool compareMeshBuffers(irr::scene::IMeshBuffer* oldMesh, irr::scene::IMeshBuffer* newMesh);

    // Will create a mesh from a section of a heightmap.
    // Creates the mesh at in XY plane starting at 0,0 in world space, 1 pixel = 1 unit, and height along Z axis.
    // To move or scale the mesh differently, just follow up with irrlicht's irr::scene::IMeshManipulator class.
    // For edge tiles where the image size is not an exact match for the tile size, generates as much of the mesh on the last tile as it can.
    // Returns NULL if the requested tile is outside the image or if the image dimensions leave 0 or 1 rows or columns for the requested tile.
    static irr::scene::IMesh* createMeshFromHeightmap(irr::video::IImage* image, irr::core::dimension2du tileSizeInPixels, irr::core::vector2di tilePosInTiles, bool extraStripsOnEdges);
};

}}
