// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/IndexPack.hpp"

namespace LM {

template <typename... Args>
class StaticMethodCallTarget_void : public CallTarget
{
public:
    typedef void (*F)(Args...);

private:

    F func_ptr;

    template<int... Indices>
    void build_method_call(ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        (*func_ptr)(EvalAs<Args>::value(args[Indices], wards[Indices])...);
    }

public:

    StaticMethodCallTarget_void(F func_ptr_) : func_ptr(func_ptr_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        build_method_call(args, IPack());
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }
};

template <typename R, typename... Args>
class StaticMethodCallTarget_R : public CallTarget
{
public:
    typedef R (*F)(Args...);

private:

    F func_ptr;

    // Handle functions that return a value
    template<int... Indices>
    ExprPtr build_method_call(ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        return Term<R>::create((*func_ptr)(
               EvalAs<Args>::value(args[Indices], wards[Indices])...));
    }

public:

    StaticMethodCallTarget_R(F func_ptr_) : func_ptr(func_ptr_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return build_method_call(args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }
};

}
