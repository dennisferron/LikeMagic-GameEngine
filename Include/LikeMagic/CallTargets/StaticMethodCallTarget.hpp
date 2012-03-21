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

#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;
using namespace LikeMagic::Generators;

template <typename R, typename... Args>
class StaticMethodCallTarget : public AbstractCallTargetSelector
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<Args>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
    typedef R (*F)(Args...);

private:

    F func_ptr;

    // Handle functions that return a value
    template<typename R_, int... Indices>
    boost::intrusive_ptr<Expression<R_&>>
    build_method_call(ArgList args, TypePack<R_>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        // When there are no args, args_tuple does not get expanded below and therefore is set but unused.
        #pragma GCC diagnostic ignored "-Wunused-but-set-variable"

        boost::intrusive_ptr<Expression<R&>> result = Term<R, true>::create(
            (*func_ptr)(std::get<Indices>(args_tuple)->eval()...)
        );

        return result;
    }

    // Handle functions that do not return a value
    template<int... Indices>
    boost::intrusive_ptr<Expression<void>>
    build_method_call(ArgList args, TypePack<void>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        (*func_ptr)(std::get<Indices>(args_tuple)->eval()...);

        return Term<void, true>::create();
    }

public:

    StaticMethodCallTarget(F func_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        auto result_proxy = ExprProxy::create
        (
            build_method_call
            (
                args, TypePack<R>(), IPack()
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
