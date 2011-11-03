// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"

#include "boost/intrusive_ptr.hpp"
#include <map>
#include <vector>
#include <set>

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
    class PossibleVertex;
    typedef boost::intrusive_ptr<PossibleVertex> PsblVertPtr;

    class PossibleVertex
    {
    private:
        friend void ::Bindings::Custom::intrusive_ptr_add_ref(PossibleVertex const* p);
        friend void ::Bindings::Custom::intrusive_ptr_release(PossibleVertex const* p);

        mutable std::size_t ref_count;

        irr::video::S3DVertex vert;
        std::map<irr::scene::SMeshBuffer*, int> assignedIndices;
        std::map<irr::core::vector3df, PsblVertPtr> duplicates;

        // Private constructor so only friend function intrusive_ptr_release can delete us.
        ~PossibleVertex();

        // This class contains a lot of members (ref_count, duplicates list, etc.)
        // that you actually wouldn't want copied.  I could define a copy constructor
        // that handles that, but I think it's better to force everyone to use the constructor
        // that takes an S3DVertex, to make it clear that that is the only part being copied.
        PossibleVertex(PossibleVertex const&) = delete;
        PossibleVertex& operator =(PossibleVertex const&) = delete;

    public:

        PossibleVertex(irr::video::S3DVertex const& vert_);

        // lerps the vertex between two others
        PossibleVertex(irr::video::S3DVertex const& vLeft, irr::video::S3DVertex const& vRight, float scale);

        // Adds the vertex at most once per meshbuffer.
        // Adds an index on each call; 3 calls to add a triangle.
        int addToMeshBuf(irr::scene::SMeshBuffer* meshBuf, irr::core::vector3df offset);

        float distSQ(PsblVertPtr other) const;

        // creates a duplicate of this vertex displaced in space by offset
        // the vertex tracks its duplicates and will always return the same copy
        // for the same offset.  This ensures vertex sharing in meshbuffer instead
        // of creating extra copies of the same vertex data in a buffer.
        PsblVertPtr duplicate(irr::core::vector3df offset);

        irr::core::vector3df const& getPos() const;
    };

    class LinkSplitter
    {
    private:
        irr::scene::IMeshBuffer* oldMeshBuf;
        float zCut;

        std::map<std::pair<int, int>, PsblVertPtr> splitLinksMidpoints;
        std::vector<PsblVertPtr> existingVertices;

        PsblVertPtr splitLink(int oldIndexLeft, int oldIndexRight);

    public:

        LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, float zCut_);
        void processLink(std::vector<PsblVertPtr>& left, std::vector<PsblVertPtr>& right, int a, int b);
        void addQuadOrTriangle(std::vector<PsblVertPtr> const& newShape, irr::scene::SMeshBuffer* newMeshBuf, irr::core::vector3df offset);
        void addEdgeLinks(std::vector<PsblVertPtr> const& shape, std::set<std::pair<PsblVertPtr,PsblVertPtr>>& links);
        PsblVertPtr getVert(int oldIndex);
        int compareZ(int oldIndex);
        int compareZ(PsblVertPtr vert);
    };

    static irr::scene::IMesh* createMeshFromSoftBody(btSoftBody* softBody);
    static btSoftBody* createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, irr::scene::IMesh* mesh);
    static irr::video::S3DVertex& getBaseVertex(irr::scene::IMeshBuffer* meshBuf, int n);

    struct SplitMeshResult
    {
        irr::scene::IMesh* left;
        irr::scene::IMesh* middle;
        irr::scene::IMesh* right;
    };

    static SplitMeshResult splitMeshZ(irr::scene::IMesh* oldMesh, float zCut, float zInsert, bool marginalTrisInLeft, bool marginalTrisInRight);

    static irr::core::vector3df cutLineZ(irr::core::line3df line, float zCut);
    // Given a line in which the endpoint is in the box and the start point is outside it,
    // returns the point on the line where the box cuts it.

    static bool compareMeshBuffers(irr::scene::IMeshBuffer* oldMesh, irr::scene::IMeshBuffer* newMesh);
    static bool checkMeshBuffer(irr::scene::IMeshBuffer* meshBuffer, irr::core::dimension2du tileSize);

    // Will create a mesh from a section of a heightmap.
    // Creates the mesh at in XY plane starting at 0,0 in world space, 1 pixel = 1 unit, and height along Z axis.
    // To move or scale the mesh differently, just follow up with irrlicht's irr::scene::IMeshManipulator class.
    // For edge tiles where the image size is not an exact match for the tile size, generates as much of the mesh on the last tile as it can.
    // Returns NULL if the requested tile is outside the image or if the image dimensions leave 0 or 1 rows or columns for the requested tile.
    static irr::scene::IMesh* createMeshFromHeightmap(irr::video::IImage* image, irr::core::dimension2du tileSizeInPixels, irr::core::vector2di tilePosInTiles, bool extraStripsOnEdges);
};

void intrusive_ptr_add_ref(MeshTools::PossibleVertex const* p);
void intrusive_ptr_release(MeshTools::PossibleVertex const* p);

}}
