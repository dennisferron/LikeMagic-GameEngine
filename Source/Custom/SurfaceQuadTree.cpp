// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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
        //cout << sweepline.UpperLeftCorner.X << endl;

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
        zip(triangles, left, right, -10000, 10000, visitor);
    }
}

bool SurfaceQuadTree::isBetween(double lesser, double middle, double greater)
{
    if (lesser < greater)
        return lesser <= middle && middle <= greater;
    else
        return greater <= middle && middle <= lesser;
}

int SurfaceQuadTree::boundaryCrossings(vector<double> boundaries)
{
    double cx = region.getCenter().X;
    double cy = region.getCenter().Y;
    double sy = region.UpperLeftCorner.Y;
    double ny = region.LowerRightCorner.Y;
    double wx = region.UpperLeftCorner.X;
    double ex = region.LowerRightCorner.X;

    vector<double> test_points =
    {
        surface.heightAt(cx, cy),

        surface.heightAt(cx, sy),
        surface.heightAt(cx, ny),
        surface.heightAt(wx, cy),
        surface.heightAt(ex, cy),

        surface.heightAt(wx, sy),
        surface.heightAt(wx, ny),
        surface.heightAt(ex, sy),
        surface.heightAt(ex, ny)
    };

    int crossings = 0;

    for (int b=0; b<boundaries.size(); ++b)
    {
        bool crosses = false;
        for (auto t1 : test_points)
            for (auto t2 : test_points)
                if (isBetween(t1, boundaries[b], t2))
                {
                    crosses = true;
                    goto end;
                }
    end:
        if (crosses)
            ++crossings;
    }
    return crossings;
}

double SurfaceQuadTree::closestHeight(double h, std::vector<double> boundaries)
{
    double best = *boundaries.begin();
    for (double b : boundaries)
        if (abs(h-b) < abs(h-best))
            best = b;
    return best;
}

void SurfaceQuadTree::fit(dimension2df min_size, vector<double> boundaries)
{
    if (isLeaf())
    {
        int crossings = boundaryCrossings(boundaries);

        if (crossings > 0)
        {
            if (crossings > 1 || (region.getSize().Width/2 >= min_size.Width && region.getSize().Height/2 >= min_size.Height))
            {
                split(1);
            }
            else
            {
                vector3df vert_pos = vert->getPos();
                double expected_height = closestHeight(vert_pos.Z, boundaries);
                vector2df best_pos = locate(expected_height);
                vert_pos.X = best_pos.X;
                vert_pos.Y = best_pos.Y;
                vert_pos.Z = expected_height;
                vert->setPos(vert_pos);
            }
        }
    }

    if (!isLeaf())
        for (auto c : child)
            c->fit(min_size, boundaries);
}

// Locate the best position within the cell for a vertex based on
// a weighted average the corner positions by their difference from expected height.
vector2df SurfaceQuadTree::locate(double expected_height)
{
    float total_weight = 0.0;
    vector2df total_pos;

    double cx = region.getCenter().X;
    double cy = region.getCenter().Y;
    double sy = region.UpperLeftCorner.Y;
    double ny = region.LowerRightCorner.Y;
    double wx = region.UpperLeftCorner.X;
    double ex = region.LowerRightCorner.X;

    vector<vector2df> test_points =
    {
        vector2df(cx, cy),

        vector2df(cx, sy),
        vector2df(cx, ny),
        vector2df(wx, cy),
        vector2df(ex, cy),

        vector2df(wx, sy),
        vector2df(wx, ny),
        vector2df(ex, sy),
        vector2df(ex, ny)
    };

    for (vector2df p : test_points)
    {
        double height = surface.heightAt(p.X, p.Y);
        float inverse_weight = abs(height - expected_height);
        float adjusted_weight = 1.0f / (inverse_weight + 0.001f);

        total_pos += adjusted_weight * p;
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

                //if (contX && contY)
                //    cout << "Combined on diagonal" << endl;
                //else if (!contX && !contY)
                //sit    cout << "Combined nonsequential" << endl;
            }

            prev = cur;
        }
    }

    return result;
}

void SurfaceQuadTree::addTriangle(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, double min_height, double max_height, Visitor* visitor) const
{
    if (a != b && b != c && c != a && isBetween(a, b, c, min_height, max_height))
    {
        triangles.push_back(a->vert);
        triangles.push_back(b->vert);
        triangles.push_back(c->vert);

        //triangles.push_back(c->vert);
        //triangles.push_back(b->vert);
        //triangles.push_back(a->vert);

        if (visitor)
            visitor->addTriangle(a, b, c);
    }
}

