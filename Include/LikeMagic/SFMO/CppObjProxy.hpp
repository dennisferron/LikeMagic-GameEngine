// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "ExprProxy.hpp"
#include "Term.hpp"

#include "LikeMagic/Utility/IsContainer.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

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
class CppObjProxy
{
private:
    CppObjProxy()
    {
    }

    virtual ~CppObjProxy()
    {
    }

public:

    static AbstractCppObjProxy* create(boost::intrusive_ptr<Expression<T>> expr_, AbstractTypeSystem const& type_system)
        { return ExprProxy::create(expr_, type_system, BetterTypeInfo::create_index<T>()); }
};

}}
