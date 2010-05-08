
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
using LikeMagic::Marshaling::AbstractFunctionoid;

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

template <typename T>
class CppObjProxy : public AbstractCppObjProxy
{
private:
    boost::intrusive_ptr<Expression<T>> expr;

    template <typename T_>
    AbstractCppObjProxy* wrap_value(T_ value)
    {
        return CppObjProxy<T_&>::create(
            Term<T_>::create(value), type_system);
    }

    // Nonvoid expressions get a value returned.
    // This is a template so that run(boost::intrusive_ptr<Expression<void>>) will be a better
    // match if the expression is in fact void type.
    template <typename T_>
    AbstractCppObjProxy* eval(boost::intrusive_ptr<Expression<T_>> expr)
    {
        return wrap_value(expr->eval());
    }

    // Void expressions return null.  This matches over the template
    // version when T in fact equals void.
    AbstractCppObjProxy* eval(boost::intrusive_ptr<Expression<void>> expr)
    {
        expr->eval();
        return 0;
    }

    template <typename T_>
    typename boost::enable_if<std::is_convertible<T_, double>, double>::type
    to_number(boost::intrusive_ptr<Expression<T_>> expr) const { return expr->eval(); }

    template <typename T_>
    typename boost::disable_if<std::is_convertible<T_, double>, double>::type
    to_number(boost::intrusive_ptr<Expression<T_>> expr) const
    {
        throw std::logic_error("to_number called on SFMO object that is not a number!");
    }

    bool to_bool(boost::intrusive_ptr<Expression<bool>> expr) const { return expr->eval(); }
    bool to_bool(boost::intrusive_ptr<Expression<bool&>> expr) const { return expr->eval(); }
    bool to_bool(boost::intrusive_ptr<Expression<bool const>> expr) const { return expr->eval(); }
    bool to_bool(boost::intrusive_ptr<Expression<bool const&>> expr) const { return expr->eval(); }

    template <typename T_>
    bool to_bool(boost::intrusive_ptr<Expression<T_>> expr) const
    {
        throw std::logic_error("to_bool called on SFMO object that is not a bool!");
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

        auto result = Term<std::vector<ElementType>>::create(std::vector<ElementType>());

        for (reset(objsets); !at_end(objsets); advance(objsets))
            result->eval().push_back(type_system.try_conv<ElementType>(expr)->eval());

        std::cout << "Collected " << result->eval().size() << " results." << std::endl;

        return
                CppObjProxy<std::vector<ElementType>&>::create(result, type_system);
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
        AbstractCppObjProxy(type_system, BetterTypeInfo::create<T>()), expr(expr_)
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
        auto term = Term<ObjT_>::create(expr->eval());
        return CppObjProxy<typename ContainerSet<ContainerType>::ReturnType>::create(
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

    virtual bool is_reference() const
    {
        return std::is_reference<T>::value;
    }

    virtual bool is_terminal() const
    {
        return expr->is_terminal();
    }

    virtual bool is_number() const
    {
        return std::is_convertible<T, double>::value;
    }

    virtual bool is_bool() const
    {
        return boost::is_same<
                typename boost::remove_const<
                    typename boost::remove_reference<T>::type
                >::type, bool>::value;
    }

    virtual bool is_string() const
    {
        return IsString<T>::value;
    }

    virtual bool is_vector_of(const std::type_info& type) const
    {
        // TODO: fix this for other types of vectors
        if ( (type == typeid(int) && typeid(T) == typeid(std::vector<int>&))
        ||
            (type == typeid(unsigned int) && typeid(T) == typeid(std::vector<unsigned int>&))
        )
            return true;
        else
            return false;
    }

    virtual double to_number() const
    {
        return to_number(expr);
    }

    virtual bool to_bool() const
    {
        return to_bool(expr);
    }

    virtual std::string to_string() const
    {
        return type_system.try_conv<std::string>(expr)->eval();
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
    virtual void mark() const { expr->mark(); }

};

}}
