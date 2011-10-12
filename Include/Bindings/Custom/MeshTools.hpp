// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"

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

    class LinkSplitter
    {
    private:
        irr::scene::IMeshBuffer* oldMeshBuf;
        irr::scene::SMeshBuffer* newMeshBuf;
        irr::core::aabbox3df box;
        std::map<std::pair<int, int>, int> oldLinksToNewIndices;  // Key is 2 old indices, Value is index in new meshbuf

        int addLink(int index, int other);
        int splitLink(int index, int other);
        bool inBox(int index);

    public:
        LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, irr::scene::SMeshBuffer* newMeshBuf_, irr::core::aabbox3df box_);
        void processCorner(std::vector<int>& newInd, int a, int b, int c);
        float distSQ(int a, int b) const;
    };

    static irr::scene::IMesh* createMeshFromSoftBody(btSoftBody* softBody);
    static btSoftBody* createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, irr::scene::IMesh* mesh);
    static irr::video::S3DVertex& getBaseVertex(irr::scene::IMeshBuffer* meshBuf, int n);
    static irr::scene::IMesh* sliceMesh(irr::scene::IMesh* mesh, irr::core::aabbox3df bounds);

    // Given a line in which the endpoint is in the box and the start point is outside it,
    // returns the point on the line where the box cuts it.
    static irr::core::vector3df cutLine(irr::core::line3df line, irr::core::aabbox3df box);

    // Allows you to define a function on X and then re-use it to do Y and Z.
    static inline irr::core::vector3df rotateVector(irr::core::vector3df const& vect)
    {
        return irr::core::vector3df(vect.Y, vect.Z, vect.X);
    }

    static bool compareMeshBuffers(irr::scene::IMeshBuffer* oldMesh, irr::scene::IMeshBuffer* newMesh);
};

}}
