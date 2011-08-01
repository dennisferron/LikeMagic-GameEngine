// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/ImplicitConv.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

template <typename From, typename To>
class GenericConv : public ImplicitConv<From, To>
{
private:
    TypeInfoPtr from_info;
    TypeInfoPtr to_info;

public:

    GenericPtrConv(TypeInfoPtr from, TypeInfoPtr to) : from_info(from), to_info(to)
    {
    }

    virtual std::string describe() const
    {
        return
            "GenericConv " +
            " from " + from_info->describe() +
            " to " + to_info->describe();
    }
};


}}
