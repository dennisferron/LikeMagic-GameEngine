// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractClass.hpp"
#include "ProxyMethodSelector.hpp"
#include "LikeMagic/SFMO/ClassExpr.hpp"
#include "LikeMagic/Marshaling/DummyClass.hpp"

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;

class ProxyMethods : public DummyClass<ProxyMethods>
{
private:
    // No copying or assignment.
    ProxyMethods(ProxyMethods const&);
    ProxyMethods& operator=(ProxyMethods const&);

    friend class LikeMagic::RuntimeTypeSystem;
    ProxyMethods(TypeIndex type_, std::string name_, AbstractTypeSystem& type_system_, NamespacePath const namespace_);

public:

    // Used to declare the default methods that operate on the proxy object.
    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        auto calltarget = new ProxyMethodSelector<F>(f, type_system);
        add_method(method_name, calltarget);
    }

    virtual AbstractCppObjProxy* create_class_proxy() const;

};


}}
