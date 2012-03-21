// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"


#include <iostream>


namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Utility::TypeIndex;

class AbstractCppObjProxy;
class ExprProxy;

template <typename T, bool IsCopyable>
class Expression : public AbstractExpression
{
private:
    Expression(Expression<T> const& other);

protected:
    Expression() {}

    // Nonvoid expressions get a value returned.
    // This is a template so that eval(boost::intrusive_ptr<Expression<void>>) will be a better
    // match if the expression is in fact void type.
    template <typename T_>
    typename boost::enable_if_c<IsCopyable || boost::is_reference<T_>::value || boost::is_pointer<T_>::value,
        AbstractCppObjProxy*>::type
    eval_proxy(Expression<T_>* expr)
    {
        // Circular dependency Term <-> Expression
        //// TODO: add "BetterTypeInfo::create_index<T>()" to create() args.
        //return ExprProxy::create(
        //    Term<T, IsCopyable>::create(expr->eval()), type_system);
        return NULL;
    }

    template <typename T_>
    typename boost::enable_if_c<!IsCopyable && !boost::is_reference<T_>::value && !boost::is_pointer<T_>::value,
        AbstractCppObjProxy*>::type
    eval_proxy(Expression<T_>* expr)
    {
        throw std::logic_error("Cannot eval() expression '" + description() + ": " +
                    "the return type is by-value but the class is registered as not copyable."
        );
    }

    // eval void expression returns null.
    AbstractCppObjProxy* eval_proxy(Expression<void>* expr)
    {
        expr->eval();
        return 0;
    }


public:
    virtual ~Expression() {}
    virtual T eval() = 0;
    virtual boost::intrusive_ptr<Expression<T>> clone() const = 0;
    typedef T ReturnType;
    virtual TypeIndex get_type() const { return BetterTypeInfo::create_index<T>(); }

    virtual AbstractCppObjProxy* eval_proxy()
    {
        return eval_proxy(this);
    }
};

}}
