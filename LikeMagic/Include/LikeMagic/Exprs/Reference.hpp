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

namespace LikeMagic { namespace Exprs {

using namespace LikeMagic::Utility;

template <typename T>
class Reference : public Expression<T&>
{
private:

    T& value;

    // This allows the reference expression to bump up the refcount
    // on the storage location, if that is being tracked.  Otherwise this is null.
    boost::intrusive_ptr<Expression<T&>> storage_location;

    Reference(T& value_, boost::intrusive_ptr<Expression<T&>> storage_location_) : value(value_), storage_location(storage_location_)
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

    static boost::intrusive_ptr<Expression<T&>> create(T& value_, boost::intrusive_ptr<Expression<T&>> storage_location_=0)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Reference(value_, storage_location_);
        return result;
    }

    virtual bool is_terminal() const { return false; }
    virtual bool disable_script_conv() const { return true; }

    virtual std::string description() const
    {
        return std::string("Reference<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<typename boost::remove_pointer<typename boost::remove_reference<T>::type>::type>());
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual bool disable_to_script_conv() const { return true; }
};


}}
