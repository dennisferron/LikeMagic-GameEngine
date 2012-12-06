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
#include "ThinPlateSpline/ThinPlateSpline.hpp"

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

typedef MeshTools::PsblVertPtr PsblVertPtr;


MeshTools::SplitMeshResult MeshTools::createHillMesh(ThinPlateQuilt& tps, rectf region, float gridSize)
{
	SMeshBuffer* buffer = new SMeshBuffer();

	dimension2du regionSize(region.getSize().Width, region.getSize().Height);

	// Preallocate vertex buffer to the size we know we'll need.
	buffer->Vertices.set_used(regionSize.Width*regionSize.Height);

	// Amount of TCoord per unit of x,y in image.
    vector2df tCoordsScale(1.0f / regionSize.Width, 1.0f / regionSize.Height);

    // Whether we put y on the outside or x on the outside, doesn't matter, because we are
    // using getIndex() to find where x and y map too.  However, I happen to know I made getIndex
    // put x's together, y in rows, and looping in the same rank order might have better cache performance
    // because it should access the vertices in the same order they are in the array.
    for (u32 y=0; y < regionSize.Height; ++y)
    {
        for (u32 x=0; x < regionSize.Width; ++x)
        {
            u32 index = getIndex(regionSize, x, y);

            if (index < 0 || index >= buffer->Vertices.size())
                throw std::logic_error("Index out of range.");

            S3DVertex& vert = buffer->Vertices[index];

            // No special coloration
            vert.Color = SColor(255,255,255,255);

            // Scale texture to tile.
            vert.TCoords = vector2df(x,y) * tCoordsScale;

            float thisHeight = tps.heightAt(region.UpperLeftCorner.X+x, region.UpperLeftCorner.Y+y);

            vert.Pos.set(x, y, thisHeight);

            // I'm only averaging normals along the 4 compass directions.  It's
            // arguable whether diagonals should count; I chose to ignore diagonals.
            // Ignoring diagonals allows me to assume the "run" in rise/run is always
            // just one unit; if you add diagonals here you'll also need to change
            // the slope calculation to use the actual distance instead of assuming 1.
            vector2di offsetsArray[] = {
                vector2di( 1, 0),  //  3 o'clock
                vector2di( 0, 1),  // 12 o'clock
                vector2di(-1, 0),  //  9 o'clock
                vector2di( 0,-1)   //  6 o'clock
            };

            // Calculate the normals of the surrounding slopes.
            // Uses the image, not just the tile patch size, so it will
            // calculate correct normals for vertices on tile edges.
            for (size_t i=-0; i < 4; ++i)
            {
                vector2di offset = vector2di(x,y) + offsetsArray[i];

                // Skip this offset if it's outside the image
                if (offset.X < 0 || offset.Y < 0 || offset.X >= (s32)regionSize.Width || offset.Y >= (s32)regionSize.Height)
                    continue;

                float otherHeight = tps.heightAt(region.UpperLeftCorner.X+offset.X, region.UpperLeftCorner.Y+offset.Y);

                // The code Irrlicht's in terrain scene node does all kinds of complicated
                // business with cross products and such - waaay over complicated.  You don't need
                // all that stuff.  Dude it' s a heightmap: all you need to worray about is
                // rise over run on unit intervals!  Algebra 1 type stuff, y = mx + c

                // Calculate the rise of the line over the run, taking into account the fact
                // that the offset could be in either direction.
                float rise = (offset.X < 0 || offset.Y < 0)? thisHeight - otherHeight : otherHeight - thisHeight;

                // Assuming that run = 1, m = rise / run is just m = rise.
                float m = rise;

                // The the slope of the normal is just the negative of the reciprocal of the line slope.
                float n = -1.0f / rise;

                // The X,Y of the normal vector is just going to be the X and Y of the offset
                // (think about it - obviously the normal of the slope must tilt in the direction of the run)
                // and the Z of the normal vector is just the slope of the normal over that run.
                vector3df normVect(offset.X, offset.Y, n);

                //vert.Normal += normVect;
            }

            //vert.Normal.normalize();
            vert.Normal.set(0,0,-1.0f);
        }
    }

    // Pre-allocate index data to 2*3*Width*Height for triangles.
    // There is actually 1 less square per count of vertices though,
    // for instance if you had 2x2 vertices, you only have 1 square.
    buffer->Indices.set_used(2*3*(regionSize.Width-1)*(regionSize.Height-1));

    // Start with 1 and generate all the triangles from their top right corners.
    // Like this (A is top right corner at x,y):
    //
    //              y=1  B---A
    //                   | / |
    //              y=0  C---D
    //                  x=0 x=1
    for (u32 dst=0, x=1; x < regionSize.Width; ++x)
    {
        for (u32 y=1; y < regionSize.Height; ++y)
        {
            u32 A = getIndex(regionSize, x,   y   );
            u32 B = getIndex(regionSize, x-1, y   );
            u32 C = getIndex(regionSize, x-1, y-1 );
            u32 D = getIndex(regionSize, x,   y-1 );

            buffer->Indices[dst++] = C;
            buffer->Indices[dst++] = B;
            buffer->Indices[dst++] = A;

            buffer->Indices[dst++] = D;
            buffer->Indices[dst++] = C;
            buffer->Indices[dst++] = A;
        }
    }

	buffer->recalculateBoundingBox();
	buffer->setHardwareMappingHint(EHM_STATIC);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();

	SplitMeshResult result;
	result.middle = mesh;
	return result;
}
