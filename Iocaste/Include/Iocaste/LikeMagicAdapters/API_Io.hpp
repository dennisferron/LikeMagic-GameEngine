// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"

// Using forward declarations here so that user of IoVM class doesn't
// actually need to include Io headers to create an IoVM object.
struct IoState;
struct IoObject;
typedef IoObject IoMessage;

namespace Iocaste { namespace LMAdapters {

using namespace LM;

class IoVM;

bool is_Exprs_obj(IoObject* io_obj);
ExprPtr from_script(IoObject* self, IoObject* io_obj, TypeIndex to_type);
void add_convs_from_script(IoVM* iovm);
void add_convs_to_script(IoVM* iovm);
std::string get_type_name(IoObject* io_obj);

IoMessage* new_message(IoObject* self, std::string name);

}}
