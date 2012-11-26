#include "ThinPlateQuilt.hpp"

#define GRID_W 100
#define GRID_H 100
extern float grid[GRID_W][GRID_H];

ThinPlateQuilt instance( 3, 3, { -GRID_W/2,0,-GRID_H/2 }, { GRID_W/2-1,0,GRID_H/2-1 } );

ThinPlateQuilt::ThinPlateQuilt(int numCols_, int numRows_, Vec min_, Vec max_)
    : numCols(numCols_), numRows(numRows_), min(min_), max(max_)
{
    tiles.resize(numCols*numRows);
}

ThinPlateSpline& ThinPlateQuilt::getTile(int col, int row)
{
    return tiles.at(
        row*numCols + col
    );
}

ThinPlateSpline const& ThinPlateQuilt::getTile(int col, int row) const
{
    return tiles.at(
        row*numCols + col
    );
}

void ThinPlateQuilt::clearControlPoints()
{
    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            getTile(x,z).clearControlPoints();
    control_points.clear();
}

void ThinPlateQuilt::refresh()
{
    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            getTile(x,z).calc_matrices();

    // Interpolate grid heights
    for ( int x=-GRID_W/2; x<GRID_W/2; ++x )
    {
        for ( int z=-GRID_H/2; z<GRID_H/2; ++z )
        {
            grid[x+GRID_W/2][z+GRID_H/2] = heightAt(x,z);
        }
    }

    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            getTile(x,z).calc_bending_energy();
}

double ThinPlateQuilt::getRegularization() const
{
    double total = 0.0;

    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            total += getTile(x,z).regularization;

    return total / (numRows * numCols);
}

void ThinPlateQuilt::addRegularization(double delta)
{
    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            getTile(x,z).regularization += delta;
}

double ThinPlateQuilt::getBendingEnergy() const
{
    double total = 0.0;

    for (int x=0; x<numRows; ++x)
        for (int z=0; z<numCols; ++z)
            total += getTile(x,z).bending_energy;

    return total / (numRows * numCols);
}

void ThinPlateQuilt::removeControlPoint(unsigned pos)
{
    for (int x=0; x<numCols; ++x)
        for (int z=0; z<numRows; ++z)
            getTile(x,z).removeControlPoint(control_points.at(pos));
    control_points.erase(control_points.begin() + pos);
}

ControlPointPtr ThinPlateQuilt::addControlPoint(Vec pos)
{
    ControlPointPtr p = new ControlPoint(pos);
    control_points.push_back(p);

    std::vector<ThinPlateQuilt::TileAt> result;

    double x = pos.x;
    double z = pos.z;

    Vec quilt_size = (max - min);
    Vec tile_size = { quilt_size.x / numCols, 0, quilt_size.z / numRows };
    Vec halo_size = tile_size / 3;

    for (int i=0; i<numRows; ++i)
        for (int j=0; j<numCols; ++j)
        {
            Vec tile_min = min + Vec { i*tile_size.x, 0, j*tile_size.z };
            Vec tile_max = tile_min + tile_size;
            Vec halo_min = tile_min - halo_size;
            Vec halo_max = tile_max + halo_size;

            if (x >= tile_min.x && x <= tile_max.x && z >= tile_min.z && z <= tile_max.z)
            {
                getTile(i,j).addControlPoint(p);
            }
            else if (x >= halo_min.x && x <= halo_max.x && z >= halo_min.z && z <= halo_max.z)
            {
//                double x_from_halo_edge = (x <= tile_min.x)? x-halo_min.x : halo_max.x-x;
//                double z_from_halo_edge = (z <= tile_min.z)? z-halo_min.z : halo_max.z-z;
//                double x_weight = x_from_halo_edge / halo_size.x;
//                double z_weight = z_from_halo_edge / halo_size.z;
//                double best_weight = (x_weight>z_weight)? x_weight : z_weight;

                getTile(i,j).addControlPoint(p);
            }
            // Else the tile does not contribute.
        }

    return p;
}

ControlPointPtr ThinPlateQuilt::getControlPoint(unsigned index) const
{
    return control_points.at(index);
}

unsigned ThinPlateQuilt::numControlPoints() const
{
    return control_points.size();
}

std::vector<ThinPlateQuilt::TileAt> ThinPlateQuilt::tilesAt(double x, double z)
{
    std::vector<ThinPlateQuilt::TileAt> result;

    Vec quilt_size = (max - min);
    Vec tile_size = { quilt_size.x / numCols, 0, quilt_size.z / numRows };
    Vec halo_size = 1.3333 * tile_size;

    double dist_limit_sq = halo_size.x*halo_size.x + halo_size.z*halo_size.z;

    for (int i=0; i<numCols; ++i)
        for (int j=0; j<numRows; ++j)
        {
            Vec tile_center = min + Vec { i*tile_size.x, 0, j*tile_size.z } + (0.5*tile_size);

            double dist_sq = (tile_center.x-x)*(tile_center.x-x) + (tile_center.z-z)*(tile_center.z-z);

            if (dist_sq > dist_limit_sq)
                continue;

            double weight = 0.0;

            if (dist_sq > 0.001)
                weight = 1.0 / (dist_sq*dist_sq);
            else
                weight = 1000.0;

            result.push_back( { &getTile(i,j), weight } );
        }

    return result;
}

double ThinPlateQuilt::heightAt(double x, double z)
{
    double h = 0.0;
    double w = 0.0;
    std::vector<TileAt> list = tilesAt(x,z);

    for (auto tile : list)
    {
        h += tile.weight * tile.plate->height_at(x,z);
        w += tile.weight;
    }

    if (w == 0.0)
        return 0.0;
    else
        return h / w;
}
