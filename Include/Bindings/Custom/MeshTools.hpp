// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"
#include "Bindings/Custom/SurfaceQuadTree.hpp"
#include "Bindings/Custom/LinkSplitter.hpp"

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

    static irr::scene::IMesh* createHillMesh(SurfaceQuadTree& tree, irr::core::rectf region, double min_height, double max_height);
};

}}
