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





template <typename... Args>
class DelegateCallTarget_void_nonconst : public CallTarget
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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate& target_obj = try_conv<Delegate&>(target_check)->eval();
        (target_obj.*func_ptr)(try_conv<Args>(args[Indices])->eval()...);
    }

public:

    DelegateCallTarget_void_nonconst(F func_ptr_, TypeIndex actual_type_)
        : func_ptr(func_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        if (args.size() != sizeof...(Args))
            throw std::logic_error("Wrong number of arguments.");

        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        build_method_call(target, args, IPack());
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }
};

template <typename... Args>
class DelegateCallTarget_void_const : public CallTarget
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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate const& target_obj = try_conv<Delegate const&>(target_check)->eval();
        (target_obj.*func_ptr)(try_conv<Args>(args[Indices])->eval()...);
    }

public:

    DelegateCallTarget_void_const(F func_ptr_, TypeIndex actual_type_)
        : func_ptr(func_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        if (args.size() != sizeof...(Args))
            throw std::logic_error("Wrong number of arguments.");

        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        build_method_call(target, args, IPack());
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }
};

template <typename R, typename... Args>
class DelegateCallTarget_R_nonconst : public CallTarget
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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate& target_obj = try_conv<Delegate&>(target_check)->eval();
        return Term<R>::create((target_obj.*func_ptr)(try_conv<Args>(args[Indices])->eval()...));
    }

public:

    DelegateCallTarget_R_nonconst(F func_ptr_, TypeIndex actual_type_)
        : func_ptr(func_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        if (args.size() != sizeof...(Args))
            throw std::logic_error("Wrong number of arguments.");

        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return build_method_call(target, args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }
};

template <typename R, typename... Args>
class DelegateCallTarget_R_const : public CallTarget
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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate const& target_obj = try_conv<Delegate const&>(target_check)->eval();
        return Term<R>::create((target_obj.*func_ptr)(try_conv<Args>(args[Indices])->eval()...));
    }

public:

    DelegateCallTarget_R_const(F func_ptr_, TypeIndex actual_type_)
        : func_ptr(func_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        if (args.size() != sizeof...(Args))
            throw std::logic_error("Wrong number of arguments.");

        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return build_method_call(target, args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }
};

}
