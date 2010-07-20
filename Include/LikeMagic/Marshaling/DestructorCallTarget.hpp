// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include "AbstractCallTargetSelector.hpp"

#include "../SFMO/CppObjProxy.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename ObjT>
class DestructorCallTarget : public AbstractCallTargetSelector
{
private:
    AbstractTypeSystem const& type_system;

public:

    DestructorCallTarget(AbstractTypeSystem const& type_system_) : type_system(type_system_) {}

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
