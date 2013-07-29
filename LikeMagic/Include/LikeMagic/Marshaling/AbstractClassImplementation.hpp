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
#include "LikeMagic/ITypeSystemObserver.hpp"
#include "LikeMagic/NamespacePath.hpp"

#include "LikeMagic/Marshaling/AbstractClass.hpp"

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
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::NamespacePath;
using LikeMagic::CallTargets::AbstractCallTargetSelector;

class AbstractClassImplementation : public AbstractClass
{
private:
    AbstractCppObjProxy* class_proxy;  // Allows you to call constructors without already having C++ object
    boost::unordered_map<std::string, AbstractClass const*> bases;
    std::string class_name;
    boost::unordered_map<std::string, std::map<int, AbstractCallTargetSelector*>> methods;

    // Although a list of method names can be derived from the std::map methods,
    // the make_io_method_table function requires a long-lived vector of strings in order
    // for the method names' c_str() buffers to still point to valid memory long enough
    // for the Io code to make local copies of the method names.
    std::vector<std::string> method_names;

    // Don't allow the class to be accidently copied.
    AbstractClassImplementation(AbstractClass const&) = delete;
    AbstractClassImplementation& operator =(AbstractClass const&) = delete;

protected:
    AbstractTypeSystem& type_system;
    NamespacePath const ns;

    void add_method(std::string method_name, AbstractCallTargetSelector* method);
    AbstractClassImplementation(std::string name_, AbstractTypeSystem& type_system_, NamespacePath const namespace_);

public:
    virtual ~AbstractClassImplementation();
    virtual AbstractCppObjProxy* create_class_proxy() const = 0;
    std::string get_class_name() const;
    std::vector<std::string> const& get_method_names() const;
    TypeInfoList get_arg_types(std::string method_name, int num_args) const;
    ExprPtr call(ExprPtr target, std::string method_name, ArgList args) const;
    bool has_method(std::string method_name, int num_args) const;
    AbstractCallTargetSelector* get_method(std::string method_name, int num_args) const;
    AbstractCallTargetSelector* try_get_method(std::string method_name, int num_args, bool in_base_class=false) const;
    void suggest_method(std::string method_name, int num_args) const;
    std::vector<AbstractCallTargetSelector*> get_methods() const;
    NamespacePath const get_namespace() const { return ns; }

    // support inheritance
    void add_base_abstr(AbstractClass const* base);
    std::vector<std::string> get_base_names() const;
    std::vector<AbstractClass const*> get_base_classes() const;
    virtual TypeIndex get_type() const = 0;
    virtual bool has_base(AbstractClass const* base) const;

    virtual bool class_is_copyable() const = 0;

    virtual size_t get_size() const { return 0; }
};

}}
