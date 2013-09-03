// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expr.hpp"

namespace LM {

class NamespaceExpr : public Expr
{
private:
    NamespaceExpr(TypeIndex type, TypeIndex class_type);
    TypeIndex type;
    TypeIndex class_type;

public:

    static ExprPtr create(TypeIndex type, TypeIndex class_type);

    virtual bool is_terminal() const;
    virtual std::string description() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}
