// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "../Utility/SetField.hpp"

#include "AbstractCallTargetSelector.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"
#include "boost/type_traits/is_base_of.hpp"

#include "../SFMO/MethodCall.hpp"
#include "../SFMO/CppObjProxy.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename T, typename FieldPtr>
class FieldSetterTarget : public AbstractCallTargetSelector
{
private:
    typedef T& CallAs;

    FieldPtr f_ptr;

    typedef FieldPtrTraits<FieldPtr, CallAs> Traits;

    typedef typename Traits::R const& ArgType;

public:

    static bool const is_const_func = false;

    FieldSetterTarget(FieldPtr f_ptr_, AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_), f_ptr(f_ptr_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        set_expr_debug_name(args[0]);
        SetField<CallAs>::set(type_system.try_conv<CallAs>(proxy->get_expr())->eval(), f_ptr,
            type_system.try_conv<ArgType>(args[0]));
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<ArgType>());
    }

};

}}
