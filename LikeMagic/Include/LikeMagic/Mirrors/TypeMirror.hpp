// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/shared_ptr.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Exprs/AbstractExpression.hpp"

namespace LikeMagic {
    class TypeSystem;
}

namespace LikeMagic { namespace Exprs {
    class AbstractCppObjProxy;
    class AbstractExpression;
}}

namespace LikeMagic { namespace Mirrors {
    class CallTarget;
}}

namespace LikeMagic { namespace Mirrors {

using LikeMagic::Exprs::AbstractExpression;
using LikeMagic::Exprs::ExprPtr;
using LikeMagic::Exprs::ArgList;
using LikeMagic::TypeSystem;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::Mirrors::CallTarget;

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

    virtual std::string get_name() const;

    virtual CallTarget* get_method(std::string method_name, int num_args, bool in_base_class=false) const;
    virtual void add_method(std::string method_name, CallTarget* method);

    // support inheritance
    virtual void add_base(TypeMirror const* base);
    virtual bool has_base(TypeMirror const* base) const;

    virtual TypeIndex get_type() const;
    virtual TypeIndex get_const_type() const;
    virtual TypeIndex get_ref_type() const;

    virtual size_t get_size() const;
};

void suggest_method(TypeMirror& type_, std::string method_name, int num_args);

}}
