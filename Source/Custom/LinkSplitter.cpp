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


LinkSplitter::LinkSplitter(IMeshBuffer* oldMeshBuf_, float zCut_)
    : oldMeshBuf(oldMeshBuf_), zCut(zCut_), existingVertices(oldMeshBuf_->getVertexCount())
{
    // All of the old mesh buffers vertex will go in at least one of the result meshes.
    for (u32 i=0; i<oldMeshBuf->getVertexCount(); ++i)
        existingVertices[i] = PsblVertPtr(new PossibleVertex(MeshTools::getBaseVertex(oldMeshBuf, i)));
}

// Adds point a, point b, and/or the midpoint between a and b
PsblVertPtr LinkSplitter::processLink(std::vector<PsblVertPtr>& leftInd, std::vector<PsblVertPtr>& rightInd, int a, int b)
{
    // Smart ptr empty unless the link is split.
    PsblVertPtr mid;

    int whichSideA = compareZ(a);
    int whichSideB = compareZ(b);

    // Add a to left side if it is left or in both
    if (whichSideA < 0 || whichSideA == 0)
    {
        auto vert = getVert(a);
        leftInd.push_back(vert);

        if (whichSideA == 0)
            mid = vert;
    }

    // Add a to right side if it is right or in both
    if (whichSideA > 0 || whichSideA == 0)
    {
        auto vert = getVert(a);
        rightInd.push_back(vert);

        if (whichSideA == 0)
            mid = vert;
    }

    // Link crosses like this:  a --|--> b
    if (whichSideA < 0 && whichSideB > 0)
    {
        mid = splitLink(a, b);
        leftInd.push_back(mid);
        rightInd.push_back(mid);
    }
    // Link crosses like this: b <--|-- a
    else if (whichSideB < 0 && whichSideA > 0)
    {
        mid = splitLink(b, a);
        leftInd.push_back(mid);
        rightInd.push_back(mid);
    }

    // Don't add vertex B here.  Since all 3 sides of the triangle
    // will be processed, eventually B will be passed to the function as A.

    // Return the midpoint of the split link or NULL.
    return mid;
}

int LinkSplitter::compareZ(int index)
{
    S3DVertex& vert = MeshTools::getBaseVertex(oldMeshBuf, index);
    float z = vert.Pos.Z;
    if (irr::core::equals(z, zCut))
        return 0;
    else if (z < zCut)
        return -1;
    else
        return 1;
}

int LinkSplitter::compareZ(PsblVertPtr vert)
{
    // TODO:  Does this function ever fail to see a match if lerp doesn't scale the Z perfectly?

    float z = vert->getPos().Z;
    if (irr::core::equals(z, zCut))
        return 0;
    else if (z < zCut)
        return -1;
    else
        return 1;
}


PsblVertPtr LinkSplitter::getVert(int oldIndex)
{
    return existingVertices[oldIndex];
}

PsblVertPtr LinkSplitter::splitLink(int oldIndexLeft, int oldIndexRight)
{
    auto iter = splitLinksMidpoints.find(make_pair(oldIndexLeft, oldIndexRight));
    if (iter != splitLinksMidpoints.end())
        return iter->second;
    else
    {
        S3DVertex& vLeft  = MeshTools::getBaseVertex(oldMeshBuf, oldIndexLeft);
        S3DVertex& vRight = MeshTools::getBaseVertex(oldMeshBuf, oldIndexRight);

        float scale = (zCut - vLeft.Pos.Z) / (vRight.Pos.Z - vLeft.Pos.Z);

        // Test if scale is going all screwy due to a bad division result.
        if (! (scale >= 0-ROUNDING_ERROR_f32 && scale <= 1.0f+ROUNDING_ERROR_f32) )
        {
            throw std::runtime_error("Hit a bad division result while slicing a mesh.");
        }

        std::map<std::pair<int, int>, PsblVertPtr>::mapped_type result = PsblVertPtr(new PossibleVertex(vLeft, vRight, scale));
        splitLinksMidpoints.insert(make_pair(make_pair(oldIndexLeft, oldIndexRight), result));
        return result;
    }
}

