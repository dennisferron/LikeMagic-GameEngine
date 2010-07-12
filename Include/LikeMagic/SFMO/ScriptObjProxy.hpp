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
using LikeMagic::Marshaling::AbstractFunctionoid;



class ScriptObjProxy : public AbstractCppObjProxy
{
private:
    ExprPtr expr;

private:
    ScriptObjProxy(ExprPtr expr_, AbstractTypeSystem const& type_system) :
        AbstractCppObjProxy(type_system, BetterTypeInfo()), expr(expr_)
    {
    }

public:

    static AbstractCppObjProxy* create(ExprPtr expr_, AbstractTypeSystem const& type_system)
        { return new ScriptObjProxy(expr_, type_system); }

    virtual void dispose() const
    {
        if (type_system.leak_memory())
            std::cout << "Not deleting " << describe() << std::endl;
        else
            delete this;
    }

    virtual ExprPtr get_expr() { return expr; }

    virtual AbstractCppObjProxy* eval()
    {
        throw std::logic_error("Can't directly eval() a ScriptObj proxy - it must be converted to a native script object.");
    }

    virtual AbstractCppObjProxy* elem()
    {
        return eval();
    }

    virtual void adv_loop()
    {
        throw std::logic_error("SFMO collection operations not defined for ScriptObj proxies.");
    }

    virtual void begin_loop()
    {
        throw std::logic_error("SFMO collection operations not defined for ScriptObj proxies.");
    }

    virtual bool loop_at_end() const
    {
        throw std::logic_error("SFMO collection operations not defined for ScriptObj proxies.");
    }

    virtual void exec()
    {
        eval();
    }

    virtual void iterate()
    {
        throw std::logic_error("SFMO collection operations not defined for ScriptObj proxies.");
    }

    virtual AbstractCppObjProxy* each() const
    {
        throw std::logic_error("SFMO collection operations not defined for ScriptObj proxies.");
    }

    virtual AbstractCppObjProxy* clone() const
    {
        throw std::logic_error("clone not implemented yet on ScriptObj proxies");
        //return create(expr->clone(), type_system);
    }

    virtual bool is_terminal() const
    {
        // Has to be terminal because we can't eval.
        return true;
    }

    virtual std::string describe() const
    {
        return expr->description();
    }

    virtual bool is_lazy() const
    {
        return expr->is_lazy();
    }

    virtual AbstractCppObjProxy* lazy()
    {
        throw std::logic_error("I'm not sure what the lazy keyword should mean for a ScriptObjProxy.");
    }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() { expr->mark(); }

    // Compares the proxied expression to the other expression.
    // It can't be const because it may cause an eval().
    virtual bool expr_equals(ExprPtr other)
    {
        try
        {
            ExprPtr conv_expr = type_system.try_conv(other, expr->get_type());
            return expr->eval_equals(conv_expr);
        }
        catch (std::logic_error le)
        {
            throw std::logic_error(std::string("Error doing type conversion on from expression for expr_equals() compare.  ") + le.what());
        }
    }

};

}}
