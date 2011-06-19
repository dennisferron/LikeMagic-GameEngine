// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "AbstractCppObjProxy.hpp"
#include "Term.hpp"
#include "LazyExpr.hpp"

#include "LikeMagic/Utility/IsContainer.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"
#include "ContainerSet.hpp"

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <set>

namespace LikeMagic { namespace SFMO {

using LikeMagic::Marshaling::AbstractMethodset;

/*

 Warning:  Do not try to refactor AbstractCppObjProxy and CppObjProxy<T>
 to unify them with AbstractExpression and Expression<T>.  Although
 conceptually these classes fulfill parallel roles, there are many methods
 in CppObjProxy which depend on classes derived from Expression<T>.
 Since the expression classes are all templates, this creates an unresolvable circular
 dependency between Expression.hpp and Term.hpp, ContainerSet.hpp, etc.

 Adding additional classes to break that dependency will put you right back
 where we are now, with the same methods implemented in them as are now
 in the Proxy classes!

*/


template <typename T, bool IsCopyable>
class CppObjProxy : public AbstractCppObjProxy
{
private:
    boost::intrusive_ptr<Expression<T>> expr;

    // Nonvoid expressions get a value returned.
    // This is a template so that run(boost::intrusive_ptr<Expression<void>>) will be a better
    // match if the expression is in fact void type.
    template <typename T_>
    typename boost::enable_if_c<IsCopyable || boost::is_reference<T_>::value || boost::is_pointer<T_>::value,
        AbstractCppObjProxy*>::type
    eval(boost::intrusive_ptr<Expression<T_>> expr)
    {
        return CppObjProxy<T&, IsCopyable>::create(
            Term<T, IsCopyable>::create(expr->eval()), type_system);
    }

    template <typename T_>
    typename boost::enable_if_c<!IsCopyable && !boost::is_reference<T_>::value && !boost::is_pointer<T_>::value,
        AbstractCppObjProxy*>::type
    eval(boost::intrusive_ptr<Expression<T_>> expr)
    {
        throw std::logic_error("Cannot eval() expression '" + describe() + ": " +
                    "the return type is by-value but the class is registered as not copyable."
        );
    }

    // Void expressions return null.
    AbstractCppObjProxy* eval(boost::intrusive_ptr<Expression<void>> expr)
    {
        expr->eval();
        return 0;
    }

private:
    CppObjProxy(boost::intrusive_ptr<Expression<T>> expr_, AbstractTypeSystem const& type_system) :
        AbstractCppObjProxy(type_system, type_system.get_class(BetterTypeInfo::create_index<T>())), expr(expr_)
    {
    }

    virtual ~CppObjProxy()
    {
    }

public:

    static AbstractCppObjProxy* create(boost::intrusive_ptr<Expression<T>> expr_, AbstractTypeSystem const& type_system)
        { return new CppObjProxy(expr_, type_system); }

    virtual void dispose() const
    {
        if (type_system.leak_memory())
            std::cout << "Not deleting " << describe() << std::endl;
        else
            delete this;
    }

    virtual boost::intrusive_ptr<AbstractExpression> get_expr() { return expr; }

    virtual AbstractCppObjProxy* eval()
    {
        //auto objsets = expr->get_objsets();

        //if (!objsets.empty())
        //    return collect(expr, expr->get_objsets());
        //else
            return eval(expr);
    }

    virtual void exec()
    {
        expr->eval();
    }

    virtual AbstractCppObjProxy* clone() const
    {
        return create(expr->clone(), type_system);
    }

    virtual bool is_terminal() const
    {
        return expr->is_terminal();
    }

    virtual std::string describe() const
    {
        //std::cout << "Description: " << expr->description() << (is_lazy()? " (lazy)" : "") << std::endl;
        return expr->description();
    }

    virtual bool is_lazy() const
    {
        return expr->is_lazy();
    }

    virtual bool disable_to_script_conv() const
    {
        return expr->disable_to_script_conv();
    }

    virtual AbstractCppObjProxy* lazy()
    {
        return create(LazyExpr<T>::create(expr), type_system);
    }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        expr->mark();
    }

    virtual TypeIndex get_type() const { return expr->get_type(); }
};

}}
