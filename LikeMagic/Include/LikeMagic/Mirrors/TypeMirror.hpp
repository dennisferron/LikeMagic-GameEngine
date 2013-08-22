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

namespace LM {
    class TypeSystem;
}

namespace LM {
    class AbstractCppObjProxy;
    class AbstractExpression;
}

namespace LM {
    class CallTarget;
}

namespace LM {

using LM::AbstractExpression;
using LM::ExprPtr;
using LM::ArgList;
using LM::TypeSystem;
using LM::TypeIndex;
using LM::TypeInfoList;
using LM::CallTarget;

class TypeMirror
{
private:
    struct Impl;
    boost::shared_ptr<Impl> impl;

    TypeMirror(TypeMirror const&) = delete;
    TypeMirror& operator =(TypeMirror const&) = delete;

    friend void suggest_method(TypeMirror& type_, std::string method_name, int num_args);

public:
    TypeMirror(std::string class_name, size_t instance_size, TypeIndex class_type, TypeIndex ref_type, TypeIndex const_ref_type);
    virtual ~TypeMirror();

    virtual std::string get_class_name() const;

    virtual CallTarget* get_method(std::string method_name, int num_args, bool in_base_class=false) const;
    virtual void add_method(std::string method_name, CallTarget* method);

    // support inheritance
    virtual void add_base(TypeMirror const* base);
    virtual bool has_base(TypeMirror const* base) const;

    virtual TypeIndex get_class_type() const;
    virtual TypeIndex get_ref_type() const;
    virtual TypeIndex get_const_ref_type() const;

    virtual size_t get_instance_size() const;

    virtual void suggest_method(std::string method_name, int num_args) const;
};

}
