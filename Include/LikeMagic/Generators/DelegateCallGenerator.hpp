// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "../Utility/FuncPtrTraits.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/SFMO/DelegateMethodCall.hpp"
#include "LikeMagic/SFMO/StaticMethodCall.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

#include "boost/mpl/if.hpp"

namespace LikeMagic { namespace Generators {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <MemberKind K, typename R, typename... Args>
class DelegateCallGenerator : public AbstractCallTargetSelector
{
public:
    typedef R (AbstractDelegate::*F)(Args...);

private:

    F func_ptr;
    TypeIndex actual_type;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args,IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);
        auto target_check = type_system.try_conv(target, actual_type);

        boost::intrusive_ptr<Expression<R>> method_call = DelegateMethodCall<R, false, IPack, Args...>::create(
            type_system.try_conv<AbstractDelegate&>(target_check), func_ptr, args_tuple);

        return method_call;
    }

public:

    template <typename OtherF>
    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, OtherF func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(reinterpret_cast<F>(func_ptr_)), actual_type(ref_type_) {}

    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), actual_type(ref_type_) {}

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

template <typename R, typename... Args>
class DelegateCallGenerator<MemberKind::member_const, R, Args...> : public AbstractCallTargetSelector
{
public:
    typedef R (AbstractDelegate::*F)(Args...) const;

private:
    F func_ptr;
    TypeIndex actual_type;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);
        auto target_check = type_system.try_conv(target, actual_type);

        boost::intrusive_ptr<Expression<R>> method_call = DelegateMethodCall<R, true, IPack, Args...>::create(
            type_system.try_conv< AbstractDelegate const&>(target_check), func_ptr, args_tuple);

        return method_call;
    }

public:

    template <typename OtherF>
    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, OtherF func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(reinterpret_cast<F>(func_ptr_)), actual_type(const_ref_type_) {}

    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), actual_type(const_ref_type_) {}

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
template <typename R, typename... Args>
class DelegateCallGenerator<MemberKind::nonmember_op, R, Args...> : public AbstractCallTargetSelector
{
public:
    typedef R (*F)(Args...);

private:
    F func_ptr;
    TypeIndex ref_type;
    TypeIndex const_ref_type;

    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    template<int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, IndexPack<Indices...>) const
    {
        // Target object is the first function argument.
        auto target_check = type_system.try_conv(target, get_arg_types().at(0));
        args.insert(args.begin(), target_check);

        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        boost::intrusive_ptr<Expression<R>> method_call =
            StaticMethodCall<R, F, Args...>::create(func_ptr, args_tuple);

        return method_call;
    }

public:

    template <typename OtherF>
    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, OtherF func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(reinterpret_cast<F>(func_ptr_)), ref_type(ref_type_), const_ref_type(const_ref_type_) {}

    DelegateCallGenerator(TypeIndex ref_type_, TypeIndex const_ref_type_, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), ref_type(ref_type_), const_ref_type(const_ref_type_) {}

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
