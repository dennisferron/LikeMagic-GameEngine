// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"

#include "LikeMagic/SFMO/ExprProxy.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename ObjT>
class DestructorCallTarget : public AbstractCallTargetSelector
{
private:

public:

    DestructorCallTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

   virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        ExprPtr target = proxy->get_expr();
        delete type_system.try_conv<ObjT const*>(target)->eval();
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};


}}
