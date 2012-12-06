/*
 *  One file long C++ library of linear algebra primitives for
 *  simple 3D programs
 *
 *  Copyright (C) 2001-2003 by Jarno Elonen
 *
 *  Permission to use, copy, modify, distribute and sell this software
 *  and its documentation for any purpose is hereby granted without fee,
 *  provided that the above copyright notice appear in all copies and
 *  that both that copyright notice and this permission notice appear
 *  in supporting documentation.  The authors make no representations
 *  about the suitability of this software for any purpose.
 *  It is provided "as is" without express or implied warranty.
 */

#include "ThinPlateSpline/linalg3d.h"

namespace TPS {

// Creates a scale matrix
Mtx scale( const Vec &scale )
{
  Mtx m;
  m.data[ 0 + 0 ] = scale.x;
  m.data[ 4 + 1 ] = scale.y;
  m.data[ 8 + 2 ] = scale.z;
  return m;
}

// Creates a translation matrix
Mtx translate( const Vec &moveAmt )
{
  Mtx m;
  m.data[ 0 + 3 ] = moveAmt.x;
  m.data[ 4 + 3 ] = moveAmt.y;
  m.data[ 8 + 3 ] = moveAmt.z;
  return m;
}

// Creates an euler rotation matrix (by X-axis)
Mtx rotateX( float ang )
{
  float s = ( float ) sin( Deg2Rad( ang ) );
  float c = ( float ) cos( Deg2Rad( ang ) );

  Mtx m;
  m.data[ 4 + 1 ] = c; m.data[ 4 + 2 ] = -s;
  m.data[ 8 + 1 ] = s; m.data[ 8 + 2 ] = c;
  return m;
}

// Creates an euler rotation matrix (by Y-axis)
Mtx rotateY( float ang )
{
  float s = ( float ) sin( Deg2Rad( ang ) );
  float c = ( float ) cos( Deg2Rad( ang ) );

  Mtx m;
  m.data[ 0 + 0 ] = c; m.data[ 0 + 2 ] = s;
  m.data[ 8 + 0 ] = -s; m.data[ 8 + 2 ] = c;
  return m;
}

// Creates an euler rotation matrix (by Z-axis)
Mtx rotateZ( float ang )
{
  float s = ( float ) sin( Deg2Rad( ang ) );
  float c = ( float ) cos( Deg2Rad( ang ) );

  Mtx m;
  m.data[ 0 + 0 ] = c; m.data[ 0 + 1 ] = -s;
  m.data[ 4 + 0 ] = s; m.data[ 4 + 1 ] = c;
  return m;
}

// Creates an euler rotation matrix (pitch/head/roll (x/y/z))
Mtx rotate( float pitch, float head, float roll )
{
  float sp = ( float ) sin( Deg2Rad( pitch ) );
  float cp = ( float ) cos( Deg2Rad( pitch ) );
  float sh = ( float ) sin( Deg2Rad( head ) );
  float ch = ( float ) cos( Deg2Rad( head ) );
  float sr = ( float ) sin( Deg2Rad( roll ) );
  float cr = ( float ) cos( Deg2Rad( roll ) );

  Mtx m;
  m.data[ 0 + 0 ] = cr * ch - sr * sp * sh;
  m.data[ 0 + 1 ] = -sr * cp;
  m.data[ 0 + 2 ] = cr * sh + sr * sp * ch;

  m.data[ 4 + 0 ] = sr * ch + cr * sp * sh;
  m.data[ 4 + 1 ] = cr * cp;
  m.data[ 4 + 2 ] = sr * sh - cr * sp * ch;

  m.data[ 8 + 0 ] = -cp * sh;
  m.data[ 8 + 1 ] = sp;
  m.data[ 8 + 2 ] = cp * ch;
  return m;
}

// Creates an arbitraty rotation matrix
Mtx makeRotationMatrix( const Vec &dir, const Vec &up )
{
  Vec x = cross( up, dir ), y = cross( dir, x ), z = dir;
  Mtx m;
  m.data[ 0 ] = x.x; m.data[ 1 ] = x.y; m.data[ 2 ] = x.z;
  m.data[ 4 ] = y.x; m.data[ 5 ] = y.y; m.data[ 6 ] = y.z;
  m.data[ 8 ] = z.x; m.data[ 9 ] = z.y; m.data[ 10 ] = z.z;
  return m;
}

// Multiplies a matrix by another matrix
Mtx operator * ( const Mtx& a, const Mtx& b )
{
  Mtx ans;
  for ( int aRow = 0; aRow < 4; ++aRow )
    for ( int bCol = 0; bCol < 4; ++bCol )
    {
      int aIdx = aRow * 4;
      int bIdx = bCol;

      float val = 0;
      for ( int idx = 0; idx < 4; ++idx, ++aIdx, bIdx += 4 )
        val += a.data[ aIdx ] * b.data[ bIdx ];
      ans.data[ bCol + aRow * 4 ] = val;
    }
  return ans;
}

}
