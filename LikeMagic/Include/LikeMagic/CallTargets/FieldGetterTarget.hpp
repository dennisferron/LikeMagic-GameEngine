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
class FieldGetterTarget : public CallTarget
{
public:
    typedef R (Delegate::*F);

private:
    F const f_ptr;
    TypeIndex const actual_type;

public:

    FieldGetterTarget(F f_ptr_, TypeIndex actual_type_)
        : f_ptr(f_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        ExprPtr target_ward;
        Delegate* target_obj = eval_as_target(target, actual_type, target_ward);
        return Term<R>::create(target_obj->*f_ptr);
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        return empty_arg_list;
    }

    virtual bool is_inherited() const { return true; }
};

}
