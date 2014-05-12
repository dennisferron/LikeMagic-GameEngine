// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/IndexPack.hpp"
#include "LikeMagic/Utility/TypePack.hpp"
#include "LikeMagic/Exprs/Term.hpp"

namespace LM {

template <typename ObjT, typename... Args>
class ConstructorCallTarget : public CallTarget
{
private:
    bool auto_delete;

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        ExprPtr wards[sizeof...(Args)];
        ExprPtr term = Term<ObjT*>::create(new ObjT(
            EvalAs<Args>::value(args[Indices], wards[Indices])...));
        term->set_auto_delete_ptr(auto_delete);
        return term;
    }

public:

    ConstructorCallTarget(bool auto_delete_) : auto_delete(auto_delete_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(args, IPack());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<Args...>::value();
        return arg_types;
    }

    virtual TypeIndex get_return_type() const
    {
        return TypId<ObjT>::liberal();
    }

    virtual bool is_inherited() const { return false; }

    virtual void mark() const { /* do nothing */ }
};

}
