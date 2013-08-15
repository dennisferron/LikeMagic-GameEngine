// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Exprs/Term.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename F>
class ProxyMethodSelector : public CallTarget
{
private:
    F func_ptr;

    typedef FuncPtrTraits<F> Traits;

    typedef typename Traits::TPack TPack;
    typedef typename Traits::IPack IPack;

    typedef typename Traits::R R;

    // This calls a function on the proxy object with return type R
    // and creates a new Term to hold it and returns it in a proxy object.
    template<typename R, typename... Args, int... Indices>
    typename boost::disable_if<boost::is_void<R>,
            ExprPtr>::type
    do_proxy_op(ExprPtr target, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        return Term<R, true>::create(
                    (target->*func_ptr)(try_conv<Args>(args[Indices])->eval()...));
    }

    // This calls a function on the proxy which returns void.
    template<typename R, typename... Args, int... Indices>
    typename boost::enable_if<
        boost::is_void<R>,
            ExprPtr>::type
    do_proxy_op(ExprPtr target, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        (target->*func_ptr)(try_conv<Args>(args[Indices])->eval()...);
        return 0;
    }

public:

    ProxyMethodSelector(F func_ptr_) : func_ptr(func_ptr_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return do_proxy_op<typename Traits::R>(target, args, TPack(), IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return Traits::get_arg_types();
    }
};

}}
