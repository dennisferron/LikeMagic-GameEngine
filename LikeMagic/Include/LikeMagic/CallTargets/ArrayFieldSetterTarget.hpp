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
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate& target_obj = try_conv<Delegate&>(target_check)->eval();
        (target_obj.*f_ptr)[try_conv<size_t>(args[0])->eval()] = try_conv<R const&>(args[1])->eval();
        return 0;
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        static TypeInfoList arg_types = make_arg_list(TypePack<size_t, R const&>());
        return arg_types;
    }
};

}}
