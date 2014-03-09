// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/CallTargets/DeleterCallTarget.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/TypeSystem.hpp"

using namespace LM;

DeleterCallTarget::DeleterCallTarget() {}

ExprPtr DeleterCallTarget::call(ExprPtr target, ArgList args) const
{
    TypeMirror const* mirror = type_system->get_class(target->get_type());
    mirror->try_delete(target.get());
    return 0;
}

TypeInfoList const& DeleterCallTarget::get_arg_types() const
{
    return empty_arg_list;
}
