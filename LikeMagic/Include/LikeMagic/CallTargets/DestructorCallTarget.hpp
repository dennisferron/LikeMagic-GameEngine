// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include "LikeMagic/CallTargets/AbstractMethod.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;

template <typename ObjT>
class DestructorCallTarget : public AbstractMethod
{
private:

public:

    DestructorCallTarget() {}

   virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        delete type_system->try_conv<ObjT const*>(target)->eval();
        return 0;
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

};


}}
