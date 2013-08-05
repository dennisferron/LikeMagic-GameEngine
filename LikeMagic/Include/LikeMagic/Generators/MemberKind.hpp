// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

namespace LikeMagic { namespace Generators {

enum class MemberKind
{
    member_nonconst,
    member_const,
    nonmember_op,
    static_method,
    field_nonconst,
    field_const
};

template <MemberKind K, typename ObjT>
struct CallAs
{
    typedef ObjT& type;
};

template <typename ObjT>
struct CallAs<MemberKind::member_const, ObjT>
{
    typedef ObjT const& type;
};

template <typename ObjT>
struct CallAs<MemberKind::field_const, ObjT>
{
    typedef ObjT const& type;
};

template <typename ObjT>
struct CallAs<MemberKind::static_method, ObjT>
{
    typedef LikeMagic::Utility::StaticMethod type;
};


template <MemberKind K, typename R, typename ObjT, typename... Args>
struct MemberPointer
{
    typedef R (ObjT::*type)(Args...);
};

template <typename R, typename ObjT, typename... Args>
struct MemberPointer<MemberKind::member_const, R, ObjT, Args...>
{
    typedef R (ObjT::*type)(Args...) const;
};

template <typename R>
struct ReturnAs
{
    typedef R& type;
};

template <>
struct ReturnAs<void>
{
    typedef void type;
};

}}
