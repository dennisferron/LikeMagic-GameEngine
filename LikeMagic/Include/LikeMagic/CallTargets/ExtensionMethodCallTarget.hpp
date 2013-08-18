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
#include "LikeMagic/Exprs/methodcall_args.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/IndexPack.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename R, typename FirstArg, typename... Args>
class ExtensionMethodCallTarget : public CallTarget
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

        boost::intrusive_ptr<Expression<R&>> result = Term<R>::create(
            (*func_ptr)(try_conv<FirstArg>(target)->eval(), try_conv<Args>(args[Indices])->eval()...)
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

        (*func_ptr)(try_conv<FirstArg>(target)->eval(), try_conv<Args>(args[Indices])->eval()...);

        return 0;
    }

public:

    ExtensionMethodCallTarget(F func_ptr_) : func_ptr(func_ptr_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return build_method_call(target, args, TypePack<R>(), IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }

};

}}
