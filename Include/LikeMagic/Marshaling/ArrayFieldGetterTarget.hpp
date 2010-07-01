// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
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

#include "../SFMO/MethodCall.hpp"
#include "../SFMO/CppObjProxy.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename T, typename FieldPtr>
class ArrayFieldGetterTarget : public AbstractCallTargetSelector
{
private:
    typedef T const& CallAs;

    FieldPtr f_ptr;
    AbstractTypeSystem const& type_system;

    typedef FieldPtrTraits<FieldPtr, CallAs> Traits;

    typedef typename Traits::R FieldType;

public:

    //static bool const is_const_func = true;

    ArrayFieldGetterTarget(FieldPtr f_ptr_, AbstractTypeSystem const& type_system_) : f_ptr(f_ptr_), type_system(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        return CppObjProxy<FieldType&, true>::create(
                Term<FieldType, true>::create(
                    SetField<CallAs>::getAt(
                        type_system.try_conv<size_t>(args[0])->eval(),
                        type_system.try_conv<CallAs>(proxy->get_expr())->eval(),
                        f_ptr
                    )
                ), type_system
        );
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};

}}
