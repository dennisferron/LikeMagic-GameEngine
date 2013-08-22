// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/NamespaceExpr.hpp"

using namespace LM;

NamespaceExpr::NamespaceExpr(TypeIndex type_, TypeIndex class_type_)
    : type(type_), class_type(class_type_)
{
}

ExprPtr NamespaceExpr::create(TypeIndex type, TypeIndex class_type)
{
    return new NamespaceExpr(type, class_type);
}

bool NamespaceExpr::is_terminal() const
{
    return true;
}

std::string NamespaceExpr::description() const
{
    return "namespace or class expression " + type.description();
}

bool NamespaceExpr::disable_to_script_conv() const
{
    return true;
}

void NamespaceExpr::mark() const
{
    // Do nothing
}

TypeIndex NamespaceExpr::get_type() const
{
    return type;
}

TypeIndex NamespaceExpr::get_class_type() const
{
    return class_type;
}

bool NamespaceExpr::is_null() const
{
    return false;
}
