
#include "LikeMagic/MarkableObjGraph.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

namespace LikeMagic
{

MarkableObjGraph::MarkableObjGraph()
    : just_testing(false), has_marked(false)
{
}

void MarkableObjGraph::mark() const
{
    if (get_debug_name() == "DebugBreak")
        cout << "mark: DebugBreak" << endl;

    if (!is_just_testing())
        for (auto it=children.begin(); it!=children.end(); ++it)
            (*it)->mark();
    has_marked = true;
}

MarkableObjGraph::~MarkableObjGraph()
{
    for (auto it=parents.begin(); it!=parents.end(); ++it)
        (*it)->remove_mark_obj(this);
}

std::size_t MarkableObjGraph::number_of_parents() const
{
    return parents.size();
}

std::size_t MarkableObjGraph::number_of_children() const
{
    return children.size();
}


bool MarkableObjGraph::is_just_testing() const
{
    return just_testing;
}

void MarkableObjGraph::test_compliance() const
{
    just_testing = true;
    has_marked = false;
    mark();
    if (!has_marked)
        throw std::logic_error("A class derived from MarkableObjGraph is not working right.  You *MUST* call the base implementation MarkableObjGraph::mark() if you override the mark() function.");
    just_testing = false;
}

void MarkableObjGraph::add_mark_obj(IMarkable const& obj) const
{
    test_compliance();
    children.insert(&obj);
}

void MarkableObjGraph::remove_mark_obj(IMarkable const& obj) const
{
    children.erase(&obj);
}

void MarkableObjGraph::add_mark_obj(MarkableObjGraph const& obj) const
{
    test_compliance();
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
