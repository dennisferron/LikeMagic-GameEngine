
/*
 *    Thin Plate Spline demo/example in C++
 *
 *    - a simple TPS editor, using the Boost uBlas library for large
 *        matrix operations and OpenGL + GLUT for 2D function visualization
 *        (curved plane) and user interface
 *
 *    Copyright (C) 2003,2005 by Jarno Elonen
 *
 *    TPSDemo is Free Software / Open Source with a very permissive
 *    license:
 *
 *    Permission to use, copy, modify, distribute and sell this software
 *    and its documentation for any purpose is hereby granted without fee,
 *    provided that the above copyright notice appear in all copies and
 *    that both that copyright notice and this permission notice appear
 *    in supporting documentation.    The authors make no representations
 *    about the suitability of this software for any purpose.
 *    It is provided "as is" without express or implied warranty.
 *
 *    TODO:
 *        - implement TPS approximation 3 as suggested in paper
 *            Gianluca Donato and Serge Belongie, 2002: "Approximation
 *            Methods for Thin Plate Spline Mappings and Principal Warps"
 */

#include "ThinPlateSpline/ThinPlateSpline.hpp"
#include "ThinPlateSpline/ludecomposition.h"

using namespace boost::numeric::ublas;
using namespace TPS;

static double tps_base_func(double r)
{
    if ( r == 0.0 )
        return 0.0;
    else
        return r*r * log(r);
}

ThinPlateSpline::ThinPlateSpline() :
    regularization(0.0),  bending_energy(0.0)
{
}

void ThinPlateSpline::clearControlPoints()
{
    control_points.clear();
}

void ThinPlateSpline::addControlPoint(ControlPointPtr p)
{
    control_points.push_back(p);
}

void ThinPlateSpline::removeControlPoint(ControlPointPtr p)
{
    control_points.erase(
        std::remove_if(control_points.begin(), control_points.end(),
            [=](ControlPointPtr el) { return p == el; }
        ),
        control_points.end()
    );
}

void ThinPlateSpline::calc_matrices()
{
    // You We need at least 3 points to define a plane
    if ( control_points.size() < 3 )
        return;

    unsigned p = control_points.size();

    if (mtx_orig_k.size1() != p)
    {
        // Allocate the matrix and vector
        mtx_l.resize(p+3, p+3);
        mtx_v.resize(p+3, 1);
        mtx_orig_k.resize(p, p);
    }


    // Fill K (p x p, upper left of L) and calculate
    // mean edge length from control points
    //
    // K is symmetrical so we really have to
    // calculate only about half of the coefficients.
    double a = 0.0;
    for ( unsigned i=0; i<p; ++i )
    {
        for ( unsigned j=i+1; j<p; ++j )
        {
            Vec pt_i = control_points[i]->pos;
            Vec pt_j = control_points[j]->pos;
            pt_i.y = pt_j.y = 0;
            double elen = (pt_i - pt_j).len();
            mtx_l(i,j) = mtx_l(j,i) =
                mtx_orig_k(i,j) = mtx_orig_k(j,i) =
                    tps_base_func(elen);
            a += elen * 2; // same for upper & lower tri
        }
    }
    a /= (double)(p*p);

    // Fill the rest of L
    for ( unsigned i=0; i<p; ++i )
    {
        // diagonal: reqularization parameters (lambda * a^2)
        mtx_l(i,i) = mtx_orig_k(i,i) =
            regularization * (a*a);

        // P (p x 3, upper right)
        mtx_l(i, p+0) = 1.0;
        mtx_l(i, p+1) = control_points[i]->pos.x;
        mtx_l(i, p+2) = control_points[i]->pos.z;

        // P transposed (3 x p, bottom left)
        mtx_l(p+0, i) = 1.0;
        mtx_l(p+1, i) = control_points[i]->pos.x;
        mtx_l(p+2, i) = control_points[i]->pos.z;
    }
    // O (3 x 3, lower right)
    for ( unsigned i=p; i<p+3; ++i )
        for ( unsigned j=p; j<p+3; ++j )
            mtx_l(i,j) = 0.0;

    // Fill the right hand vector V
    for ( unsigned i=0; i<p; ++i )
        mtx_v(i,0) = control_points[i]->pos.y;
    mtx_v(p+0, 0) = mtx_v(p+1, 0) = mtx_v(p+2, 0) = 0.0;

    // Solve the linear system "inplace"
    if (0 != LU_Solve(mtx_l, mtx_v))
    {
        std::cerr << "Error singular matrix!" << std::endl;
        //throw std::runtime_error( "Singular matrix! Aborting." );
    }
}


/*
 *    Calculate Thin Plate Spline (TPS) weights from
 *    control points and build a new height grid by
 *    interpolating with them.
 *
void ThinPlateSpline::calc_tps()
{
    // You We need at least 3 points to define a plane
    if ( control_points.size() < 3 )
        return;

    calc_matrices();

    // Interpolate grid heights
    for ( int x=-GRID_W/2; x<GRID_W/2; ++x )
    {
        for ( int z=-GRID_H/2; z<GRID_H/2; ++z )
        {
            grid[x+GRID_W/2][z+GRID_H/2] = height_at(x,z);
        }
    }

    calc_bending_energy();
}
*/

void ThinPlateSpline::calc_bending_energy()
{
    // You We need at least 3 points to define a plane
    if ( control_points.size() < 3 )
    {
        bending_energy = 0.0;
        return;
    }

    unsigned p = control_points.size();

    // Calc bending energy
    matrix<double> w( p, 1 );
    for ( int i=0; i<(int)p; ++i )
        w(i,0) = mtx_v(i,0);
    matrix<double> be = prod( prod<matrix<double> >( trans(w), mtx_orig_k ), w );
    bending_energy = be(0,0);
}

double ThinPlateSpline::height_at(double x, double z)
{
    // You We need at least 3 points to define a plane
    if ( control_points.size() < 3 )
        return 0.0f;

    unsigned p = control_points.size();

    if (mtx_orig_k.size1() != p)
    {
        throw std::logic_error("Error TPS matrices not sized right for number of control points.  Did you forget to call refresh() and/or calc_matrices()?");
    }

    double h = mtx_v(p+0, 0) + mtx_v(p+1, 0)*x + mtx_v(p+2, 0)*z;

    Vec pt_i, pt_cur(x,0,z);
    for ( unsigned i=0; i<p; ++i )
    {
        pt_i = control_points[i]->pos;
        pt_i.y = 0;
        h += mtx_v(i,0) * tps_base_func( ( pt_i - pt_cur ).len());
    }

    return h;
}



