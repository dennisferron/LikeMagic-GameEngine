// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "irrlicht.h"
#include "Bindings/Custom/PossibleVertex.hpp"

#include <map>
#include <vector>
#include <set>

namespace Bindings { namespace Custom {

class LinkSplitter
{
private:
    irr::scene::IMeshBuffer* oldMeshBuf;
    float zCut;

    std::map<std::pair<int, int>, PsblVertPtr> splitLinksMidpoints;
    std::vector<PsblVertPtr> existingVertices;

    PsblVertPtr splitLink(int oldIndexLeft, int oldIndexRight);

public:

    LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, float zCut_);
    PsblVertPtr processLink(std::vector<PsblVertPtr>& left, std::vector<PsblVertPtr>& right, int a, int b);
    void addConvexShape(std::vector<PsblVertPtr> const& newShape, irr::scene::SMeshBuffer* newMeshBuf, irr::core::vector3df offset);
    void addEdgeLinks(std::vector<PsblVertPtr> const& shape, std::set<std::pair<PsblVertPtr,PsblVertPtr>>& links);
    PsblVertPtr getVert(int oldIndex);
    int compareZ(int oldIndex);
    int compareZ(PsblVertPtr vert);
    std::vector<PsblVertPtr> chopLink(PsblVertPtr left, PsblVertPtr right, int numNewPoints);
    void insertPoints(std::vector<PsblVertPtr>& shape, PsblVertPtr left, PsblVertPtr right, std::vector<PsblVertPtr> const& source);
};


}}
