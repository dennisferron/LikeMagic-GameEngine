// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/StripModifiers.hpp"

#include "LikeMagic/CallTargets/AbstractMethod.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/CallTargets/ICustomField.hpp"

#include "boost/shared_ptr.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;

template <typename CallAs, typename FieldAccessor>
class CustomFieldSetterTarget : public AbstractMethod
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
            type_system->try_conv<CallAs>(target)->eval(),
            type_system->try_conv<FieldType>(args[0])->eval()
        );
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<FieldType>());
    }

};

}}
