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

namespace LikeMagic { namespace Reflection {

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::AbstractTypeSystem;

class Mirror : public IMarkable
{
public:
    virtual ~Mirror() = 0;
    virtual void dispose() const = 0;

    // Perform / call
    virtual ExprPtr call(std::string method_name, ArgList args) = 0;
    virtual TypeInfoList get_arg_types(std::string method_name, int num_args) const = 0;
    virtual bool has_method(std::string method_name, int num_args) const = 0;
    virtual void suggest_method(std::string method_name, int num_args) const = 0;

    virtual bool disable_to_script_conv() const = 0;
    virtual bool is_terminal() const = 0;

    virtual std::string describe() const = 0;
};

}}
