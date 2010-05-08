
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
    static void set(ObjT t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        t.*f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        (t.*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    get(ObjT t, FieldPtr f)
    {
        return t.*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    getAt(size_t pos, ObjT t, FieldPtr f)
    {
        return (t.*f)[pos];
    }

};

// Call by pointer
template <typename ObjT>
struct SetField<ObjT*>
{

    template <typename FieldPtr>
    static void set(ObjT* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        t->*f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, ObjT* t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        (t->*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    get(ObjT* t, FieldPtr f)
    {
        return t->*f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    getAt(size_t pos, ObjT* t, FieldPtr f)
    {
        return (t->*f)[pos];
    }

};

template <>
struct SetField<StaticField>
{

    template <typename FieldPtr>
    static void set(StaticField t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        *f = arg->eval();
    }

    template <typename FieldPtr>
    static void setAt(size_t pos, StaticField t, FieldPtr f, boost::intrusive_ptr<Expression<typename FieldPtrTraits<FieldPtr>::R>> arg)
    {
        (*f)[pos] = arg->eval();
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    get(StaticField t, FieldPtr f)
    {
        return *f;
    }

    template <typename FieldPtr>
    static typename FieldPtrTraits<FieldPtr>::R
    getAt(size_t pos, StaticField t, FieldPtr f)
    {
        return (*f)[pos];
    }

};

}}
