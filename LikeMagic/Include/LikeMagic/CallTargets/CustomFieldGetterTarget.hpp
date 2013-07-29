// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/StripModifiers.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/SFMO/ExprProxy.hpp"

#include "boost/shared_ptr.hpp"

#include "LikeMagic/CallTargets/ICustomField.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename CallAs, typename FieldAccessor>
class CustomFieldGetterTarget : public AbstractCallTargetSelector
{
private:
    typedef StripModifiers<CallAs> stripped;
    typedef typename stripped::type ObjType;
    FieldAccessor f;
    typedef typename boost::remove_pointer<FieldAccessor>::type::FieldType FieldType;

public:

    static bool const is_const_func = true;

    CustomFieldGetterTarget(FieldAccessor f_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), f(f_) {}

    // Both the set and get target have a pointer to the same field accessor object;
    // only one of them needs to delete the shared accessor.
    //~CustomFieldGetterTarget() { delete f; }

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        return Term<FieldType, true>::create(
                    f->get(
                        type_system.try_conv<CallAs>(target)->eval()
                    )
                );
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};

}}
