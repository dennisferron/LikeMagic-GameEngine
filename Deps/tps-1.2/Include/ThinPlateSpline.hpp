
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

#include "ControlPoint.hpp"
#include "linalg3d.h"
#include "boost/numeric/ublas/matrix.hpp"
#include <vector>

class ThinPlateSpline
{
private:

    boost::numeric::ublas::matrix<double> mtx_l;
    boost::numeric::ublas::matrix<double> mtx_v;
    boost::numeric::ublas::matrix<double> mtx_orig_k;

    std::vector< ControlPointPtr > control_points;

public:
    double regularization;
    double bending_energy;

public:
    ThinPlateSpline();

    double height_at(double x, double z);
    void calc_tps();
    void addControlPoint(ControlPointPtr p);
    void removeControlPoint(ControlPointPtr p);
    void clearControlPoints();
    void calc_matrices();
    void calc_bending_energy();
};
