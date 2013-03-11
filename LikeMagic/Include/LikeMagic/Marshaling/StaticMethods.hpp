// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Marshaling/AbstractClass.hpp"
#include "LikeMagic/Generators/GeneratorFactory.hpp"
#include "LikeMagic/SFMO/ClassExpr.hpp"
#include "LikeMagic/Marshaling/DummyClass.hpp"
#include "LikeMagic/Marshaling/NamespaceTypeInfo.hpp"

// We don't use this anymore, we use NamespaceTypeInfo instead.
//namespace LikeMagic { namespace Utility { struct StaticMethod; }}

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::StaticMethod;
using LikeMagic::Generators::GeneratorFactory;
using LikeMagic::Generators::MemberKind;

class StaticMethods : public DummyClass<StaticMethods>
{
private:
    TypeIndex const static_method_type;

    // No copying or assignment.
    StaticMethods(StaticMethods const&) = delete;
    StaticMethods& operator=(StaticMethods const&) = delete;

    friend class LikeMagic::RuntimeTypeSystem;
    StaticMethods(AbstractTypeSystem& type_system_, NamespacePath const namespace_);

public:

    template <typename R, typename... Args>
    void bind_method(std::string method_name, R (*f)(Args...))
    {
        auto calltarget = GeneratorFactory<MemberKind::static_method, R, StaticMethod, Args...>::create(static_method_type, static_method_type, f, type_system);
        add_method(method_name, calltarget);
    }

    virtual AbstractCppObjProxy* create_class_proxy() const;

};


}}
