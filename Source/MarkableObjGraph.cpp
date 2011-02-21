
#include "LikeMagic/MarkableObjGraph.hpp"

#include <iostream>

namespace LikeMagic
{


void MarkableObjGraph::add_mark_obj(IMarkable const& obj) const
{
    children.insert(&obj);
}

void MarkableObjGraph::remove_mark_obj(IMarkable const& obj) const
{
    children.erase(&obj);
}

void MarkableObjGraph::add_mark_obj(MarkableObjGraph const& obj) const
{
    children.insert(&obj);
    obj.parents.insert(this);
}

void MarkableObjGraph::remove_mark_obj(MarkableObjGraph const& obj) const
{
    if (children.find(&obj) != children.end())
    {
        remove_mark_obj(static_cast<IMarkable const&>(obj));
        obj.parents.erase(this);
    }
}


}
