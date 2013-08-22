// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/IMarkable.hpp"

#include <set>

#include "boost/type_traits.hpp"
#include "boost/utility/enable_if.hpp"

namespace LM
{

// Utility class to aid in implementing scripted C++ objects that keep track of child
// objects so that the garbage collector won't accidently collect C++-owned objects.
// Note: Although it is OK for an object to have multiple parents, you must not make loops
// (two objects connected directly to each other).  If
// you do that then you'll get an infinite recursion when it tries to mark all the objects.
class MarkableObjGraph : public IMarkable
{
private:
    // Has to be mutable because sometimes we need to track objects created by const functions
    // so add_mark_obj and remove_mark_obj need to be const yet need to modify this set.
    // The rationale is that tracking which object points to which so that garbage collection will
    // work right isn't a logical change to the objects' behavior, but it happens to be easier
    // to implement by embedding this set of tracked objects.
    mutable std::set<IMarkable const*> children;

    // Markable objects keep track of their parents so that they can notify
    // them to stop marking them when they are deleted.
    mutable std::set<MarkableObjGraph const*> parents;

    // Used when the class is just testing to make sure the derived class is really implementing correctly;
    mutable bool just_testing;
    mutable bool has_marked;

    // Used to ensure derived classes comply with the class contract (they have to call the base mark() function).
    void test_compliance() const;

protected:

    bool is_just_testing() const;

public:

    MarkableObjGraph();
    virtual ~MarkableObjGraph();

    template <typename T>
    void add_mark_obj(T const* obj) const
    {
        auto pMarkable = dynamic_cast<IMarkable const*>(obj);
        if (pMarkable)
            children.insert(pMarkable);

        auto pGraph = dynamic_cast<MarkableObjGraph const*>(obj);
        if (pGraph)
            pGraph->parents.insert(this);
    }

    template <typename T>
    void remove_mark_obj(T const* obj) const
    {
        auto pMarkable = dynamic_cast<IMarkable const*>(obj);
        if (pMarkable)
            children.erase(pMarkable);

        auto pGraph = dynamic_cast<MarkableObjGraph const*>(obj);
        if (pGraph)
            pGraph->parents.erase(this);
    }

    void add_mark_obj(IMarkable const& obj) const;
    void remove_mark_obj(IMarkable const& obj) const;
    void add_mark_obj(MarkableObjGraph const& obj) const;
    void remove_mark_obj(MarkableObjGraph const& obj) const;

    std::size_t number_of_parents() const;
    std::size_t number_of_children() const;

public:

    virtual void mark() const;
};



template <typename T, typename F>
typename boost::disable_if<
    boost::is_base_of<IMarkable, F>
>::type
add_mark_obj(T const& obj, F const& field)
{
    static_assert(!boost::is_base_of<IMarkable, F>::value,
        "Default add_mark_obj should not be called on markable field");
}

template <typename T, typename F>
typename boost::enable_if_c<
    boost::is_base_of<IMarkable, F>::value
&&
    !boost::is_base_of<MarkableObjGraph, F>::value
>::type
add_mark_obj(T const& obj, F const& field)
{
    static_assert(boost::is_base_of<MarkableObjGraph, T>::value, "An object with a markable member must inherit from MarkableObjGraph.");
    obj.add_mark_obj(field);
}

template <typename T, typename F>
typename boost::enable_if<
    boost::is_base_of<MarkableObjGraph, F>
>::type
add_mark_obj(T const& obj, F const& field)
{
    static_assert(boost::is_base_of<MarkableObjGraph, T>::value, "An object with a markable member must inherit from MarkableObjGraph.");
    obj.add_mark_obj(field);
}


template <typename T, typename F>
typename boost::disable_if<
    boost::is_base_of<IMarkable, F>
>::type
remove_mark_obj(T const& obj, F const& field)
{
    static_assert(!boost::is_base_of<IMarkable, F>::value,
        "Default remove_mark_obj should not be called on markable field");
}

template <typename T, typename F>
typename boost::enable_if_c<
    boost::is_base_of<IMarkable, F>::value
&&
    !boost::is_base_of<MarkableObjGraph, F>::value
>::type
remove_mark_obj(T const& obj, F const& field)
{
    static_assert(boost::is_base_of<MarkableObjGraph, T>::value, "An object with a markable member must inherit from MarkableObjGraph.");
    obj.remove_mark_obj(field);
}

template <typename T, typename F>
typename boost::enable_if<
    boost::is_base_of<MarkableObjGraph, F>
>::type
remove_mark_obj(T const& obj, F const& field)
{
    static_assert(boost::is_base_of<MarkableObjGraph, T>::value, "An object with a markable member must inherit from MarkableObjGraph.");
    obj.remove_mark_obj(field);
}


}