void LinkSplitter::addConvexShape(vector<PsblVertPtr> const& newShape, SMeshBuffer* newMeshBuf, vector3df offset)
{
    u32 numCorners = newShape.size();
    switch (numCorners)
    {
        case 0:
            // Nothing touches
            break; // no triangle
        case 1:
            // Only a corner touches
            break; // incomplete triangle
        case 2:
            // Only a side touches
            break; // incomplete triangle
        case 3:  // add 1 triangle
            for (int j=0; j<3; ++j)
                newShape[j]->addToMeshBuf(newMeshBuf, offset);
            break;
//        case 4:  // add quad, need to make two triangles
//        {
//            // If you don't have the braces around the variable declarations here, gcc gives the cryptic error "jump to case label".
//            // The GCC maintainers closed someone's bug report about this problem saying that's expected behavior, you should just know
//            // that the problem is the variables escape scope to the next label (even though I'm not actually using any of them there).
//            // Really GCC guys?  Really?  "jump to case label" - you think that's an acceptable error message?  F*** you.
//            PsblVertPtr A=newShape[0], B=newShape[1], C=newShape[2], D=newShape[3];
//            PsblVertPtr acTris[] = { A,B,C , A,C,D };
//            PsblVertPtr bdTris[] = { B,C,D , B,D,A };
//            PsblVertPtr* twoTris = A->distSQ(C) < B->distSQ(D) ? acTris : bdTris;
//            for (int j=0; j<6; ++j)
//            {
//                twoTris[j]->addToMeshBuf(newMeshBuf, offset);
//            }
//
//            break;
//        }
        default:
        {
            // Naive, greedy, recursive ear clip algorithm.  Inefficient but dead simple:
            // Clip off narrowest triangle, and recurse until the remaining shape is a 3-gon.
            // Won't work for the general case, but we know the polygon is not concave.

            unsigned int bestIndex = 0;
            float bestRatio = 1.99f;
            for (unsigned int i=0; i < numCorners; ++i)
            {
                float a = newShape[i]->dist(newShape[ (i+numCorners-1) % numCorners ]);
                float b = newShape[i]->dist(newShape[ (i+1) % numCorners ]);
                float c = newShape[ (i+numCorners-1) % numCorners ]->distSQ(newShape[ (i+1) % numCorners ]);

                float ratio = c / (a+b);

                if (ratio < bestRatio)
                    bestIndex = i;
            }

            newShape[ (bestIndex+numCorners-1) % numCorners]->addToMeshBuf(newMeshBuf, offset);
            newShape[ bestIndex ]->addToMeshBuf(newMeshBuf, offset);
            newShape[ (bestIndex+1) % numCorners]->addToMeshBuf(newMeshBuf, offset);

            vector<PsblVertPtr> smallerShape;
            for (unsigned int i=0; i<numCorners; ++i)
                if (i != bestIndex)
                    smallerShape.push_back(newShape[i]);

            addConvexShape(smallerShape, newMeshBuf, offset);
        }
    }
}

std::vector<PsblVertPtr> LinkSplitter::chopLink(PsblVertPtr left, PsblVertPtr right, int numNewPoints)
{
    std::vector<PsblVertPtr> result;

    for (int i=1; i<=numNewPoints; ++i)
    {
        float scale = ((float)i) / (numNewPoints+1.0f);
        PsblVertPtr pv(new PossibleVertex(left, right, scale));
        vector3df pos = pv->getPos();
        //pos.Y += 0.03f*(i+1);
        pv->setPos(pos);
        result.push_back(pv);
    }

    return result;
}

void print(PsblVertPtr const& pv, PsblVertPtr const& base)
{
    vector3df pos = pv->getPos() - base->getPos();
    cout << "(" << (int)(10*pos.X) << "," << (int)(10*pos.Y) << "," << (int)(10*pos.Z) << ")";
}

void print(std::vector<PsblVertPtr> const& list)
{
    PsblVertPtr base = list[0];

    for (PsblVertPtr pv : list)
    {
        cout << " ";
        print(pv, base);
    }
    cout << endl;
}

void LinkSplitter::insertPoints(std::vector<PsblVertPtr>& shape, PsblVertPtr left, PsblVertPtr right, std::vector<PsblVertPtr> const& source)
{
    auto iterL = std::find(shape.begin(), shape.end(), left);
    auto iterR = std::find(shape.begin(), shape.end(), right);

    bool leftToRight = ((iterR-iterL) == 1) || (iterR == shape.begin() && iterL == (shape.end()-1));

    cout << "Input: "  << (leftToRight? "(left to right)" : "(right to left)") << ": ";
    print({shape[0], left, right, source[0]});

    cout << "Old shape: ";
    print(shape);

    if (leftToRight)
        shape.insert(iterL+1, source.begin(), source.end());
    else
        shape.insert(iterR+1, source.rbegin(), source.rend());

    cout << "New shape: ";
    print(shape);
}

void LinkSplitter::addEdgeLinks(vector<PsblVertPtr> const& shape, set<pair<PsblVertPtr,PsblVertPtr>>& links)
{
    if (shape.size() >= 2)
    {
        for (size_t i=0; i<shape.size(); ++i)
        {
            PsblVertPtr a = shape[i];
            PsblVertPtr b = shape[(i+1)%shape.size()];
            if (compareZ(a)==0 && compareZ(b)==0)
                links.insert(make_pair(a,b));
        }
    }
}

