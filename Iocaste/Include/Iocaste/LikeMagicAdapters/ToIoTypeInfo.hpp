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
#include "LikeMagic/Utility/TypeInfo.hpp"

#include <tuple>

namespace Iocaste { namespace LMAdapters {

using LM::TypeSystem;
using namespace LM;
using namespace LM;

class ToIoTypeInfo
{
public:

    static TypeInfo create()
    {
        return create("");
    }

    static TypeInfo create(std::string type_name)
    {
        return TypeInfo { "ToIo", type_name, false, false };
    }

    static TypeIndex create_index()
    {
        static TypeInfo info = create();
        return get_index(info);
    }

    static TypeIndex create_index(std::string type_name)
    {
        static TypeInfo info = create(type_name);
        return get_index(info);
    }
};

}}
