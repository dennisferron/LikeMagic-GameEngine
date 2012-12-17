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

namespace Bindings { namespace Custom {

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
    PossibleVertex(PsblVertPtr const& pvLeft, PsblVertPtr const& pvRight, float scale);

    // Adds the vertex at most once per meshbuffer.
    // Adds an index on each call; 3 calls to add a triangle.
    int addToMeshBuf(irr::scene::SMeshBuffer* meshBuf, irr::core::vector3df offset);

    float distSQ(PsblVertPtr other) const;
    float dist(PsblVertPtr other) const;

    // creates a duplicate of this vertex displaced in space by offset
    // the vertex tracks its duplicates and will always return the same copy
    // for the same offset.  This ensures vertex sharing in meshbuffer instead
    // of creating extra copies of the same vertex data in a buffer.
    PsblVertPtr duplicate(irr::core::vector3df offset);

    irr::core::vector3df const& getPos() const;
    void setPos(irr::core::vector3df const& pos);
};

void intrusive_ptr_add_ref(PossibleVertex const* p);
void intrusive_ptr_release(PossibleVertex const* p);

}}
