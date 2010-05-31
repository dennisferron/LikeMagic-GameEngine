
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
    class AbstractFunctionoid;
}}

namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::AbstractTypeSystem;
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

class AbstractCppObjProxy : public IMarkable
{
private:
    // Used to detect when we get fed a bum "this" pointer.
    long magic_number;

protected:
    AbstractTypeSystem const& type_system;
    BetterTypeInfo type;
    AbstractCppObjProxy(AbstractTypeSystem const& type_system_, BetterTypeInfo type_) : magic_number(0xCAFEBABE), type_system(type_system_), type(type_) {}

public:

    virtual void dispose() const = 0;

    virtual ~AbstractCppObjProxy() { magic_number = 0xFFFFFFFF; }

    virtual boost::intrusive_ptr<AbstractExpression> get_expr() = 0;

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
    std::vector<BetterTypeInfo> get_arg_types(std::string method_name, int num_args) const;

    BetterTypeInfo get_type() const { return type; }
    AbstractTypeSystem const& get_type_system() const { return type_system; }

    // determines whether you have to use "eval" or "exec" at the end of the expression
    virtual bool is_lazy() const = 0;
    virtual AbstractCppObjProxy* lazy() = 0;

    virtual bool is_reference() const = 0;
    virtual bool is_terminal() const = 0;
    virtual bool is_number() const = 0;
    virtual bool is_bool() const = 0;
    virtual bool is_string() const = 0;
    virtual bool is_vector_of(const std::type_info&) const = 0;
    virtual double to_number() const = 0;
    virtual bool to_bool() const = 0;
    virtual std::string to_string() const = 0;
    virtual std::string describe() const = 0;
};

}}
