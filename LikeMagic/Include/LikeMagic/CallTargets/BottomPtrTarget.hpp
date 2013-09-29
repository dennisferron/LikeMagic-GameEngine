// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Utility/TypePack.hpp"
#include "LikeMagic/Utility/make_arg_list.hpp"
#include "LikeMagic/Utility/BottomPtrTypeInfo.hpp"

namespace LM {

class BottomPtrTarget : public CallTarget
{
public:

    BottomPtrTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return create_expr(target->get_value_ptr(), create_bottom_ptr_type_index());
    }

    virtual TypeInfoList const& get_arg_types() const
    {
        return empty_arg_list;
    }

    virtual bool is_inherited() const { return true; }
};

}
