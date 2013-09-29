// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"

namespace LM {

LIKEMAGIC_API TypeInfoPtr create_bottom_ptr_type_info();
LIKEMAGIC_API TypeIndex create_bottom_ptr_type_index();

}
