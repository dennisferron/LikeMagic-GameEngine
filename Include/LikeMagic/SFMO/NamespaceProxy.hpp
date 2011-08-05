// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/AbstractCppObjProxy.hpp"
#include "LikeMagic/Marshaling/StaticMethods.hpp"

namespace LikeMagic { namespace SFMO {

// Mostly used for storing static methods that do not have a class object associated,
// but also can be used when a proxy is needed for another DummyClass such as for the ProxyMethods.
class NamespaceProxy : public AbstractCppObjProxy
{
private:
    LikeMagic::Marshaling::AbstractClass const* methods;

    NamespaceProxy(AbstractClass const* methods_, AbstractTypeSystem const& type_system);

public:

    static AbstractCppObjProxy* create(LikeMagic::Marshaling::AbstractClass const* methods_, AbstractTypeSystem const& type_system);

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
