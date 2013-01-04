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

    struct Visitor
    {
        virtual void check(QuadTreePtr a1, QuadTreePtr a2, QuadTreePtr b1, QuadTreePtr b2)=0;
        virtual void addTriangle(QuadTreePtr a, QuadTreePtr b, QuadTreePtr c)=0;
    };

public:

    friend void intrusive_ptr_add_ref(SurfaceQuadTree const* p);
    friend void intrusive_ptr_release(SurfaceQuadTree const* p);

    mutable std::size_t ref_count;

    QuadTreePtr child[4];
    irr::core::rectf region;
    TPS::ThinPlateQuilt& surface;
    std::string path;
    PsblVertPtr vert;

    irr::core::vector2df locate(double expected_height);
    bool isLeaf() const;
    bool isOuter(irr::core::rectf other_region) const;
    bool isBetween(double min_height, double max_height) const;
    bool isBetween(QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, double min_height, double max_height) const;

    std::vector<QuadTreePtr> combine(std::vector<QuadTreePtr> const& first, std::vector<QuadTreePtr> const& second);
    void addTriangle(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, double min_height, double max_height, Visitor* visitor) const;
    void addQuad(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, QuadTreePtr const& d, double min_height, double max_height, Visitor* visitor) const;
    void zip(std::vector<PsblVertPtr>& triangles, std::vector<QuadTreePtr> const& list_a, std::vector<QuadTreePtr> const& list_b, double min_height, double max_height, Visitor* visitor);

    bool isBetween(double lesser, double middle, double greater);
    int boundaryCrossings(std::vector<double> boundaries);
    double closestHeight(double h, std::vector<double> boundaries);

public:

    SurfaceQuadTree(irr::core::rectf region_, TPS::ThinPlateQuilt& surface_, std::string path_);

    Shell triangulate(std::vector<PsblVertPtr>& triangles, irr::core::rectf const& section, double min_height, double max_height, Visitor* visitor=NULL);
    void sweep(std::vector<PsblVertPtr>& triangles, irr::core::rectf const& section, Visitor* visitor=NULL);
    void split(int times);
    void fit(irr::core::dimension2df min_size, std::vector<double> boundaries);
    void testVertices(irr::core::rectf& rect);
    bool isAdjacent(QuadTreePtr const& that) const;

    void dumpLeaves(std::vector<QuadTreePtr>& result, irr::core::rectf const& section=irr::core::rectf(-1000000.0f, -10000000.0f, 1000000.0f, 1000000.0f));
    std::string getPath() const;
};

void intrusive_ptr_add_ref(SurfaceQuadTree const* p);
void intrusive_ptr_release(SurfaceQuadTree const* p);

}}
