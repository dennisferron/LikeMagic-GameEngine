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
class FieldReferenceTarget : public CallTarget
{
public:
    typedef R (Delegate::*F);

private:
    F const f_ptr;
    TypeIndex const actual_type;

public:

    FieldReferenceTarget(F f_ptr_, TypeIndex actual_type_)
        : f_ptr(f_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        ExprPtr target_check = type_system->try_conv(target, actual_type);
        ExprPtr target_warden;
        Delegate* target_obj = EvalAs<Delegate*>::value(target_check, target_warden);
        return create_reference(&(target_obj->*f_ptr), TypId<R*>::get(), target);
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        return empty_arg_list;
    }

    virtual bool is_inherited() const { return true; }
};

}
