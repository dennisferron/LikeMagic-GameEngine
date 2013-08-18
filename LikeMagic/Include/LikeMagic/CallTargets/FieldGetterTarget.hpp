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

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate& target_obj = try_conv<Delegate&>(target_check)->eval();
        return Term<R>::create(target_obj.*f_ptr);
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        return empty_arg_list;
    }
};

}}
