// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/TypeInfoCache.hpp"

#include <string>

namespace LikeMagic
{

    namespace Marshaling {
        class AbstractClass;
    }

    namespace CallTargets {
        class AbstractCallTargetSelector;
    }

class ITypeSystemObserver
{
public:
    virtual void register_class(LikeMagic::Marshaling::AbstractClass const* class_)= 0;
    virtual void register_base(LikeMagic::Marshaling::AbstractClass const* class_, LikeMagic::Marshaling::AbstractClass const* base) = 0;
    virtual void register_method(LikeMagic::Marshaling::AbstractClass const* class_, std::string method_name, LikeMagic::CallTargets::AbstractCallTargetSelector* method) = 0;
};

}
