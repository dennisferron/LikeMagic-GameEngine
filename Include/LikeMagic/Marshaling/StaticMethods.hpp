// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractClass.hpp"
#include "MethodCallGenerator.hpp"
#include "LikeMagic/SFMO/ClassExpr.hpp"
#include "LikeMagic/Marshaling/DummyClass.hpp"
#include "NamespaceTypeInfo.hpp"

namespace LikeMagic { namespace Utility { struct StaticMethod; }}

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::StaticMethod;

class StaticMethods : public DummyClass<StaticMethods>
{
private:
    // No copying or assignment.
    StaticMethods(StaticMethods const&);
    StaticMethods& operator=(StaticMethods const&);

    friend class LikeMagic::RuntimeTypeSystem;
    StaticMethods(AbstractTypeSystem& type_system_, NamespacePtr namespace_);

public:

    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        auto calltarget = new MethodCallGenerator<StaticMethod, F>(f, type_system);
        add_method(method_name, calltarget);
    }
};


}}
