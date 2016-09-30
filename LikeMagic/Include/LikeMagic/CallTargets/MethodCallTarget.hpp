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
//#include "LikeMagic/Exceptions/Exception.hpp"

namespace LM {

template <typename T>
T& eval_as_nonconst_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward)
{
    TypeIndex target_type = get_index(
        from_type.get_info().as_ref_to_nonconst().as_restricted());
    ExprPtr target_check = type_system->try_conv(target, target_type);
    T& result = EvalAs<T&>::value(target_check, target_ward);

//    if (&result == nullptr)
//        throw LM::Exception("Target of call is null!");

    return result;
}

template <typename T>
T const& eval_as_const_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward)
{
    TypeIndex target_type = get_index(
        from_type.get_info().as_ref_to_const().as_restricted());
    ExprPtr target_check = type_system->try_conv(target, target_type);
    T const& result = EvalAs<T const&>::value(target_check, target_ward);

//    if (&result == nullptr)
//        throw LM::Exception("Target of call is null!");

    return result;
}


template <bool is_const, typename R, typename Obj, typename... Args>
class MethodCallTarget { static_assert(sizeof(R) && false, "Use the specializations."); };

template <typename Obj, typename... Args>
class MethodCallTarget<false, void, Obj, Args...> : public CallTarget
{
public:
    typedef void (Obj::*F)(Args...);

private:

    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that do not return a value
    template<int... Indices>
    void build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Obj& target_obj = eval_as_nonconst_target<Obj>(target, actual_type, target_ward);
        (target_obj.*func_ptr)(EvalAs<Args>::value(args[Indices], wards[Indices])...);
    }

public:

    MethodCallTarget(F func_ptr_, TypeIndex class_type)
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

    virtual TypeIndex get_return_type() const
    {
        return TypId<void>::liberal();
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename Obj, typename... Args>
class MethodCallTarget<true, void, Obj, Args...> : public CallTarget
{
public:
    typedef void (Obj::*F)(Args...) const;

private:

    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that do not return a value
    template<int... Indices>
    void build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Obj const& target_obj = eval_as_const_target<Obj>(target, actual_type, target_ward);
        (target_obj.*func_ptr)(EvalAs<Args>::value(args[Indices], wards[Indices])...);
    }

public:

    MethodCallTarget(F func_ptr_, TypeIndex class_type)
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

    virtual TypeIndex get_return_type() const
    {
        return TypId<void>::liberal();
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename Obj, typename... Args>
class MethodCallTarget<false, R, Obj, Args...> : public CallTarget
{
public:
    typedef R (Obj::*F)(Args...);

private:
    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that return a value
    template<int... Indices>
    ExprPtr build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Obj& target_obj = eval_as_nonconst_target<Obj>(target, actual_type, target_ward);
        return Term<R>::create((target_obj.*func_ptr)(
           EvalAs<Args>::value(args[Indices], wards[Indices])...));
    }

public:

    MethodCallTarget(F func_ptr_, TypeIndex class_type)
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

    virtual TypeIndex get_return_type() const
    {
        return TypId<R>::liberal();
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename Obj, typename... Args>
class MethodCallTarget<true, R, Obj, Args...> : public CallTarget
{
public:
    typedef R (Obj::*F)(Args...) const;

private:
    F const func_ptr;
    TypeIndex const actual_type;

    // Handle functions that return a value
    template<int... Indices>
    ExprPtr build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr target_ward;
        Obj const& target_obj = eval_as_const_target<Obj>(target, actual_type, target_ward);
        return Term<R>::create((target_obj.*func_ptr)(
            EvalAs<Args>::value(args[Indices], wards[Indices])...));
    }

public:

    MethodCallTarget(F func_ptr_, TypeIndex class_type)
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

    virtual TypeIndex get_return_type() const
    {
        return TypId<R>::liberal();
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

template <typename R, typename Obj, typename... Args>
CallTarget* create_target(R (Obj::*f)(Args...), TypeIndex class_type) {
    return new MethodCallTarget<false, Obj, R, Args...>(f, class_type); }

template <typename R, typename Obj, typename... Args>
CallTarget* create_target(R (Obj::*f)(Args...) const, TypeIndex class_type) {
    return new MethodCallTarget<true, R, Obj, Args...>(f, class_type); }

}
