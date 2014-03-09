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

#include "LikeMagic/IMarkable.hpp"

#include <tuple>

namespace LM {

class LangBlock : public LM::IMarkable
{
public:

    virtual ExprPtr call(ArgList args, std::size_t num_args) = 0;

    virtual ~LangBlock() = 0;

    template <typename... Args>
    void operator()(Args... args)
    {
        if (!empty())
        {
            ArgList argList = { Term<Args>::create(args)...};
            call(argList, sizeof...(args));
        }
    }

    template <typename R, typename... Args>
    R eval(Args... args)
    {
        if (!empty())
        {
            ArgList argList = { Term<Args>::create(args)...};
            ExprPtr ward;
            return EvalAs<R>::value(
                call(argList, sizeof...(args))
            , ward);
        }
        else
            throw std::logic_error("Tried to eval an empty block.");
    }

    virtual bool empty() const = 0;
};

typedef std::shared_ptr<LangBlock> BlockPtr;

}
