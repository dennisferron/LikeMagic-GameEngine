// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expression.hpp"
#include "LikeMagic/Exprs/TermStoreAs.hpp"
#include "LikeMagic/Exprs/TermDeleter.hpp"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"
#include "LikeMagic/Utility/TypePack.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_base_of.hpp"

#include <iostream>

namespace LM {

template <typename T>
class Term : public Expression<T&>
{
private:

    typename TermStoreAs<T>::type value;

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

    Term() : value()
    {
    }

    template <typename... Args>
    Term(Args && ... args) : value(std::forward<Args>(args)...)
    {
    }

    template <typename... Args>
    Term(Args const& ... args) : value(args...)
    {
    }

public:

    ~Term()
    {
        if (((AbstractExpression*)this)->get_auto_delete_ptr())
            TermDeleter<T>::delete_if_possible(value);
    }

    static ExprPtr create()
    {
        return new Term();
    }

    template <typename... Args>
    static ExprPtr create(Args && ... args)
    {
        return new Term(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static ExprPtr create(Args const& ... args)
    {
        return new Term(args...);
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual bool is_terminal() const { return true; }

    virtual std::string description() const
    {
        return std::string("Term<" + AbstractExpression::description() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<
            typename boost::remove_reference<
                typename boost::remove_pointer<
                    T
                >::type
             >::type>());
    }
};

}
