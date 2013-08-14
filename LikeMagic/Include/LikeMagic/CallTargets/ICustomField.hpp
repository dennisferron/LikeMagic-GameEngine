// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <stdexcept>

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename ObjType, typename FieldType_>
class ICustomField
{
public:
    virtual ~ICustomField() {}
    typedef FieldType_ FieldType;
    virtual FieldType get(ObjType const& obj) const = 0;

    // A wrapper for the reference form of accessing an object.
    FieldType get(ObjType const* obj) const
    {
        return get(*obj);
    }

    virtual void set(ObjType& obj, FieldType value) const = 0;

    // A wrapper for the reference form of accessing an object.
    void set(ObjType* obj, FieldType value) const
    {
        set(*obj, value);
    }

    // The reference form of set() won't match to obj passed by-value because you
    // can't bind a nonconst ref to a temp object, but adding an overload of set()
    // that takes things by-value creates an ambiguity when passing obj by ref.
    // Since template functions always bind with lower priority, we can use a template
    // to make the by-value case still compile without breaking the by-ref case.
    // get() is unaffected because it accepts obj by const-ref, which also works for by-value.
    template <typename T>
    void set(T obj, FieldType value) const
    {
        throw std::logic_error("Can't set fields on an object stored or passed by-value.");
    }

};

}}
