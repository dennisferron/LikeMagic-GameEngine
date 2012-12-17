// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/PossibleVertex.hpp"
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

void ::Bindings::Custom::intrusive_ptr_add_ref(PossibleVertex const* p)
{
    ++(p->ref_count);
}

void ::Bindings::Custom::intrusive_ptr_release(PossibleVertex const* p)
{
    if (!--(p->ref_count))
        delete p;
}

PossibleVertex::~PossibleVertex() {}

PossibleVertex::PossibleVertex(irr::video::S3DVertex const& vert_)
    : ref_count(0), vert(vert_)
{
}

PossibleVertex::PossibleVertex(irr::video::S3DVertex const& vLeft, irr::video::S3DVertex const& vRight, float scale)
    : ref_count(0)
{
    vert.TCoords = lerp(vLeft.TCoords, vRight.TCoords, scale);

    // This isn't really going to produce correct results unless
    // the normals are close to each other already (although, they should be).
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

PossibleVertex::PossibleVertex(PsblVertPtr const& pvLeft, PsblVertPtr const& pvRight, float scale)
    : ref_count(0)
{
    auto const& vLeft = pvLeft->vert;
    auto const& vRight = pvRight->vert;

    vert.TCoords = lerp(vLeft.TCoords, vRight.TCoords, scale);

    // This isn't really going to produce correct results unless
    // the normals are close to each other already (although, they should be).
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

PsblVertPtr PossibleVertex::duplicate(irr::core::vector3df offset)
{
    if (duplicates.find(offset) == duplicates.end())
    {
        PsblVertPtr p(new PossibleVertex(this->vert));
        p->vert.Pos += offset;
        duplicates[offset] = p;
    }

    return duplicates[offset];
}

int PossibleVertex::addToMeshBuf(SMeshBuffer* meshBuf, vector3df offset)
{
    int index;
    auto existing = assignedIndices.find(meshBuf);

    // Get existing vertex or add a new vertex.
    if (existing != assignedIndices.end())
        index = existing->second;
    else
    {
        S3DVertex offsetVert(vert);
        offsetVert.Pos += offset;
        meshBuf->Vertices.push_back(offsetVert);
        index = meshBuf->Vertices.size()-1;
        assignedIndices[meshBuf] = index;
    }

    meshBuf->Indices.push_back(index);

    return index;
}

float PossibleVertex::distSQ(PsblVertPtr other) const
{
    return vert.Pos.getDistanceFromSQ(other->vert.Pos);
}

float PossibleVertex::dist(PsblVertPtr other) const
{
    return vert.Pos.getDistanceFrom(other->vert.Pos);
}

vector3df const& PossibleVertex::getPos() const
{
    return vert.Pos;
}

void PossibleVertex::setPos(vector3df const& pos)
{
    vert.Pos = pos;
}

