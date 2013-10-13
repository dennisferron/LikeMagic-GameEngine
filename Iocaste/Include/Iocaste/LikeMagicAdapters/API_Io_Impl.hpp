// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"

// The Io headers cause some compiler warnings; ignoring them to avoid cluttering error messages screen.
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wtype-limits"

// This makes it compile under windows.  Apparently both "inline" and the
// attribute are required together for it to work.
#define REPLACE_IOINLINE __attribute__((always_inline)) inline

// Note:  IoVM.h not the same thing as IoVM.hpp
#include "IoVM.h"

#include "IoBlock.h"

#include "IoState.h"
#include "IoNumber.h"
#include "IoSeq.h"
#include "IoState.h"
#include "IoObject.h"
#include "IoTag.h"
#include "IoError.h"

using namespace std;
using namespace LM;
using namespace Iocaste::LMAdapters;

extern "C"
{
    IoObject* API_io_rawClone(IoObject* proto);
    void API_io_free_expr(IoObject* self);
    void API_io_mark(IoObject* self);
    IoObject* API_io_proto(IoState* state);
    IoObject* API_io_perform(IoObject *self, IoObject *locals, IoMessage *m);
    IoObject* API_io_forward(IoObject *self, IoObject *locals, IoMessage *m);
    void API_io_willFree(IoObject *self);
}

// Using forward declarations here so that user of IoVM class doesn't
// actually need to include Io headers to create an IoVM object.
struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;

namespace Iocaste { namespace LMAdapters {

using namespace LM;
using namespace LM;

bool is_Exprs_obj(IoObject* io_obj);
boost::intrusive_ptr<Expr> from_script(IoObject* self, IoObject* io_obj, TypeIndex expected_type);

IoMethodTable* make_io_method_table(std::vector<std::string> const& method_names);
IoObject* get_io_arg_at(IoObject *self, IoObject *locals, IoMessage *m, int pos);
ExprPtr get_expr_arg_at(IoObject *self, IoObject *locals, IoMessage *m, int pos, TypeIndex target_type);

//IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy);

IoState* get_io_state(IoObject* self);

}}
