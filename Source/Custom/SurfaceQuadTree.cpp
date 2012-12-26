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


void SurfaceQuadTree::sweep(std::vector<PsblVertPtr>& triangles, irr::core::rectf const& section, Visitor* visitor)
{
    float tolerance = 0.01f;

    rectf sweepline;
    sweepline.UpperLeftCorner = region.UpperLeftCorner;
    sweepline.LowerRightCorner.Y = region.LowerRightCorner.Y;
    sweepline.LowerRightCorner.X =
        sweepline.UpperLeftCorner.X + tolerance;

    while (true)
    {
        cout << sweepline.UpperLeftCorner.X << endl;

        auto on_y = [](QuadTreePtr const& a, QuadTreePtr const& b){return a->region.getCenter().Y < b->region.getCenter().Y; };

        vector<QuadTreePtr> left;
        dumpLeaves(left, sweepline);

        //cout << endl << "left" << endl;
        //for (auto l : left)
        //    cout << l->getPath() << endl;

        // advance to right side list
        sweepline.UpperLeftCorner.X =
            (*min_element(left.begin(), left.end(),
                [](QuadTreePtr const& a, QuadTreePtr const& b)
                    {return a->region.LowerRightCorner.X < b->region.LowerRightCorner.X; }
            ))->region.LowerRightCorner.X + tolerance;
        sweepline.LowerRightCorner.X = sweepline.UpperLeftCorner.X + tolerance;

        vector<QuadTreePtr> right;
        dumpLeaves(right, sweepline);

        //cout << endl << "right" << endl;
        //for (auto r : right)
        //    cout << r->getPath() << endl;

        if (right.size() == 0)
            break;

        sort(left.begin(), left.end(), on_y);
        sort(right.begin(), right.end(), on_y);
        zip(triangles, left, right, visitor);
    }
}

bool SurfaceQuadTree::isBetween(double lesser, double middle, double greater)
{
    if (lesser < greater)
        return lesser <= middle && middle <= greater;
    else
        return greater <= middle && middle <= lesser;
}

bool SurfaceQuadTree::crossesBoundary(double lower_bound, double upper_bound)
{
    double cx = region.getCenter().X;
    double cy = region.getCenter().Y;
    double c = surface.heightAt(cx, cy);

    if (isBetween(lower_bound, c, upper_bound))
        return true;

    double sy = region.UpperLeftCorner.Y;
    double ny = region.LowerRightCorner.Y;
    double wx = region.UpperLeftCorner.X;
    double ex = region.LowerRightCorner.X;

    double s = surface.heightAt(cx, sy);
    double n = surface.heightAt(cx, ny);
    double w = surface.heightAt(wx, cy);
    double e = surface.heightAt(ex, cy);

    return
        isBetween(s, lower_bound, c) ||
        isBetween(s, upper_bound, c) ||

        isBetween(n, lower_bound, c) ||
        isBetween(n, upper_bound, c) ||

        isBetween(w, lower_bound, c) ||
        isBetween(w, upper_bound, c) ||

        isBetween(e, lower_bound, c) ||
        isBetween(e, upper_bound, c) ;
}

void SurfaceQuadTree::fit(dimension2df min_size, double lower_bound, double upper_bound)
{
    if (isLeaf())
        if (region.getSize().Width/2 >= min_size.Width && region.getSize().Height/2 >= min_size.Height)
            if (crossesBoundary(lower_bound, upper_bound))
                split(1);

    if (!isLeaf())
        for (auto c : child)
            c->fit(min_size, lower_bound, upper_bound);
}

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

void SurfaceQuadTree::dumpLeaves(std::vector<QuadTreePtr>& result, rectf const& section)
{
    if (!section.isRectCollided(this->region))
        return;
    else if (isLeaf())
        result.push_back(this);
    else
        for (auto c : child)
            c->dumpLeaves(result, section);
}

std::vector<QuadTreePtr> SurfaceQuadTree::combine(std::vector<QuadTreePtr> const& first, std::vector<QuadTreePtr> const& second)
{
    std::vector<QuadTreePtr> result;
    result.insert(result.end(), first.begin(), first.end());
    result.insert(result.end(), second.begin(), second.end());

    if (result.size() > 0)
    {
        QuadTreePtr prev = *result.begin();


        for (QuadTreePtr cur : result)
        {
            if (prev != cur)
            {
                float prevX = prev->region.LowerRightCorner.X;
                float prevY = prev->region.LowerRightCorner.Y;
                float curX = cur->region.UpperLeftCorner.X;
                float curY = cur->region.UpperLeftCorner.Y;

                bool contX = abs(curX-prevX) < 0.1f;
                bool contY = abs(curY-prevY) < 0.1f;

                if (contX && contY)
                    cout << "Combined on diagonal" << endl;
                else if (!contX && !contY)
                    cout << "Combined nonsequential" << endl;
            }

            prev = cur;
        }
    }

    return result;
}

