// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Term.hpp"

#include <iostream>

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

template <typename T>
class Reference : public Expression<T&>
{
private:

    T& value;

    Reference(T& value_) : value(value_)
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

    static boost::intrusive_ptr<Expression<T&>> create(T& value_)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Reference(value_);
        return result;
    }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return false; }
    virtual bool disable_script_conv() const { return true; }

    virtual std::string description() const
    {
        return std::string("Reference<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        typedef typename StripModifiers<T>::strip::type MarkType;
        mark_if_possible(TypePack<MarkType>());
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual boost::intrusive_ptr<Expression<T&>> clone() const { return new Reference<T>(value); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }

    virtual bool disable_to_script_conv() const { return true; }
};


}}
