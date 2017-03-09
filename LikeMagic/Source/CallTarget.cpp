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

namespace LM {

LIKEMAGIC_API Delegate& eval_as_nonconst_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward)
{
    TypeIndex target_type = get_index(
        from_type.get_info().as_ref_to_nonconst().as_restricted());
    ExprPtr target_check = type_system->try_conv(target, target_type);
    Delegate& result = EvalAs<Delegate&>::value(target_check, target_ward);

    //if (&result == nullptr)
    //    throw LM::Exception("Target of call is null!");

    return result;
}

LIKEMAGIC_API Delegate const& eval_as_const_target(ExprPtr target, TypeIndex from_type, ExprPtr& target_ward)
{
    TypeIndex target_type = get_index(
        from_type.get_info().as_ref_to_const().as_restricted());
    ExprPtr target_check = type_system->try_conv(target, target_type);
    Delegate const& result = EvalAs<Delegate const&>::value(target_check, target_ward);

    //if (&result == nullptr)
    //    throw LM::Exception("Target of call is null!");

    return result;
}

}
