// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/IMarkable.hpp"

#include <tuple>

namespace Iocaste { namespace LMAdapters {

using namespace LM;

class FromIoTypeInfo
{
public:

    static TypeInfo create(std::string type_name)
    {
        return TypeInfo { "FromIo", type_name, LM::PtrType::NotPtr, LM::RefType::ValueNonconst, false };
    }

    static TypeIndex create_index(std::string type_name)
    {
        TypeInfo info = create(type_name);
        return get_index(
                info
        );
    }
};

}}