void SurfaceQuadTree::addTriangle(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c) const
{
    if (a != b && b != c && c != a)
    {
        triangles.push_back(a->vert);
        triangles.push_back(b->vert);
        triangles.push_back(c->vert);

        //triangles.push_back(c->vert);
        //triangles.push_back(b->vert);
        //triangles.push_back(a->vert);
    }
}

void SurfaceQuadTree::addQuad(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, QuadTreePtr const& d) const
{
    /*
    b---c
    | / |
    a---d
    */

    if (a->vert->distSQ(c->vert) < b->vert->distSQ(d->vert))
    {
        addTriangle(triangles, a, c, b);
        addTriangle(triangles, a, d, c);
    }
    else
    {
        addTriangle(triangles, b, d, c);
        addTriangle(triangles, a, d, b);
    }
}

bool SurfaceQuadTree::isAdjacent(QuadTreePtr const& that) const
{
    float tolerance = 0.1f;
    vector2df displacement = this->region.getCenter() - that->region.getCenter();
    float dist_x = abs(displacement.X);
    float dist_y = abs(displacement.Y);
    dimension2df extent = this->region.getSize() / 2.0f + that->region.getSize() / 2.0f;
    bool adj_x = dist_x <= extent.Width + tolerance;
    bool adj_y = dist_y <= extent.Height + tolerance;
    return adj_x && adj_y;
}

void SurfaceQuadTree::zip(std::vector<PsblVertPtr>& triangles, std::vector<QuadTreePtr> const& list_a, std::vector<QuadTreePtr> const& list_b, Visitor* visitor=NULL)
{
    if (list_a.size() == 0 || list_b.size() == 0 || (list_a.size()+list_b.size()) < 3)
        return;

/*
    // Brute force approach for testing:

    auto total = combine(list_a, list_b);

    for (auto a : total)
        for (auto b : total)
            for (auto c : total)
                if (a != b && b != c && c != a)
                    if (a->isAdjacent(b) && b->isAdjacent(c) && c->isAdjacent(a))
                        addTriangle(triangles, a, b, c);
*/
    auto a1 = list_a.begin();
    auto b1 = list_b.begin();

    bool end_a;
    bool end_b;
    while (true)
    {
        auto a2 = a1+1;
        auto b2 = b1+1;

        end_a = (a2==list_a.end());
        end_b = (b2==list_b.end());

        if (visitor)
            visitor->check(*a1, end_a?NULL:*a2, *b1, end_b?NULL:*b2);

        bool adj_a = !end_a && (*a2)->isAdjacent(*b1);
        bool adj_b = !end_b && (*b2)->isAdjacent(*a1);

        if (adj_a && !adj_b)
            addTriangle(triangles, *a1, *b1, *a2);
        else if (!adj_a && adj_b)
            addTriangle(triangles, *a1, *b1, *b2);
        else if (adj_a && adj_b)
            addQuad(triangles, *a1, *a2, *b2, *b1);

        if (adj_a)
            a1 = a2;
        else if (adj_b)
            b1 = b2;
        else
            break;
    }
}

SurfaceQuadTree::Shell SurfaceQuadTree::triangulate(std::vector<PsblVertPtr>& triangles, rectf const& section, Visitor* visitor)
{
    if (!section.isRectCollided(this->region))
        return {{},{},{},{}};
    else if (isLeaf())
        return {{this},{this},{this},{this}};

    Shell sw = child[0]->triangulate(triangles, section, visitor);
    Shell se = child[1]->triangulate(triangles, section, visitor);
    Shell nw = child[2]->triangulate(triangles, section, visitor);
    Shell ne = child[3]->triangulate(triangles, section, visitor);

    Shell inner
    {
        combine(nw.south, ne.south),  // north
        combine(sw.north, se.north),  // south
        combine(se.west, ne.west),    // east
        combine(sw.east, nw.east)     // west
    };

    zip(triangles, inner.west, inner.east, visitor);
    zip(triangles, inner.north, inner.south, visitor);

    return Shell
    {
        combine(nw.north, ne.north),  // north
        combine(sw.south, se.south),  // south
        combine(se.east, ne.east),    // east
        combine(sw.west, nw.west)     // west
    };
}

std::string SurfaceQuadTree::getPath() const
{
    return path;
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

        std::string new_path = path + " " +
            ( quadrant.getCenter().Y < region.getCenter().Y ? "S" : "N") +
            ( quadrant.getCenter().X < region.getCenter().X ? "W" : "E");

        child[i] = new SurfaceQuadTree(quadrant, surface, new_path);
        child[i]->split(times-1);
    }
}

SurfaceQuadTree::SurfaceQuadTree(rectf region_, TPS::ThinPlateQuilt& surface_, std::string path_) :
    ref_count(0), region(region_), surface(surface_), path(path_)
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

