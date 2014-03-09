// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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

irr::scene::IMesh* MeshTools::createHillMesh(SurfaceQuadTree& tree, rectf section, double min_height, double max_height)
{
    std::vector<PsblVertPtr> triangles;

    /*
    tree.split(1);

    auto ptr = tree.child[1];
    for (int i=0; i<2; ++i)
    {
        ptr->split(1);
        ptr = ptr->child[3*(i+1)%4];
    }

    ptr = tree.child[2];
    for (int i=0; i<5; ++i)
    {
        ptr->split(1);
        ptr = ptr->child[3*(i+1)%4];
    }
    */

    struct Visitor : public SurfaceQuadTree::Visitor
    {
        vector<pair<QuadTreePtr, QuadTreePtr>> pairs;

        typedef tuple<QuadTreePtr, QuadTreePtr> edge;

        typedef vector<edge> triangle;
        vector<triangle> triangles;

        typedef vector<triangle>::const_iterator triangle_iter;
        std::map<edge, vector<triangle>> edge_to_triangle;

        bool crosses(edge e1, edge e2)
        {
            // Ignore if the edges share a vertex; that is not a crossing.
            if (
                get<0>(e1)->vert == get<0>(e2)->vert ||
                get<0>(e1)->vert == get<1>(e2)->vert ||
                get<1>(e1)->vert == get<0>(e2)->vert ||
                get<1>(e1)->vert == get<1>(e2)->vert
            )
                return false;

            // line2d(T xa, T ya, T xb, T yb)
            vector3df pos1a = get<0>(e1)->vert->getPos();
            vector3df pos1b = get<1>(e1)->vert->getPos();
            line2df line1(pos1a.X, pos1a.Y, pos1b.X, pos1b.Y);

            vector3df pos2a = get<0>(e2)->vert->getPos();
            vector3df pos2b = get<1>(e2)->vert->getPos();
            line2df line2(pos2a.X, pos2a.Y, pos2b.X, pos2b.Y);

            vector2df out;
            return line1.intersectWith(line2, out);
        }

        bool compareEdge(edge e, std::string from, std::string to)
        {
            return
                get<0>(e)->getPath() == from &&
                get<1>(e)->getPath() == to;
        }

        bool findEdge(triangle t, std::string from, std::string to)
        {
            return compareEdge(t[0], from, to) || compareEdge(t[1], from, to) || compareEdge(t[2], from, to);
        }

        virtual void addTriangle(QuadTreePtr a, QuadTreePtr b, QuadTreePtr c)
        {
            // If a,b,c already in triangles, duplicate triangle error.

            // foreach edge in the new triangle,
            // find other triangles that share one edge with this one
            // test the other 2x2 edges for intersection.
            triangle new_triangle(
            {
                make_tuple(a,b), make_tuple(b,c), make_tuple(c,a)
            });

            //if (findEdge(new_triangle, "Root SW SW SW NW SE", "Root SW SW SW NW NW"))
            //    cout << "found" << endl;

            //if (findEdge(new_triangle, "Root SW SW SW NW NE", "Root SW SW SW NW SW"))
            //    cout << "found" << endl;

            for (edge e_same : new_triangle)
                for (edge e_check : new_triangle)
                    if (e_same != e_check)
                        for (triangle contiguous : edge_to_triangle[e_same])
                            for (edge e_existing : contiguous)
                                if (e_existing != e_same)
                                    if (crosses(e_check, e_existing))
                                    {
                                        cout << "detected crossing, new is " << get<0>(e_check)->getPath() << "-" << get<1>(e_check)->getPath()
                                            << " old is " << get<0>(e_existing)->getPath() << "-" << get<1>(e_existing)->getPath() << endl;
                                    }

            triangles.push_back(new_triangle);
            edge_to_triangle[make_tuple(a,b)].push_back(new_triangle);
            edge_to_triangle[make_tuple(b,c)].push_back(new_triangle);
            edge_to_triangle[make_tuple(c,a)].push_back(new_triangle);
            edge_to_triangle[make_tuple(b,a)].push_back(new_triangle);
            edge_to_triangle[make_tuple(c,b)].push_back(new_triangle);
            edge_to_triangle[make_tuple(a,c)].push_back(new_triangle);
        }

        virtual void check(QuadTreePtr a1, QuadTreePtr a2, QuadTreePtr b1, QuadTreePtr b2)
        {
        }
    };

    Visitor visitor;
    tree.triangulate(triangles, section, min_height, max_height, &visitor);
    //tree.sweep(triangles, section, &visitor);

   //cout << "num triangle points: " << triangles.size() << endl;

    vector<QuadTreePtr> leaves;
    tree.dumpLeaves(leaves);

    //cout << "num leaves: " << leaves.size() << endl;

/*
    for (QuadTreePtr p1 : leaves)
        for (QuadTreePtr p2 : leaves)
            if (p1 != p2)
                if (p1->isAdjacent(p2))
                    if (!visitor.has(p1, p2))
                    {
                        auto sz1 = p1->region.getSize();
                        auto sz2 = p2->region.getSize();
                        auto c1 = p1->region.getCenter();
                        auto c2 = p2->region.getCenter();
                        char const* path1 = p1->getPath().c_str();
                        char const* path2 = p2->getPath().c_str();
                        cout << path1 << endl;
                        cout << path2 << endl;
                        cout << "Missing pair of adjacent vertices." << endl;
                    }

    float x1 = section.UpperLeftCorner.X;
    float x2 = section.LowerRightCorner.X;
    float y1 = section.UpperLeftCorner.Y;
    float y2 = section.LowerRightCorner.Y;
*/
    /*
        d---c
        | / |
        a---b
    */

    /*
    S3DVertex sa;
    sa.Pos = vector3df(x1, y1, 0);
    PsblVertPtr a = new PossibleVertex(sa);

    S3DVertex sb;
    sb.Pos = vector3df(x2, y1, 0);
    PsblVertPtr b = new PossibleVertex(sb);

    S3DVertex sc;
    sc.Pos = vector3df(x2, y2, 0);
    PsblVertPtr c = new PossibleVertex(sc);

    S3DVertex sd;
    sd.Pos = vector3df(x1, y2, 0);
    PsblVertPtr d = new PossibleVertex(sd);

    // a-b-c
    // a-c-d
    triangles.push_back(a);
    triangles.push_back(b);
    triangles.push_back(c);

    triangles.push_back(a);
    triangles.push_back(c);
    triangles.push_back(d);

    triangles.push_back(c);
    triangles.push_back(b);
    triangles.push_back(a);

    triangles.push_back(d);
    triangles.push_back(c);
    triangles.push_back(a);
    */

	SMeshBuffer* buffer = new SMeshBuffer();

    for (auto pv : triangles)
        pv->addToMeshBuf(buffer, vector3df());

    if (buffer->getIndexCount() % 3 > 0)
        throw std::logic_error("SurfaceQuadTree triangulation added a 'triangle' with less than 3 vertices in it.");

    //cout << "num vertices " << buffer->getVertexCount() << endl;
    //cout << "num indices " << buffer->getIndexCount() << endl;

	buffer->recalculateBoundingBox();
	buffer->setHardwareMappingHint(EHM_STATIC);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();

	return mesh;
}
