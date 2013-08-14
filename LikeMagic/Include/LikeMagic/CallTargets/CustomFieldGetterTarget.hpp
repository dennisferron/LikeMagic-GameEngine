// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/StripModifiers.hpp"
#include "LikeMagic/CallTargets/CallTarget.hpp"
#include "LikeMagic/CallTargets/ICustomField.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Mirrors;

template <typename CallAs, typename FieldAccessor>
class CustomFieldGetterTarget : public CallTarget
{
private:
    typedef StripModifiers<CallAs> stripped;
    typedef typename stripped::type ObjType;
    FieldAccessor f;
    typedef typename boost::remove_pointer<FieldAccessor>::type::FieldType FieldType;

public:

    static bool const is_const_func = true;

    CustomFieldGetterTarget(FieldAccessor f_) : f(f_) {}

    // Both the set and get target have a pointer to the same field accessor object;
    // only one of them needs to delete the shared accessor.
    //~CustomFieldGetterTarget() { delete f; }

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return Term<FieldType, true>::create(
                    f->get(
                        try_conv<CallAs>(target)->eval()
                    )
                );
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};

}}
