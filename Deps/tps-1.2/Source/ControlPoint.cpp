
#include "ControlPoint.hpp"

ControlPoint::ControlPoint(Vec const& pos_)
    : ref_count(0), pos(pos_)
{
}

typedef boost::intrusive_ptr<ControlPoint> ControlPointPtr;

void intrusive_ptr_add_ref(ControlPoint const* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(ControlPoint const* p)
{
    if (!--(p->ref_count))
        delete p;
}
