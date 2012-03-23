// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/SFMO/ExprProxy.hpp"
#include "LikeMagic/SFMO/Term.hpp"

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <set>

using namespace LikeMagic::SFMO;
using LikeMagic::Marshaling::AbstractMethodset;



// TODO:  Accept type index parameter for expression class
ExprProxy::ExprProxy(ExprPtr expr_, AbstractTypeSystem const& type_system, LikeMagic::Utility::TypeIndex class_id) :
    AbstractCppObjProxy(type_system, type_system.get_class(class_id)), expr(expr_)
{
}

ExprProxy::~ExprProxy()
{
}

AbstractCppObjProxy* ExprProxy::create(ExprPtr expr_, AbstractTypeSystem const& type_system)
{
    return new ExprProxy(expr_, type_system, expr_->get_class_type());
}

AbstractCppObjProxy* ExprProxy::create(ExprPtr expr_, AbstractTypeSystem const& type_system, LikeMagic::Utility::TypeIndex type_id)
{
    return new ExprProxy(expr_, type_system, type_id);
}

void ExprProxy::dispose() const
{
    if (type_system.leak_memory())
        std::cout << "Not deleting " << describe() << std::endl;
    else
        delete this;
}

boost::intrusive_ptr<AbstractExpression> ExprProxy::get_expr() { return expr; }

bool ExprProxy::is_terminal() const
{
    return expr->is_terminal();
}

std::string ExprProxy::describe() const
{
    return expr->description();
}

bool ExprProxy::disable_to_script_conv() const
{
    return expr->disable_to_script_conv();
}

void ExprProxy::mark() const
{
    expr->mark();
}

TypeIndex ExprProxy::get_type() const
{
    return expr->get_type();
}
