// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Mirrors/CallTarget.hpp"

#include "LikeMagic/CallTargets/Delegate.hpp"

namespace LM {

template <typename R>
class FieldSetterTarget : public CallTarget
{
public:
    typedef R (Delegate::*F);

private:
    F const f_ptr;
    TypeIndex const actual_type;

public:

    FieldSetterTarget(F f_ptr_, TypeIndex actual_type_)
        : f_ptr(f_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        ExprPtr target_ward;
        ExprPtr arg_ward;
        Delegate& target_obj = eval_as_nonconst_target(target, actual_type, target_ward);
        (target_obj.*f_ptr) = EvalAs<R const&>::value(args[0], arg_ward);
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<R const&>::value();
        return arg_types;
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

}
