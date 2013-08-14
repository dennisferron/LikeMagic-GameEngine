// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/SetField.hpp"
#include "LikeMagic/CallTargets/CallTarget.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename T, typename FieldPtr>
class FieldSetterTarget : public CallTarget
{
private:
    typedef T& CallAs;

    FieldPtr f_ptr;

    typedef FieldPtrTraits<FieldPtr, CallAs> Traits;

    typedef typename Traits::R const& ArgType;

public:

    FieldSetterTarget(FieldPtr f_ptr_) : f_ptr(f_ptr_) {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        static_assert(boost::is_const<typename boost::remove_reference<ArgType>::type>::value, "Argument source must be const &" );

        //set_expr_debug_name(args[0]);
        SetField<CallAs>::set(try_conv<CallAs>(target)->eval(), f_ptr,
            try_conv<ArgType>(args[0]));
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<ArgType>());
    }
};

}}
