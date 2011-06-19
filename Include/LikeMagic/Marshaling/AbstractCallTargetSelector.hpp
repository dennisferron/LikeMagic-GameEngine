// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/DebugInfo.hpp"
#include "LikeMagic/SFMO/AbstractExpression.hpp"

namespace LikeMagic { namespace SFMO {
    class AbstractCppObjProxy;
}}

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace Marshaling {

class AbstractCallTargetSelector : public LikeMagic::DebugInfo
{
protected:
    LikeMagic::AbstractTypeSystem const& type_system;

public:
    AbstractCallTargetSelector(LikeMagic::AbstractTypeSystem const& type_system_);
    virtual ~AbstractCallTargetSelector();

    virtual LikeMagic::SFMO::AbstractCppObjProxy* call
        (
            LikeMagic::SFMO::AbstractCppObjProxy* target,
            LikeMagic::SFMO::ArgList args
        ) const = 0;

    virtual LikeMagic::Utility::TypeInfoList get_arg_types() const = 0;

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const;

    void set_expr_debug_name(LikeMagic::SFMO::ExprPtr arg) const;
};

}}
