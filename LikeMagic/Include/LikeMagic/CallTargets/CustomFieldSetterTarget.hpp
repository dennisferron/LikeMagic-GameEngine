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
class CustomFieldSetterTarget : public CallTarget
{
private:
    typedef StripModifiers<CallAs> stripped;
    typedef typename stripped::type ObjType;
    FieldAccessor f;
    typedef typename boost::remove_pointer<FieldAccessor>::type::FieldType FieldType;

public:

    static bool const is_const_func = false;

    CustomFieldSetterTarget(FieldAccessor f_) : f(f_) {}

    // Both the set and get target have a pointer to the same field accessor object;
    // only one of them needs to delete the shared accessor.
    ~CustomFieldSetterTarget() { delete f; }

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        f->set(
            try_conv<CallAs>(target)->eval(),
            try_conv<FieldType>(args[0])->eval()
        );
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<FieldType>());
    }

};

}}
