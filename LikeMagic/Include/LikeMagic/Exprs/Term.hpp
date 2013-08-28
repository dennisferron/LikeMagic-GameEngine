// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/AbstractExpression.hpp"

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
class Expression : public AbstractExpression
{
public:
    virtual TypeIndex get_type() const { return TypId<T>::get(); }
    virtual T eval() = 0;
};

template <typename T>
class Expression<T*> : public AbstractExpression
{
protected:
    T* value;

public:

    Expression() : value(NULL) {}
    Expression(T* ptr) : value(ptr) {}

    virtual ~Expression()
    {
        if (((AbstractExpression*)this)->get_auto_delete_ptr())
            TermDeleter<T const>::delete_if_possible(value);
    }

    virtual T* eval() { return value; }
    virtual void mark() const { mark_if_possible(value); }
    virtual TypeIndex get_type() const { return TypId<T*>::get(); }
};

template <typename T>
class Expression<T&> : public AbstractExpression
{
public:
    virtual TypeIndex get_type() const { return TypId<T&>::get(); }
    virtual T& eval() = 0;
};


template <typename R>
struct Term
{
    static ExprPtr create(R func_result)
    {
        return new Expression<R*>(new R(func_result));
    }
};

// Reference case
template <typename R>
struct Term<R&>
{
    static ExprPtr create(R& func_result)
    {
        return new Expression<R*>(&func_result);
    }
};

// Pointer case
template <typename R>
struct Term<R*>
{
    static ExprPtr create(R* func_result)
    {
        return new Expression<R*>(func_result);
    }
};

// Reference to pointer case
template <typename R>
struct Term<R*&>
{
    static ExprPtr create(R*& func_result)
    {
        return new Expression<R**>(&func_result);
    }
};

}
