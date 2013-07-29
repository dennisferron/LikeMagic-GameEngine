// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <string>
#include <stdexcept>
#include <typeinfo>
#include <map>
#include <vector>

#include "boost/intrusive_ptr.hpp"
#include "boost/unordered_map.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/SFMO/AbstractExpression.hpp"
#include "LikeMagic/ITypeSystemObserver.hpp"
#include "LikeMagic/NamespacePath.hpp"

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace SFMO {
    class AbstractCppObjProxy;
    class AbstractExpression;
}}

namespace LikeMagic { namespace CallTargets {
    class AbstractCallTargetSelector;
}}

namespace LikeMagic { namespace Marshaling {

using LikeMagic::SFMO::AbstractCppObjProxy;
using LikeMagic::SFMO::AbstractExpression;
using LikeMagic::SFMO::ExprPtr;
using LikeMagic::SFMO::ArgList;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::NamespacePath;
using LikeMagic::CallTargets::AbstractCallTargetSelector;

class AbstractClass
{
public:
    virtual ~AbstractClass();
    virtual AbstractCppObjProxy* create_class_proxy() const = 0;
    virtual std::string get_class_name() const = 0;
    virtual std::vector<std::string> const& get_method_names() const = 0;
    virtual TypeInfoList get_arg_types(std::string method_name, int num_args) const = 0;
    virtual ExprPtr call(ExprPtr target, std::string method_name,
                              ArgList args) const = 0;
    virtual bool has_method(std::string method_name, int num_args) const = 0;
    virtual AbstractCallTargetSelector* get_method(std::string method_name, int num_args) const = 0;
    virtual AbstractCallTargetSelector* try_get_method(
           std::string method_name, int num_args, bool in_base_class=false) const = 0;
    virtual void suggest_method(std::string method_name, int num_args) const = 0;
    virtual std::vector<AbstractCallTargetSelector*> get_methods() const = 0;
    virtual NamespacePath const get_namespace() const = 0;

    // support inheritance
    virtual void add_base_abstr(AbstractClass const* base) = 0;
    virtual std::vector<std::string> get_base_names() const = 0;
    virtual std::vector<AbstractClass const*> get_base_classes() const = 0;
    virtual bool has_base(AbstractClass const* base) const = 0;
    virtual TypeIndex get_type() const = 0;
    virtual bool class_is_copyable() const = 0;
    virtual size_t get_size() const = 0;
};

}}
