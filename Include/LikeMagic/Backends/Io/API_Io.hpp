// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/SFMO/AbstractCppObjProxy.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

// Using forward declarations here so that user of IoVM class doesn't
// actually need to include Io headers to create an IoVM object.
struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;

namespace LikeMagic { namespace Backends { namespace Io {

using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;

class IoVM;

bool is_sfmo_obj(IoObject* io_obj);
boost::intrusive_ptr<AbstractExpression> from_script(IoObject* self, IoObject* io_obj, AbstractTypeSystem const& type_sys, TypeIndex to_type);
void add_convs_from_script(AbstractTypeSystem& type_sys, IoVM* iovm);
void add_convs_to_script(AbstractTypeSystem& type_sys, IoVM* iovm);
std::string get_type_name(IoObject* io_obj);

IoMessage* new_message(IoObject* self, std::string name);

}}}
