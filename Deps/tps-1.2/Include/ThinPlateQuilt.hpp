
#include "ThinPlateSpline.hpp"

class ThinPlateQuilt
{
private:
    int const numCols;
    int const numRows;

    std::vector<ThinPlateSpline> tiles;
    std::vector<ControlPointPtr> control_points;

    Vec min;
    Vec max;

    struct TileAt
    {
        ThinPlateSpline* plate;
        double weight;
    };

    ThinPlateSpline& getTile(int col, int row);
    ThinPlateSpline const& getTile(int col, int row) const;

    std::vector<TileAt> tilesAt(double x, double z);

public:
    ThinPlateQuilt(int numCols_, int numRows_, Vec min_, Vec max_);
    double heightAt(double x, double z);
    ControlPointPtr addControlPoint(Vec pos);
    ControlPointPtr getControlPoint(unsigned index) const;
    unsigned numControlPoints() const;
    void removeControlPoint(unsigned pos);
    double getRegularization() const;
    void addRegularization(double delta);
    double getBendingEnergy() const;
    void refresh();
    void clearControlPoints();
};
