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
#include "Bindings/Custom/SurfaceQuadTree.hpp"
#include "boost/intrusive_ptr.hpp"

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

using namespace TPS;

MeshTools::SplitMeshResult MeshTools::createHillMesh(SurfaceQuadTree& tree, rectf section)
{
    std::vector<PsblVertPtr> triangles;
    tree.triangulate(triangles, section);

	SMeshBuffer* buffer = new SMeshBuffer();

    irr::video::S3DVertex vtx;
    PsblVertPtr vert;

    vtx.Pos.X = 0.0f;
    vtx.Pos.Y = 0.0f;
    vert = new PossibleVertex(vtx);
    vert->addToMeshBuf(buffer, vector3df());

    vtx.Pos.X = 1.0f;
    vtx.Pos.Y = 0.0f;
    vert = new PossibleVertex(vtx);
    vert->addToMeshBuf(buffer, vector3df());

    vtx.Pos.X = 1.0f;
    vtx.Pos.Y = 1.0f;
    vert = new PossibleVertex(vtx);
    vert->addToMeshBuf(buffer, vector3df());

    for (auto pv : triangles)
        pv->addToMeshBuf(buffer, vector3df());

	buffer->recalculateBoundingBox();
	buffer->setHardwareMappingHint(EHM_STATIC);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();

	SplitMeshResult result;
	result.middle = mesh;
	return result;
}
