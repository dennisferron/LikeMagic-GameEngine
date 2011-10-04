// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"

#include "boost/units/quantity.h"

class btSoftBody;

namespace Bindings { namespace Custom {

class MeshTools
{
public:

    class LinkSplitter
    {
    private:
        IMeshBuffer* oldMeshBuf;
        IMeshBuffer* newMeshBuf;
        map<pair<int, int>, int> oldLinksToNewIndices;  // Key is 2 old indices, Value is index in new meshbuf

    public:
        vector<int> splitB(int a, int b, int c);
    };

    static irr::scene::IMesh* createMeshFromSoftBody(btSoftBody* softBody);
    static btSoftBody* createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, irr::scene::IMesh* mesh);
    static irr::video::S3DVertex& getBaseVertex(irr::scene::IMeshBuffer* meshBuf, int n);
    static IMesh* sliceMesh(IMesh* mesh, irr::core::aabbox3df bounds);
};

}}
