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

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename ObjT, typename... Args>
class ConstructorCallTarget : public CallTarget
{
private:
    bool auto_delete;

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        boost::intrusive_ptr<Term<ObjT*>> term = Term<ObjT*>::create(new ObjT(try_conv<Args>(args[Indices])->eval()...));
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
        static TypeInfoList arg_types = make_arg_list(TypePack<Args...>());
        return arg_types;
    }

    virtual bool is_inherited() const { return false; }
};

}}
