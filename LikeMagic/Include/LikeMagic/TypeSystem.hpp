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
#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"

#ifdef BUILDING_DLL_STD_BINDINGS
    #define BUILDING_DLL
#endif
#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class Expr;
typedef boost::intrusive_ptr<Expr> ExprPtr;
class CallTarget;
class TypeMirror;
class AbstractTypeConverter;
typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;

class TypeSystem;
DLL_PUBLIC TypeSystem* create_type_system();

class TypeSystem
{
private:
    TypeSystem();
    friend DLL_PUBLIC TypeSystem* create_type_system();

    struct Impl;
    boost::shared_ptr<Impl> impl;

    // Don't allow accidently making copies of this class
    TypeSystem(TypeSystem const&) = delete;
    TypeSystem & operator =(TypeSystem const&) = delete;

public:

    virtual ~TypeSystem();
    virtual TypeMirror* get_class(TypeIndex type) const;
    virtual void add_class(TypeIndex index, TypeMirror* class_ptr, TypeMirror& namespace_);
    virtual void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv);
    virtual ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    virtual bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;
    virtual TypeMirror& global_namespace() const;
};

DLL_PUBLIC extern TypeSystem* type_system;

template <typename T> struct EvalAs // by value
{
    EvalAs() = delete;

    inline static T const& value(ExprPtr from, ExprPtr& warden)
    {
        return *EvalAs<T const*>::value(from, warden);
    }

    inline static bool has_conv(Expr const* from)
    {
        return EvalAs<T const*>::has_conv(from);
    }
};

template <typename T> struct EvalAs<T const*> // by const ptr
{
    EvalAs() = delete;

    inline static T const* value(ExprPtr from, ExprPtr& warden)
    {
        warden = type_system->try_conv(from, LM::TypId<T const*>::get());
        return reinterpret_cast<T const*>(warden->get_value_ptr().as_const);
    }

    inline static bool has_conv(LM::Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T const*>::get());
    }
};

template <typename T> struct EvalAs<T*> // by nonconst ptr
{
    EvalAs() = delete;

    inline static T* value(ExprPtr from, ExprPtr& warden)
    {
        warden = type_system->try_conv(from, LM::TypId<T*>::get());
        return reinterpret_cast<T*>(warden->get_value_ptr().as_nonconst);
    }

    inline static bool has_conv(LM::Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T*>::get());
    }
};

template <typename T> struct EvalAs<T const&> // by const ref
{
    EvalAs() = delete;

    inline static T const& value(ExprPtr from, ExprPtr& warden)
    {
        return *EvalAs<T const*>::value(from, warden);
    }

    inline static bool has_conv(Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T const*>::get());
    }
};

template <typename T> struct EvalAs<T&> // by nonconst ref
{
    EvalAs() = delete;

    inline static T& value(ExprPtr from, ExprPtr& warden)
    {
        return *EvalAs<T*>::value(from, warden);
    }

    inline static bool has_conv(Expr const* from)
    {
        return type_system->has_conv(from->get_type(),
             LM::TypId<T*>::get());
    }
};

TypeMirror const* get_namespace(std::string full_name);

}
