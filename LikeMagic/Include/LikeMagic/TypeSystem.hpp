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

namespace LM {

class AbstractExpression;
typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;
class CallTarget;
class TypeMirror;
class AbstractTypeConverter;
typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

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
    virtual TypeMirror& global_namespace() const;
};

extern TypeSystem* type_system;

template <typename To>
LM::Expression<To>* try_conv(ExprPtr from)
{
    return static_cast<LM::Expression<To>*>(
          type_system->try_conv(
            from, LM::BetterTypeInfo::create_index<To>()).get());
}

template <typename To>
bool has_conv(LM::ExprPtr from)
{
    return type_system->has_conv(from->get_type(),
         LM::BetterTypeInfo::create_index<To>());
}

}
