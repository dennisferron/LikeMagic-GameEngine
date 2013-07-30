// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "AbstractCppObjProxy.hpp"


namespace LikeMagic { namespace SFMO {

using LikeMagic::Marshaling::AbstractMethodset;

class ExprProxy : public AbstractCppObjProxy
{
protected:

    ExprPtr expr;

    ExprProxy(ExprPtr expr_, AbstractTypeSystem const& type_system, LikeMagic::Utility::TypeIndex class_id);

    virtual ~ExprProxy();

public:

    static AbstractCppObjProxy* create(ExprPtr expr_, AbstractTypeSystem const& type_system);
    static AbstractCppObjProxy* create(ExprPtr expr_, AbstractTypeSystem const& type_system, LikeMagic::Utility::TypeIndex class_id);

    virtual void dispose() const;
    virtual ExprPtr get_expr();
    virtual bool is_terminal() const;
    virtual std::string describe() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}}
