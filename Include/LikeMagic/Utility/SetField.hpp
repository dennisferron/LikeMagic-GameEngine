// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "FieldPtrTraits.hpp"

namespace LikeMagic { namespace Utility {

// TODO:  Need to trap const fields and either not generate set function
//          or throw an exception.  Const static/namespace level variables
//          can also be const.

template <typename ObjT>
struct SetField
{
    template <typename FieldPtr>
    static void set(ObjT const t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT>::R const&>> arg)
    {
        throw std::logic_error("There is no point in setting a field on temporary object!");
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT const t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT>::R const&>> arg)
    {
        throw std::logic_error("There is no point in setting a field on temporary object!");
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT>::R&
    get(ObjT t, FieldPtr f)
    {
        return t.*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT>::R&
    getAt(size_t pos, ObjT t, FieldPtr f)
    {
        return (t.*f)[pos];
    }

};

// Call by nonconst reference.
template <typename ObjT>
struct SetField<ObjT&>
{

    template <typename FieldPtr>
    static void set(ObjT& t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT&>::R const&>> arg)
    {
        t.*f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT& t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT&>::R const&>> arg)
    {
        (t.*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT&>::R&
    get(ObjT& t, FieldPtr f)
    {
        return t.*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT&>::R&
    getAt(size_t pos, ObjT& t, FieldPtr f)
    {
        return (t.*f)[pos];
    }

};

template <typename ObjT>
struct SetField<ObjT const&>
{

    template <typename FieldPtr>
    static void set(ObjT const& t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT const&>::R const&>> arg)
    {
        throw std::logic_error("Cannot set field: the object it belongs to is const.");
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT const& t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT const&>::R const&>> arg)
    {
        throw std::logic_error("Cannot set field: the object it belongs to is const.");
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT const&>::R&
    get(ObjT const& t, FieldPtr f)
    {
        return t.*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT const&>::R&
    getAt(size_t pos, ObjT const& t, FieldPtr f)
    {
        return (t.*f)[pos];
    }

};


// Call by nonconst pointer
template <typename ObjT>
struct SetField<ObjT*>
{
    template <typename FieldPtr>
    static void set(ObjT* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT*>::R const&>> arg)
    {
        t->*f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT*>::R const&>> arg)
    {
        (t->*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT*>::R&
    get(ObjT* t, FieldPtr f)
    {
        return t->*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT*>::R&
    getAt(size_t pos, ObjT* t, FieldPtr f)
    {
        return (t->*f)[pos];
    }

};


// Call by const pointer
template <typename ObjT>
struct SetField<ObjT const*>
{
    template <typename FieldPtr>
    static void set(ObjT const* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT const*>::R const&>> arg)
    {
        throw std::logic_error("Cannot set field: the object it belongs to is const.");
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT const* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, ObjT const*>::R const&>> arg)
    {
        throw std::logic_error("Cannot set field: the object it belongs to is const.");
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT const*>::R&
    get(ObjT const* t, FieldPtr f)
    {
        return t->*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, ObjT const*>::R&
    getAt(size_t pos, ObjT const* t, FieldPtr f)
    {
        return (t->*f)[pos];
    }

};


template <>
struct SetField<StaticField>
{

    template <typename FieldPtr>
    static void set(StaticField t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, StaticField>::R const&>> arg)
    {
        *f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, StaticField t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr, StaticField>::R const&>> arg)
    {
        (*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, StaticField>::R&
    get(StaticField t, FieldPtr f)
    {
        return *f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr, StaticField>::R&
    getAt(size_t pos, StaticField t, FieldPtr f)
    {
        return (*f)[pos];
    }

};

}}
