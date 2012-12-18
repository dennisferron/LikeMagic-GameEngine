// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/intrusive_ptr.hpp"
#include "irrlicht.h"
#include "ThinPlateSpline/ThinPlateQuilt.hpp"
#include "PossibleVertex.hpp"
#include <vector>

namespace Bindings { namespace Custom {

class SurfaceQuadTree;
typedef boost::intrusive_ptr<SurfaceQuadTree> QuadTreePtr;

class SurfaceQuadTree
{
public:

    struct Shell
    {
        std::vector<QuadTreePtr> north;
        std::vector<QuadTreePtr> south;
        std::vector<QuadTreePtr> east;
        std::vector<QuadTreePtr> west;
    };

private:

    friend void intrusive_ptr_add_ref(SurfaceQuadTree const* p);
    friend void intrusive_ptr_release(SurfaceQuadTree const* p);

    mutable std::size_t ref_count;

    QuadTreePtr child[4];
    irr::core::rectf region;
    TPS::ThinPlateQuilt& surface;
    PsblVertPtr vert;

    irr::core::vector2df locate(double expected_height);
    bool isLeaf() const;
    bool isOuter(irr::core::rectf other_region) const;

    std::vector<QuadTreePtr> combine(std::vector<QuadTreePtr> const& first, std::vector<QuadTreePtr> const& second);
    void addTriangle(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c) const;
    void addQuad(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, QuadTreePtr const& d) const;
    bool isAdjacent(QuadTreePtr const& that) const;
    void zip(std::vector<PsblVertPtr>& triangles, std::vector<QuadTreePtr> const& list_a, std::vector<QuadTreePtr> const& list_b);

public:

    SurfaceQuadTree(irr::core::rectf region_, TPS::ThinPlateQuilt& surface_);

    Shell triangulate(std::vector<PsblVertPtr>& triangles, irr::core::rectf const& section);
    void split(int times);
    void testVertices(irr::core::rectf& rect);
};

void intrusive_ptr_add_ref(SurfaceQuadTree const* p);
void intrusive_ptr_release(SurfaceQuadTree const* p);

}}
