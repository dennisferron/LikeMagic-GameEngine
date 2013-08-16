// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/intrusive_ptr.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Exprs/Expression.hpp"

namespace LikeMagic {

namespace Exprs {
    class AbstractExpression;
    typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;
}

namespace Mirrors {
    class CallTarget;
    class TypeMirror;
}

namespace TypeConv {
    class AbstractTypeConverter;
    typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;
}

using LikeMagic::TypeConv::p_conv_t;
using LikeMagic::Mirrors::CallTarget;
using LikeMagic::Mirrors::TypeMirror;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using LikeMagic::Exprs::AbstractExpression;
using LikeMagic::Exprs::ExprPtr;

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
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual TypeMirror* global_namespace() const;
};

extern TypeSystem* type_system;

template <typename To>
boost::intrusive_ptr<LikeMagic::Exprs::Expression<To>> try_conv(ExprPtr from)
{
    return static_cast<LikeMagic::Exprs::Expression<To>*>(
          type_system->try_conv(
            from, LikeMagic::Utility::BetterTypeInfo::create_index<To>()).get());
}

template <typename To>
bool has_conv(LikeMagic::Exprs::ExprPtr from)
{
    return type_system->has_conv(from->get_type(),
         LikeMagic::Utility::BetterTypeInfo::create_index<To>());
}

}
