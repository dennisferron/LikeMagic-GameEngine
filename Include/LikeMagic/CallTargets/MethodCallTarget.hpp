// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Term.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/MakeCall.hpp"

#include "LikeMagic/SFMO/methodcall_args.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;
using namespace LikeMagic::Generators;

template <MemberKind K, typename R, typename T, typename... Args>
class MethodCallTarget : public AbstractCallTargetSelector
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<Args>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

    // Decide whether to generate the call by-ref or by-const-ref.
    // Const functions convert the target to const ref, while
    // nonconst functions convert target to nonconst ref, which
    // fails by design for calling nonconst functions on value types.
    typedef typename CallAs<K, T>::type CallAs;

    typedef typename MemberPointer<K, R, T, Args...>::type F;

private:

    F func_ptr;

    // Handle functions that return a value
    template<typename R_, int... Indices>
    boost::intrusive_ptr<Expression<R_&>>
    build_method_call(ExprPtr target, ArgList args, TypePack<R_>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        CallAs& target_obj = type_system.try_conv<CallAs>(target)->eval();

        boost::intrusive_ptr<Expression<R&>> result = Term<R, true>::create(
            (target_obj.*func_ptr)(std::get<Indices>(args_tuple)->eval()...)
        );

        return result;
    }

    // Handle functions that do not return a value
    template<int... Indices>
    boost::intrusive_ptr<Expression<void>>
    build_method_call(ExprPtr target, ArgList args, TypePack<void>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        CallAs& target_obj = type_system.try_conv<CallAs>(target)->eval();

        (target_obj.*func_ptr)(std::get<Indices>(args_tuple)->eval()...);

        return Term<void, true>::create();
    }

public:

    MethodCallTarget(F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        auto result_proxy = ExprProxy::create
        (
            build_method_call
            (
                proxy->get_expr(), args, TypePack<R>(), IPack()
            ),
            type_system
        );
        return result_proxy;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

};

}}
