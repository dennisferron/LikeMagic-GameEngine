// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Term.hpp"

#include <iostream>

namespace LM {



template <typename T>
class Reference : public Expr
{
private:

    // This allows the reference expression to bump up the refcount
    // on the storage location, if that is being tracked.  Otherwise this is null.
    ExprPtr storage_location;

    Reference(T* value_, ExprPtr storage_location_) : Expr(value_), storage_location(storage_location_)
    {
    }

    static void mark(IMarkable const* obj)
    {
        obj->mark();
    }

    static void mark(IMarkable const& obj)
    {
        obj.mark();
    }

    template <typename MarkType>
    typename boost::enable_if<boost::is_base_of<IMarkable, MarkType>
        >::type mark_if_possible(TypePack<MarkType>) const
    {
        mark(value);
    }

    template <typename MarkType>
    typename boost::disable_if<boost::is_base_of<IMarkable, MarkType>
        >::type mark_if_possible(TypePack<MarkType>) const
    {
    }

public:

    static ExprPtr create(T* value_, ExprPtr storage_location_=0)
    {
        ExprPtr result = new Reference(value_, storage_location_);
        return result;
    }

    virtual bool is_terminal() const { return true; }

    virtual std::string description() const
    {
        return std::string("Reference<" + Expr::description() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<typename boost::remove_pointer<typename boost::remove_reference<T>::type>::type>());
    }
};


}
