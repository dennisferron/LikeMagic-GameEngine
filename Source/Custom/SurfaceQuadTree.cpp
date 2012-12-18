// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Custom/SurfaceQuadTree.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
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

// Locate the best position within the cell for a vertex based on
// a weighted average the corner positions by their difference from expected height.
vector2df SurfaceQuadTree::locate(double expected_height)
{
    float total_weight = 0.0;
    vector2df total_pos;

    for (int i=0; i<4; ++i)
    {
        vector2df corner_pos(
            region.getSize().Width * (i&1) + region.UpperLeftCorner.X,
            region.getSize().Height * ((i>>1)&1) + region.UpperLeftCorner.Y
        );

        double height = surface.heightAt(corner_pos.X, corner_pos.Y);
        float inverse_weight = abs(height - expected_height);
        float adjusted_weight = 1.0f / (inverse_weight + 0.001f);

        total_pos += adjusted_weight * corner_pos;
        total_weight += adjusted_weight;
    }

    return total_pos / total_weight;
}

bool SurfaceQuadTree::isLeaf() const
{
    return child[0] == NULL;
}

bool SurfaceQuadTree::isOuter(rectf other_region) const
{
    vector2df displacement = other_region.getCenter() - region.getCenter();
    vector2df twice_displaced = other_region.getCenter() + displacement;
    return !region.isPointInside(twice_displaced);
}

std::vector<QuadTreePtr> SurfaceQuadTree::combine(std::vector<QuadTreePtr> const& first, std::vector<QuadTreePtr> const& second)
{
    std::vector<QuadTreePtr> result;
    result.insert(result.end(), first.begin(), first.end());
    result.insert(result.end(), second.begin(), second.end());
    return result;
}

void SurfaceQuadTree::addTriangle(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c) const
{
    triangles.push_back(a->vert);
    triangles.push_back(b->vert);
    triangles.push_back(c->vert);

    triangles.push_back(c->vert);
    triangles.push_back(b->vert);
    triangles.push_back(a->vert);
}

void SurfaceQuadTree::addQuad(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, QuadTreePtr const& d) const
{
    if (a->vert->distSQ(c->vert) < b->vert->distSQ(d->vert))
    {
        addTriangle(triangles, a, b, c);
        addTriangle(triangles, a, c, d);
    }
    else
    {
        addTriangle(triangles, b, c, d);
        addTriangle(triangles, b, d, a);
    }
}

bool SurfaceQuadTree::isAdjacent(QuadTreePtr const& that) const
{
    float tolerance = 0.001;
    vector2df displacement = this->region.UpperLeftCorner - that->region.UpperLeftCorner;
    float dist_x = abs(displacement.X);
    float dist_y = abs(displacement.Y);
    dimension2df extent = this->region.getSize() / 2.0f + that->region.getSize() / 2.0f;
    bool adj_x = dist_x <= extent.Width + tolerance;
    bool adj_y = dist_y <= extent.Height + tolerance;
    return adj_x && adj_y;
}

void SurfaceQuadTree::zip(std::vector<PsblVertPtr>& triangles, std::vector<QuadTreePtr> const& list_a, std::vector<QuadTreePtr> const& list_b)
{
    if (list_a.size() == 0 || list_b.size() == 0 || (list_a.size()+list_b.size()) < 3)
        return;

    auto a1 = list_a.begin();
    auto b1 = list_b.begin();

    bool end_a;
    bool end_b;
    do
    {
        auto a2 = a1+1;
        auto b2 = b1+1;

        end_a = (a2==list_a.end());
        end_b = (b2==list_b.end());

        bool adj_a = !end_a && (*a2)->isAdjacent(*b1);
        bool adj_b = !end_b && (*b2)->isAdjacent(*a1);

        if (adj_a && !adj_b)
            addTriangle(triangles, *a1, *a2, *b1);
        else if (!adj_a && adj_b)
            addTriangle(triangles, *a1, *b2, *b1);
        else if (adj_a && adj_b)
            addQuad(triangles, *a1, *a2, *b2, *b1);

        a1 = end_a? a1 : a2;
        b1 = end_b? b1 : b2;
    } while (!(end_a && end_b));
}

SurfaceQuadTree::Shell SurfaceQuadTree::triangulate(std::vector<PsblVertPtr>& triangles, rectf const& section)
{
    if (!section.isRectCollided(this->region))
        return {{},{},{},{}};
    else if (isLeaf())
        return {{this},{this},{this},{this}};

    Shell nw = child[0]->triangulate(triangles, section);
    Shell ne = child[1]->triangulate(triangles, section);
    Shell sw = child[2]->triangulate(triangles, section);
    Shell se = child[3]->triangulate(triangles, section);

    Shell inner
    {
        combine(nw.south, ne.south),  // north
        combine(sw.north, se.north),  // south
        combine(ne.west, se.west),    // east
        combine(nw.east, sw.east)     // west
    };

    zip(triangles, inner.west, inner.east);
    zip(triangles, inner.north, inner.south);

    return Shell
    {
        combine(nw.north, ne.north),  // north
        combine(sw.south, se.south),  // south
        combine(ne.east, se.east),    // east
        combine(nw.west, sw.west)     // west
    };
}

void SurfaceQuadTree::split(int times)
{
    if (times <= 0)
        return;

    vert = NULL;

    dimension2df size = region.getSize() / 2.0f;
    for (int i=0; i<4; ++i)
    {
        vector2df upper_left(
            size.Width * (i&1) + region.UpperLeftCorner.X,
            size.Height * ((i>>1)&1) + region.UpperLeftCorner.Y
        );
        rectf quadrant(upper_left, size);
        child[i] = new SurfaceQuadTree(quadrant, surface);
        child[i]->split(times-1);
    }
}

SurfaceQuadTree::SurfaceQuadTree(rectf region_, TPS::ThinPlateQuilt& surface_) :
    ref_count(0), region(region_), surface(surface_)
{
    irr::video::S3DVertex vtx;
    vtx.Pos.X = region.getCenter().X;
    vtx.Pos.Y = region.getCenter().Y;
    vtx.Pos.Z = surface.heightAt(vtx.Pos.X, vtx.Pos.Y);
    vert = new PossibleVertex(vtx);
}

void SurfaceQuadTree::testVertices(rectf& rect)
{
    rect.repair();

    if (isLeaf())
        rect.addInternalPoint(vert->getPos().X, vert->getPos().Y);
    else
        for (int i=0; i<4; ++i)
            child[i]->testVertices(rect);
}

void ::Bindings::Custom::intrusive_ptr_add_ref(SurfaceQuadTree const* p)
{
    ++(p->ref_count);
}

void ::Bindings::Custom::intrusive_ptr_release(SurfaceQuadTree const* p)
{
    if (!--(p->ref_count))
        delete p;
}