void SurfaceQuadTree::addQuad(std::vector<PsblVertPtr>& triangles, QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, QuadTreePtr const& d, double min_height, double max_height, Visitor* visitor) const
{
    /*
    b---c
    | / |
    a---d
    */

    if (a->vert->distSQ(c->vert) < b->vert->distSQ(d->vert))
    {
        addTriangle(triangles, a, c, b, min_height, max_height, visitor);
        addTriangle(triangles, a, d, c, min_height, max_height, visitor);
    }
    else
    {
        addTriangle(triangles, b, d, c, min_height, max_height, visitor);
        addTriangle(triangles, a, d, b, min_height, max_height, visitor);
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

bool SurfaceQuadTree::isBetween(double min_height, double max_height) const
{
    return vert->getPos().Z >= min_height && vert->getPos().Z <= max_height;
}

bool SurfaceQuadTree::isBetween(QuadTreePtr const& a, QuadTreePtr const& b, QuadTreePtr const& c, double min_height, double max_height) const
{
    return
        a->isBetween(min_height, max_height) &&
        b->isBetween(min_height, max_height) &&
        c->isBetween(min_height, max_height);
}

void SurfaceQuadTree::zip(std::vector<PsblVertPtr>& triangles, std::vector<QuadTreePtr> const& list_a, std::vector<QuadTreePtr> const& list_b, double min_height, double max_height, Visitor* visitor)
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
        SurfaceQuadTree* qa1 = a1->get();
        SurfaceQuadTree* qb1 = b1->get();
        SurfaceQuadTree* qa2 = NULL;
        SurfaceQuadTree* qb2 = NULL;

        auto a2 = a1+1;
        auto b2 = b1+1;

        end_a = (a2==list_a.end());
        end_b = (b2==list_b.end());

        if (end_a && end_b)
            break;

        if (!end_a)
            qa2 = a2->get();
        if (!end_b)
            qb2 = b2->get();

        //cout << "a1 = " << qa1->getPath() << "  b1 = " << qb1->getPath();
        //cout << "  a2 = " << (end_a? "NULL" : qa2->getPath());
        //cout << "  b2 = " << (end_b? "NULL" : qb2->getPath());
        //cout << endl;

        if (visitor)
            visitor->check(*a1, end_a?NULL:*a2, *b1, end_b?NULL:*b2);

        bool adj_a = !end_a && (*a2)->isAdjacent(*b1);
        bool adj_b = !end_b && (*b2)->isAdjacent(*a1);

        if (adj_a && !adj_b)
            addTriangle(triangles, *a1, *b1, *a2, min_height, max_height, visitor);
        else if (!adj_a && adj_b)
            addTriangle(triangles, *a1, *b1, *b2, min_height, max_height, visitor);
        else if (adj_a && adj_b)
            addQuad(triangles, *a1, *a2, *b2, *b1, min_height, max_height, visitor);

        if (adj_a)
            a1 = a2;

        if (adj_b)
            b1 = b2;

        // If neither are adjacent but we are not ended, skip to next.
        if (!adj_a && !adj_b)
        {
            a1 = a2;
            b1 = b2;
        }
    }
}

SurfaceQuadTree::Shell SurfaceQuadTree::triangulate(std::vector<PsblVertPtr>& triangles, rectf const& section, double min_height, double max_height, Visitor* visitor)
{
    if (!section.isRectCollided(this->region))
        return {{},{},{},{}};
    else if (isLeaf())
        return {{this},{this},{this},{this}};

    Shell sw = child[0]->triangulate(triangles, section, min_height, max_height, visitor);
    Shell se = child[1]->triangulate(triangles, section, min_height, max_height, visitor);
    Shell nw = child[2]->triangulate(triangles, section, min_height, max_height, visitor);
    Shell ne = child[3]->triangulate(triangles, section, min_height, max_height, visitor);

    // Zip the north and south sides together in one west-east line.
    //cout << "zip long north+south halves" << endl;
    zip(triangles, combine(nw.south, ne.south), combine(sw.north, se.north), min_height, max_height, visitor);

    // Zip the west and east sides together in two independent south-north runs.
    // Zipping these two haves separately skips the middle square which was already triangulated.
    //cout << "zip short sw+se" << endl;
    zip(triangles, sw.east, se.west, min_height, max_height, visitor);
    //cout << "zip short nw+ne" << endl;
    zip(triangles, nw.east, ne.west, min_height, max_height, visitor);

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

