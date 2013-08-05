// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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
#include "LikeMagic/Exprs/AbstractExpression.hpp"
#include "LikeMagic/NamespacePath.hpp"

namespace LikeMagic {
    class AbstractTypeSystem;
}

namespace LikeMagic { namespace Exprs {
    class AbstractCppObjProxy;
    class AbstractExpression;
}}

namespace LikeMagic { namespace CallTargets {
    class AbstractMethod;
}}

namespace LikeMagic { namespace Marshaling {

using LikeMagic::Exprs::AbstractCppObjProxy;
using LikeMagic::Exprs::AbstractExpression;
using LikeMagic::Exprs::ExprPtr;
using LikeMagic::Exprs::ArgList;
using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::NamespacePath;
using LikeMagic::CallTargets::AbstractMethod;

class TypeMirror
{
private:
    struct Impl;
    boost::shared_ptr<Impl> impl;

    TypeMirror(TypeMirror const&) = delete;
    TypeMirror& operator =(TypeMirror const&) = delete;

public:
    TypeMirror();
    virtual ~TypeMirror();

    virtual std::string get_type_name() const;
    virtual TypeMirror const* get_namespace() const ;

    virtual AbstractMethod* get_method(std::string method_name, int num_args, bool in_base_class=false) const;
    virtual void add_method(std::string method_name, AbstractMethod* method);

    // support inheritance
    virtual void add_base(TypeMirror const* base);
    virtual bool has_base(TypeMirror const* base) const;
    virtual TypeIndex get_type() const;

    virtual size_t get_size() const;
};

void suggest_method(TypeMirror& type_, std::string method_name, int num_args) const;

}}
