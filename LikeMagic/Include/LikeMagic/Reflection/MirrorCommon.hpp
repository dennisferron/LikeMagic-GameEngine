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

class MirrorCommon : public IMarkable
{
protected:
    AbstractClass const* class_;
    AbstractCppObjProxy(AbstractTypeSystem const& type_system_, AbstractClass const* class__) : magic_number(0xCAFEBABE), type_system(type_system_), class_(class__) {}

public:

    // Perform / call
    virtual ExprPtr call(std::string method_name, ArgList args);
    virtual TypeInfoList get_arg_types(std::string method_name, int num_args) const ;
    virtual bool has_method(std::string method_name, int num_args) const;
    virtual void suggest_method(std::string method_name, int num_args) const;

    // Class information
    virtual AbstractClass const* get_class() const;
    virtual std::string get_class_name() const;
    virtual std::string get_base_names() const;
    virtual TypeIndex get_type() const = 0;

    virtual bool disable_to_script_conv() const = 0;
    virtual bool is_terminal() const = 0;

    virtual std::string describe() const = 0;
};

}}
