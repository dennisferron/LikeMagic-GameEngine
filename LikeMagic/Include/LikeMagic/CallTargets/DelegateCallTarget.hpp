// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/IndexPack.hpp"
#include "LikeMagic/CallTargets/Delegate.hpp"

namespace LM {

template <bool is_const, typename R, typename... Args>
class DelegateCallTarget { static_assert(sizeof(R) && false, "Use the specializations."); };

template <typename... Args>
class DelegateCallTarget<false, void, Args...> : public CallTarget
{
public:
    typedef void (Delegate::*F)(Args...);

private:

    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that do not return a value
    template<int... Indices>
    void build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Delegate& target_obj = eval_as_nonconst_target(target, actual_type, target_ward);
        (target_obj.*func_ptr)(EvalAs<Args>::value(args[Indices], wards[Indices])...);
    }

public:

    DelegateCallTarget(F func_ptr_, TypeIndex class_type)
        : func_ptr(func_ptr_), actual_type(class_type) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        build_method_call(target, args, IPack());
        return nullptr;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename... Args>
class DelegateCallTarget<true, void, Args...> : public CallTarget
{
public:
    typedef void (Delegate::*F)(Args...) const;

private:

    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that do not return a value
    template<int... Indices>
    void build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Delegate const& target_obj = eval_as_const_target(target, actual_type, target_ward);
        (target_obj.*func_ptr)(EvalAs<Args>::value(args[Indices], wards[Indices])...);
    }

public:

    DelegateCallTarget(F func_ptr_, TypeIndex class_type)
        : func_ptr(func_ptr_), actual_type(class_type) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        build_method_call(target, args, IPack());
        return nullptr;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename... Args>
class DelegateCallTarget<false, R, Args...> : public CallTarget
{
public:
    typedef R (Delegate::*F)(Args...);

private:
    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that return a value
    template<int... Indices>
    ExprPtr build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Delegate& target_obj = eval_as_nonconst_target(target, actual_type, target_ward);
        return Term<R>::create((target_obj.*func_ptr)(
           EvalAs<Args>::value(args[Indices], wards[Indices])...));
    }

public:

    DelegateCallTarget(F func_ptr_, TypeIndex class_type)
        : func_ptr(func_ptr_), actual_type(class_type) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return build_method_call(target, args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename... Args>
class DelegateCallTarget<true, R, Args...> : public CallTarget
{
public:
    typedef R (Delegate::*F)(Args...) const;

private:
    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that return a value
    template<int... Indices>
    ExprPtr build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Delegate const& target_obj = eval_as_const_target(target, actual_type, target_ward);
        return Term<R>::create((target_obj.*func_ptr)(
            EvalAs<Args>::value(args[Indices], wards[Indices])...));
    }

public:

    DelegateCallTarget(F func_ptr_, TypeIndex class_type)
        : func_ptr(func_ptr_), actual_type(class_type) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return build_method_call(target, args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename... Args>
CallTarget* create_target(R (Delegate::*f)(Args...), TypeIndex class_type) {
    return new DelegateCallTarget<false, R, Args...>(f, class_type); }

template <typename R, typename... Args>
CallTarget* create_target(R (Delegate::*f)(Args...) const, TypeIndex class_type) {
    return new DelegateCallTarget<true, R, Args...>(f, class_type); }

}
