// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/AbstractExpression.hpp"
#include "LikeMagic/Marshaling/StaticMethods.hpp"

namespace LikeMagic { namespace Exprs {

// Mostly used for storing static methods that do not have a class object associated,
// but also can be used when a proxy is needed for another DummyClass such as for the ProxyMethods.
class NamespaceExpr : public AbstractExpression
{
private:
    TypeMirror const* methods;

    NamespaceExpr(TypeMirror const* methods_);

public:

    static ExprPtr create(TypeMirror const* methods_);

    virtual bool is_terminal() const;
    virtual std::string description() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
    virtual TypeIndex get_class_type() const;
    virtual bool is_null() const;
};

}}
