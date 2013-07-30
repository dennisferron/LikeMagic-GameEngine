// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/SFMO/Expression.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <vector>

#include <typeinfo>

// forward declarations
namespace LikeMagic { namespace Marshaling {
    class AbstractMethodset;
}}
namespace LikeMagic { namespace CallTargets {
    class AbstractCallTargetSelector;
}}

namespace LikeMagic { namespace Reflection {

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Marshaling::AbstractMethodset;
using LikeMagic::CallTargets::AbstractCallTargetSelector;

class Mirror : public IMarkable
{
public:

    virtual ~Mirror() = 0;
    virtual void dispose() const = 0;
    virtual AbstractTypeSystem const& get_type_system() = 0;

    virtual ExprPtr get_expr() = 0;

    // Perform / call
    virtual ExprPtr call(std::string method_name, ArgList args) = 0;
    virtual TypeInfoList get_arg_types(std::string method_name, int num_args) const = 0;
    virtual bool has_method(std::string method_name, int num_args) const = 0;
    virtual void suggest_method(std::string method_name, int num_args) const = 0;

    // Class information
    virtual AbstractClass const* get_class() const = 0;
    virtual std::string get_class_name() const = 0;
    virtual std::string get_base_names() const = 0;
    virtual TypeIndex get_type() const = 0;

    virtual bool disable_to_script_conv() const = 0;
    virtual bool is_terminal() const = 0;

    virtual std::string describe() const = 0;
};

}}
