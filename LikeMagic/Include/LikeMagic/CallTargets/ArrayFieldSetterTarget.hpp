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
class ArrayFieldSetterTarget : public CallTarget
{
public:
    typedef R (Delegate::*F)[];

private:
    F const f_ptr;
    TypeIndex const actual_type;
    size_t array_size;

public:

    ArrayFieldSetterTarget(F f_ptr_, TypeIndex actual_type_, size_t array_size_)
        : f_ptr(f_ptr_), actual_type(actual_type_), array_size(array_size_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        ExprPtr wards[2];
        ExprPtr target_ward;
        Delegate& target_obj = eval_as_nonconst_target(target, actual_type, target_ward);
        (target_obj.*f_ptr)[EvalAs<size_t>::value(args[0], wards[0])]
            = EvalAs<R const&>::value(args[1], wards[1]);
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = MakeArgList<size_t, R const&>::value();
        return arg_types;
    }

    virtual TypeIndex get_return_type() const
    {
        return TypId<void>::liberal();
    }

    virtual bool is_inherited() const { return true; }

    virtual void mark() const { /* do nothing */ }
};

}
