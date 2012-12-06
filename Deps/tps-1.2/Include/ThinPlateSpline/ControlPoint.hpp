
#pragma once

#include "ThinPlateSpline/linalg3d.h"

#include "boost/intrusive_ptr.hpp"

namespace TPS {

class ControlPoint;
void intrusive_ptr_add_ref(ControlPoint const* p);
void intrusive_ptr_release(ControlPoint const* p);

class ControlPoint
{
private:
    friend void intrusive_ptr_add_ref(ControlPoint const* p);
    friend void intrusive_ptr_release(ControlPoint const* p);

    mutable int ref_count;

public:
    ControlPoint(Vec const& pos_);

    Vec pos;
};

typedef boost::intrusive_ptr<ControlPoint> ControlPointPtr;

}
