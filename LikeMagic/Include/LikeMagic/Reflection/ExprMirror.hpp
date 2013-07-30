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

namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Marshaling::AbstractMethodset;
using LikeMagic::CallTargets::AbstractCallTargetSelector;

class AbstractCppObjProxy : public IMarkable
{
private:
    // Used to detect when we get fed a bum "this" pointer.
    long magic_number;

protected:
    AbstractTypeSystem const& type_system;
    AbstractClass const* class_;
    AbstractCppObjProxy(AbstractTypeSystem const& type_system_, AbstractClass const* class__) : magic_number(0xCAFEBABE), type_system(type_system_), class_(class__) {}

public:

    virtual void dispose() const = 0;

    virtual ~AbstractCppObjProxy() { magic_number = 0xEEEEEEEE; }

    virtual ExprPtr get_expr() = 0;

    void check_magic();

    template <typename To>
    boost::intrusive_ptr<Expression<To>> try_conv() { return type_system.try_conv<To>(get_expr()); }

    virtual std::string get_class_name() const;
    virtual AbstractCppObjProxy* call(std::string method_name, ArgList args);
    virtual TypeInfoList get_arg_types(std::string method_name, int num_args) const;
    virtual AbstractClass const* get_class() const;
    virtual bool has_method(std::string method_name, int num_args) const;
    virtual void suggest_method(std::string method_name, int num_args) const;

    virtual std::string get_base_names() const;

    virtual TypeIndex get_type() const = 0;
    AbstractTypeSystem const& get_type_system() const { return type_system; }

    virtual bool disable_to_script_conv() const = 0;
    virtual bool is_terminal() const = 0;
    virtual std::string describe() const = 0;
};

}}
