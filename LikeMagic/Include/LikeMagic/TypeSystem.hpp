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
#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class Expr;
typedef boost::intrusive_ptr<Expr> ExprPtr;
class CallTarget;
class TypeMirror;
class AbstractTypeConverter;
typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

class TypeSystem
{
public:
    virtual ~TypeSystem() = 0;
    virtual TypeMirror* get_class(TypeIndex type) const = 0;
    virtual void add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_) = 0;
    virtual void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv) = 0;
    virtual void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv) = 0;
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const = 0;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const = 0;
    virtual TypeMirror& global_namespace() const = 0;
    virtual TypeMirror const* get_namespace(std::string full_name) const = 0;
    virtual bool has_type(TypeIndex type) const = 0;
};

LIKEMAGIC_API extern TypeSystem* type_system;
LIKEMAGIC_API TypeSystem* create_type_system();
//LIKEMAGIC_API void throw_argument_null(Expr* expr, int arg_num, std::string const& method_name);

template <typename T>
T& deref(T* ptr, Expr* expr)
{
    if (ptr == nullptr)
        throw std::logic_error(expr->description() + " is null");
    else
        return *ptr;
}

template <typename T> struct EvalAs // by value
{
    EvalAs() = delete;

    inline static T const& value(ExprPtr from, ExprPtr& ward)
    {
        ward = type_system->try_conv(from, LM::TypId<T>::restricted());
        T const* ptr = reinterpret_cast<T const*>(ward->get_value_ptr().as_const);
        return deref(ptr, from.get());
    }

    inline static bool has_conv(Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T>::restricted());
    }
};

template <typename T> struct EvalAs<T const*> // by const ptr
{
    EvalAs() = delete;

    inline static T const* value(ExprPtr from, ExprPtr& ward)
    {
        ward = type_system->try_conv(from, LM::TypId<T const*>::restricted());
        return reinterpret_cast<T const*>(ward->get_value_ptr().as_const);
    }

    inline static bool has_conv(LM::Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T const*>::restricted());
    }
};

template <typename T> struct EvalAs<T*> // by nonconst ptr
{
    EvalAs() = delete;

    inline static T* value(ExprPtr from, ExprPtr& ward)
    {
        ward = type_system->try_conv(from, LM::TypId<T*>::restricted());
        return reinterpret_cast<T*>(ward->get_value_ptr().as_nonconst);
    }

    inline static bool has_conv(LM::Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T*>::restricted());
    }
};

template <typename T> struct EvalAs<T const&> // by const ref
{
    EvalAs() = delete;

    inline static T const& value(ExprPtr from, ExprPtr& ward)
    {
        ward = type_system->try_conv(from, LM::TypId<T const&>::restricted());
        T const* ptr = reinterpret_cast<T const*>(ward->get_value_ptr().as_const);
        return deref(ptr, from.get());
    }

    inline static bool has_conv(Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T const&>::restricted());
    }
};

template <typename T> struct EvalAs<T&> // by nonconst ref
{
    EvalAs() = delete;

    inline static T& value(ExprPtr from, ExprPtr& ward)
    {
        ward = type_system->try_conv(from, LM::TypId<T&>::restricted());
        T* ptr = reinterpret_cast<T*>(ward->get_value_ptr().as_nonconst);
        return deref(ptr, from.get());
    }

    inline static bool has_conv(Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T&>::restricted());
    }
};

}
