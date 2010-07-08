// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include <iostream>


namespace LikeMagic { namespace SFMO {

template <typename T>
class Expression : public AbstractExpression
{
private:
    Expression(Expression<T> const& other);
protected:
    Expression()
    {
        //std::cout << "created expression with T=" << LikeMagic::Utility::TypeDescr<T>::text() << std::endl;
    }
public:
    virtual ~Expression() {}
    virtual T eval() = 0;
    virtual boost::intrusive_ptr<Expression<T>> clone() const = 0;
    typedef T ReturnType;
    virtual BetterTypeInfo get_type() const { return BetterTypeInfo::create<T>(); }
};

// Some operations (for instance, the equals comparison) will always compile if the type is a pointer.
template <typename T>
class Expression<T*> : public AbstractExpression
{
private:
    Expression(Expression<T*> const& other);
protected:
    Expression()
    {
        //std::cout << "created expression with T=" << LikeMagic::Utility::TypeDescr<T>::text() << std::endl;
    }
public:
    virtual ~Expression() {}
    virtual T* eval() = 0;
    virtual boost::intrusive_ptr<Expression<T*>> clone() const = 0;
    typedef T* ReturnType;
    virtual BetterTypeInfo get_type() const { return BetterTypeInfo::create<T*>(); }

    // Compares the expression contents to the other expression's contents.
    // It can't be const because it may cause an eval().
    // Important:  Use AbstractTypeSystem::try_conv to convert the other expression to this type.
    // The result of calling equals if ExprPtr other isn't really of a compatible
    // type to this expression is undefined.
    virtual bool equals(ExprPtr other)
    {
        // Have to use static cast because sometimes type conversion works by returning an expression of one
        // type and pretending it is of another type when it is known the conversion doesn't affect the expression.
        Expression<T*>* cast_expr = static_cast<Expression<T*>*>(other.get());
        return this->eval() == cast_expr->eval();
    }
};


}}
