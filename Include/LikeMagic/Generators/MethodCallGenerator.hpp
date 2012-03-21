// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/SFMO/MethodCall.hpp"
#include "LikeMagic/SFMO/StaticMethodCall.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

namespace LikeMagic { namespace Generators {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::CallTargets;

template <MemberKind K, typename R, typename T, typename... Args>
class MethodCallGenerator : public AbstractCallTargetSelector
{
private:

    // Decide whether to generate the call by-ref or by-const-ref.
    // Const functions convert the target to const ref, while
    // nonconst functions convert target to nonconst ref, which
    // fails by design for calling nonconst functions on value types.
    typedef typename CallAs<K, T>::type CallAs;

    typedef typename MemberPointer<K, R, T, Args...>::type F;
    F func_ptr;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        boost::intrusive_ptr<Expression<R>> method_call = MethodCall<R, CallAs, F, Args...>::create(
            type_system.try_conv<CallAs>(target), func_ptr, args_tuple);

        return method_call;
    }

public:

    //static bool const is_const_func = Traits::is_const;

    MethodCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       auto result_proxy = ExprProxy::create(build_method_call(proxy->get_expr(), args, IPack()), type_system);
       result_proxy->check_magic();
       return result_proxy;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }
};

// Static methods that do not pass the object as an argument.
template <typename R, typename... Args>
class MethodCallGenerator<MemberKind::static_method, R, StaticMethod, Args...> : public AbstractCallTargetSelector
{
private:

    typedef R (*F)(Args...);
    F func_ptr;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        boost::intrusive_ptr<Expression<R>> method_call = StaticMethodCall<R, F, Args...>::create(func_ptr, args_tuple);

        return method_call;
    }

public:

    //static bool const is_const_func = Traits::is_const;

    MethodCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       auto result_proxy = ExprProxy::create(build_method_call(proxy->get_expr(), args, IPack()), type_system);
       result_proxy->check_magic();
       return result_proxy;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }
};

// Static methods that do pass the object as first argument (e.g., nonmember operators).
template <typename R, typename T, typename... Args>
class MethodCallGenerator<MemberKind::nonmember_op, R, T, Args...> : public AbstractCallTargetSelector
{
private:

    typedef StaticMethod CallAs;

    typedef R (*F)(Args...);
    F func_ptr;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        // Target object is the first function argument.
        args.insert(args.begin(), target);

        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        boost::intrusive_ptr<Expression<R>> method_call =
            StaticMethodCall<R, F, Args...>::create(func_ptr, args_tuple);

        return method_call;
    }

public:

    //static bool const is_const_func = Traits::is_const;

    MethodCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       auto result_proxy = ExprProxy::create(build_method_call(proxy->get_expr(), args, IPack()), type_system);
       result_proxy->check_magic();
       return result_proxy;
    }

    virtual TypeInfoList get_arg_types() const
    {
        TypeInfoList args = make_arg_list(TypePack<Args...>());

        // Have to report that we take 1 less arg, because "this" object is the first arg.
        args.erase(args.begin());

        return args;
    }
};



}}
