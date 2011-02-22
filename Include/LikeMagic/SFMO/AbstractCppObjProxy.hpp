// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/SFMO/Expression.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <vector>

#include <typeinfo>

// forward declarations
namespace LikeMagic { namespace Marshaling {
    class AbstractMethodset;
    class AbstractCallTargetSelector;
}}

namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Marshaling::AbstractMethodset;
using LikeMagic::Marshaling::AbstractCallTargetSelector;

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

class AbstractCppObjProxy : public IMarkable
{
private:
    // Used to detect when we get fed a bum "this" pointer.
    long magic_number;

protected:
    AbstractTypeSystem const& type_system;
    AbstractClass const* class_;
    AbstractCppObjProxy(AbstractTypeSystem const& type_system_, AbstractClass const* class__) : magic_number(0xCAFEBABE), type_system(type_system_), class_(class__) {}

public:

    virtual void dispose() const = 0;

    virtual ~AbstractCppObjProxy() { magic_number = 0xEEEEEEEE; }

    virtual ExprPtr get_expr() = 0;

    void check_magic();

    template <typename To>
    boost::intrusive_ptr<Expression<To>> try_conv() { return type_system.try_conv<To>(get_expr()); }

    // Evaluate expression and get a result.  If there are object sets, result is a vector of results.
    virtual AbstractCppObjProxy* eval() = 0;

    // Same as eval but discards the result.
    virtual void exec() = 0;

    // For iterating objsets, evals only the current element.  Same as eval if there are no elements.
    virtual AbstractCppObjProxy* elem() = 0;

    // Execs against set and discards results.
    virtual void iterate() = 0;

    // move loop forward by one.
    virtual void adv_loop() = 0;

    // Reset singlestepping
    virtual void begin_loop() = 0;

    // Done singlestepping?
    virtual bool loop_at_end() const = 0;

    // If you have a container in a SingleObjectSet, turns it into
    // a ContainerSet with the methods associated with the contained object.
    virtual AbstractCppObjProxy* each() const = 0;

    // Returns a new proxy containing a  copy of this expression and copy of the object set.
    virtual AbstractCppObjProxy* clone() const = 0;


    std::string get_class_name() const;
    AbstractCppObjProxy* call(std::string method_name, ArgList args);
    AbstractCppObjProxy* call(AbstractCallTargetSelector* method, ArgList args);
    TypeInfoList get_arg_types(std::string method_name, int num_args) const;
    AbstractClass const* get_class() const { return 0; }
    AbstractCallTargetSelector* get_method(std::string method_name, int num_args) const;

    std::string get_base_names() const;

    virtual TypeIndex get_type() const = 0;
    AbstractTypeSystem const& get_type_system() const { return type_system; }

    // determines whether you have to use "eval" or "exec" at the end of the expression
    virtual bool is_lazy() const = 0;
    virtual bool disable_to_script_conv() const = 0;
    virtual AbstractCppObjProxy* lazy() = 0;
    virtual bool is_terminal() const = 0;
    virtual std::string describe() const = 0;
};

}}
