// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic {

namespace Exprs {
    class AbstractCppObjProxy;
}

namespace Marshaling {
    class CallTargetset;
    class TypeMirror;
}

using LikeMagic::Marshaling::CallTargetset;
using LikeMagic::Mirrors::TypeMirror;
using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;

class TypeSystem
{
private:

    struct Impl;
    boost::shared_ptr<Impl> impl;

    // Don't allow accidently making copies of this class
    TypeSystem(TypeSystem const&) = delete;
    TypeSystem & operator =(TypeSystem const&) = delete;

protected:

    TypeSystem();

public:

    virtual ~TypeSystem();
    virtual TypeMirror* get_class(TypeIndex type) const;
    virtual void add_class(TypeIndex index, TypeMirror* class_ptr);
    virtual void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual void add_ptr_conversions(TypeIndex from_type, bool auto_deref);
    virtual TypeMirror* global_namespace() const;
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual void print_conv_chain(TypeIndex from, TypeIndex to) const;
};

extern TypeSystem* type_system;

}
