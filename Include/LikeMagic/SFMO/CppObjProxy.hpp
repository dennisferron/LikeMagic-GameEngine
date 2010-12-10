// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
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

    static void reset(std::set<AbstractObjectSet*> total_objsets)
    {
        for (auto iter=total_objsets.begin(); iter != total_objsets.end(); iter++)
            (**iter).reset();
    }

    static void advance(std::set<AbstractObjectSet*> total_objsets)
    {
        for (auto iter=total_objsets.begin(); iter != total_objsets.end(); iter++)
            (**iter).advance();
    }

    static bool at_end(std::set<AbstractObjectSet*> total_objsets)
    {
        bool at_end;
        bool all_yes = true;
        bool all_no = true;
        bool first = true;

        for (auto iter=total_objsets.begin(); iter != total_objsets.end(); iter++)
        {
            at_end = (**iter).at_end();

            if (!first)
            {
                first = false;

                if ( (all_yes && !at_end) || (all_no && at_end) )
                    throw std::runtime_error("AbstractCppObjProxy::at_end: not all sets ended together!");
            }
            all_yes &= at_end;
            all_no &= !at_end;
        }

        return all_yes;
    }

    static void iterate(boost::intrusive_ptr<Expression<T>> expr, std::set<AbstractObjectSet*> objsets)
    {
        for (reset(objsets); !at_end(objsets); advance(objsets))
            expr->eval();
    }

    template <typename T_>
    AbstractCppObjProxy* collect(boost::intrusive_ptr<Expression<T_>> expr, std::set<AbstractObjectSet*> objsets)
    {
        typedef typename std::remove_reference<T_>::type ElementType;

        auto result = Term<std::vector<ElementType>, true>::create(std::vector<ElementType>());

        for (reset(objsets); !at_end(objsets); advance(objsets))
            result->eval().push_back(type_system.try_conv<ElementType>(expr)->eval());

        std::cout << "Collected " << result->eval().size() << " results." << std::endl;

        return
                CppObjProxy<std::vector<ElementType>&, true>::create(result, type_system);
    }

    template <typename T_>
    static AbstractCppObjProxy* collect(boost::intrusive_ptr<Expression<T_&>> expr, std::set<AbstractObjectSet*> objsets)
    {
        throw std::logic_error("sorry can't collect results of function returning reference; stl vector does not support collections of references");
    }

    static AbstractCppObjProxy* collect(boost::intrusive_ptr<Expression<void>> expr, std::set<AbstractObjectSet*> objsets)
    {
        throw std::logic_error("can't collect result of set operation on function returning void");
    }

private:
    CppObjProxy(boost::intrusive_ptr<Expression<T>> expr_, AbstractTypeSystem const& type_system) :
        AbstractCppObjProxy(type_system, type_system.get_class(BetterTypeInfo::create_index<T>())), expr(expr_)
    {
    }

    virtual ~CppObjProxy()
    {
    }

    template <typename ObjT_>
    typename boost::enable_if<LikeMagic::Utility::IsContainer<ObjT_>,
        AbstractCppObjProxy*>::type
    each_impl() const
    {
        //std::cout << LikeMagic::Utility::TypeDescr<ObjT_>::text() << " is a container, running the 'each' method." << std::endl;

        typedef typename std::remove_reference<ObjT_>::type ContainerType;

        // The return value of "each" is not the bound type per se; the bound type a collection
        // and the return value of "each" is actually a proxy of Expression<T::reference>!
        auto term = Term<ObjT_, true>::create(expr->eval());
        return CppObjProxy<typename ContainerSet<ContainerType>::ReturnType, IsCopyable>::create(
                ContainerSet<ContainerType>::create(term), type_system);
    }

    template <typename ObjT_>
    typename boost::disable_if<LikeMagic::Utility::IsContainer<ObjT_>,
        AbstractCppObjProxy*>::type
    each_impl() const
    {
        std::cout << LikeMagic::Utility::TypeDescr<ObjT_>::text() << " is not a container; each has no meaning here." << std::endl;
        throw std::logic_error("each should not be callable on object not a container");
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
        auto objsets = expr->get_objsets();

        if (!objsets.empty())
            return collect(expr, expr->get_objsets());
        else
            return eval(expr);
    }

    virtual AbstractCppObjProxy* elem()
    {
        return eval(expr);
    }

    virtual void adv_loop()
    {
        advance(expr->get_objsets());
    }

    virtual void begin_loop()
    {
        reset(expr->get_objsets());
    }

    virtual bool loop_at_end() const
    {
        return at_end(expr->get_objsets());
    }

    virtual void exec()
    {
        expr->eval();
    }

    virtual void iterate()
    {
        iterate(expr, expr->get_objsets());
    }

    virtual AbstractCppObjProxy* each() const
    {
        return each_impl<T>();
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
