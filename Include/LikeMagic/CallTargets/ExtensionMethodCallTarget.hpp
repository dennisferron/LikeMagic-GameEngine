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

#include "LikeMagic/SFMO/ExprProxy.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;
using namespace LikeMagic::Generators;

template <typename R, typename FirstArg, typename... Args>
class ExtensionMethodCallTarget : public AbstractCallTargetSelector
{
public:
    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
    typedef R (*F)(FirstArg, Args...);

private:

    F func_ptr;

    // Handle functions that return a value
    template<typename R_, int... Indices>
    boost::intrusive_ptr<Expression<R_&>>
    build_method_call(ExprPtr target, ArgList args, TypePack<R_>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        boost::intrusive_ptr<Expression<R&>> result = Term<R, true>::create(
            (*func_ptr)(type_system.try_conv<FirstArg>(target)->eval(), type_system.try_conv<Args>(args[Indices])->eval()...)
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

        (*func_ptr)(type_system.try_conv<FirstArg>(target)->eval(), type_system.try_conv<Args>(args[Indices])->eval()...);

        return Term<void, true>::create();
    }

public:

    ExtensionMethodCallTarget(F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

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
        TypeInfoList args = make_arg_list(TypePack<Args...>());

        return args;
    }

};

}}
