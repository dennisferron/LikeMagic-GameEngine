// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/AbstractCppObjProxy.hpp"
#include "LikeMagic/Marshaling/StaticMethods.hpp"

namespace LikeMagic { namespace SFMO {

class NamespaceProxy : public AbstractCppObjProxy
{
private:
    LikeMagic::Marshaling::StaticMethods const* methods;

    // Note:  If someone were to refactor this class to be more general or use it as a model for making
    // another kind of derived proxy, you'd probably have this constructor accept AbstractClass* instead of StaticMethods*.
    NamespaceProxy(LikeMagic::Marshaling::StaticMethods const* methods_, AbstractTypeSystem const& type_system);

public:

    static AbstractCppObjProxy* create(LikeMagic::Marshaling::StaticMethods const* methods_, AbstractTypeSystem const& type_system);

    virtual void dispose() const;
    virtual boost::intrusive_ptr<AbstractExpression> get_expr();
    virtual AbstractCppObjProxy* eval();
    virtual void exec();
    virtual AbstractCppObjProxy* clone() const;
    virtual bool is_terminal() const;
    virtual std::string describe() const;
    virtual bool is_lazy() const;
    virtual bool disable_to_script_conv() const;
    virtual AbstractCppObjProxy* lazy();
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}}
