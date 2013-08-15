// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/SetField.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Exprs/Reference.hpp"

#include "LikeMagic/CallTargets/Delegate.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename R>
class ArrayFieldReferenceTarget : public CallTarget
{
public:
    typedef R (Delegate::*F);

private:
    F const f_ptr;
    TypeIndex const actual_type;

public:

    ArrayFieldReferenceTarget(F f_ptr_, TypeIndex actual_type_)
        : f_ptr(f_ptr_), actual_type(actual_type_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        auto target_check = type_system->try_conv(target, actual_type);
        Delegate& target_obj = try_conv<Delegate&>(target_check)->eval();
        return Reference<R>::create(
            (target_obj.*f_ptr)[try_conv<size_t>(args[0])->eval()]);
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<size_t>());
    }
};

}}
