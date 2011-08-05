// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)



#include "LikeMagic/SFMO/NamespaceProxy.hpp"


#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Marshaling;
using namespace LikeMagic::SFMO;

NamespaceProxy::NamespaceProxy(AbstractClass const* methods_, AbstractTypeSystem const& type_system) :
    AbstractCppObjProxy(type_system, methods_), methods(methods_)
{
}


AbstractCppObjProxy* NamespaceProxy::create(AbstractClass const* methods_, AbstractTypeSystem const& type_system)
    { return new NamespaceProxy(methods_, type_system); }

void NamespaceProxy::dispose() const
{
    if (type_system.leak_memory())
        std::cout << "Not deleting " << describe() << std::endl;
    else
        delete this;
}

boost::intrusive_ptr<AbstractExpression> NamespaceProxy::get_expr()
{
    return ClassExpr<LikeMagic::Utility::StaticMethod>::create();
}

AbstractCppObjProxy* NamespaceProxy::eval()
{
    throw std::logic_error("Can't eval a namespace.");
}

void NamespaceProxy::exec()
{
    throw std::logic_error("Can't exec a namespace.");
}

AbstractCppObjProxy* NamespaceProxy::clone() const
{
    return create(methods, type_system);
}

bool NamespaceProxy::is_terminal() const
{
    return true;
}

std::string NamespaceProxy::describe() const
{
    return "namespace proxy: " + methods->get_type().describe();
}

bool NamespaceProxy::is_lazy() const
{
    return false;
}

bool NamespaceProxy::disable_to_script_conv() const
{
    return true;
}

AbstractCppObjProxy* NamespaceProxy::lazy()
{
    throw std::logic_error("Not sure what it means to create a lazy version of a Namespace.");
}

// mark Io objects held by this object so the garbage collector won't free them
void NamespaceProxy::mark() const
{
}

TypeIndex NamespaceProxy::get_type() const
{
    return methods->get_type();
}

}}
