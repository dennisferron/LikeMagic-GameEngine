// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
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

#include <boost/intrusive_ptr.hpp>

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace SFMO {
    class AbstractCppObjProxy;
    class AbstractExpression;
}}

namespace LikeMagic { namespace Marshaling {

class AbstractCallTargetSelector;
using LikeMagic::SFMO::AbstractCppObjProxy;
using LikeMagic::SFMO::AbstractExpression;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::TypeInfoKey;
using LikeMagic::Utility::TypeInfoPtr;
using LikeMagic::Utility::TypeInfoList;

class AbstractClass
{
private:
    AbstractCppObjProxy* class_proxy;  // Allows you to call constructors without already having C++ object
    std::map<std::string, AbstractClass const*> bases;
    std::string class_name;
    std::map<std::string, std::map<int, AbstractCallTargetSelector*>> methods;

    // Although a list of method names can be derived from the std::map methods,
    // the make_io_method_table function requires a long-lived vector of strings in order
    // for the method names' c_str() buffers to still point to valid memory long enough
    // for the Io code to make local copies of the method names.
    std::vector<std::string> method_names;

    void suggest_method(std::string method_name, int num_args) const;

    // Don't allow the class to be accidently copied.
    AbstractClass(AbstractClass const&) = delete;
    AbstractClass& operator =(AbstractClass const&) = delete;

protected:
    AbstractTypeSystem& type_system;

    void add_method(std::string method_name, AbstractCallTargetSelector* method);
    AbstractCallTargetSelector* get_method(std::string method_name, int num_args) const;
    AbstractCallTargetSelector* try_get_method(std::string method_name, int num_args) const;

    AbstractClass(std::string name_, AbstractTypeSystem& type_system_) :
        class_name(name_),
        type_system(type_system_)
    {
        //std::cout << "Registering class " << typeid(T).name() << " as " << name_ << std::endl;
    }

public:
    virtual ~AbstractClass() {}
    virtual AbstractCppObjProxy* create_class_proxy() const = 0;
    std::string get_class_name() const;
    std::vector<std::string> const& get_method_names() const;
    TypeInfoList get_arg_types(std::string method_name, int num_args) const;
    AbstractCppObjProxy* call(AbstractCppObjProxy* target, std::string method_name, std::vector<boost::intrusive_ptr<AbstractExpression>> args) const;
    bool has_method(std::string method_name, int num_args) const;

    // support inheritance
    void add_base_abstr(AbstractClass const* base);
    std::vector<std::string> get_base_names() const;
};

}}
