// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exceptions/Exception.hpp"

using namespace LM;

Delegate* CallTarget::eval_as_target(ExprPtr target, TypeIndex actual_type, ExprPtr& target_ward)
{
    ExprPtr target_check = type_system->try_conv(target, actual_type);
    Delegate* result = EvalAs<Delegate*>::value(target_check, target_ward);

    if (result == nullptr)
        throw LM::Exception("Target of call is null!");

    return result;
}
