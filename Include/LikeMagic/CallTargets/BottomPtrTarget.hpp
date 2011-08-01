// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/SFMO/BottomPtrExpr.hpp"
#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"
#include "LikeMagic/SFMO/BottomPtrExpr.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

class BottomPtrTarget : public AbstractCallTargetSelector
{
public:

    BottomPtrTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        /*
        return CppObjProxy<BottomPtrType, true>::create(
            BottomPtrExpr::create(type_system.try_conv<void*>(proxy->get_expr().get()))
          , type_system
        );
        */
        return CppObjProxy<BottomPtrType, true>::create(
            NullExpr::create()
          , type_system
        );
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};

}}
