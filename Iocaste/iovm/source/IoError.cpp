//metadoc Error category Core
//metadoc Error copyright Rich Collins 2008
//metadoc Error license BSD revised
/*metadoc Error description
An object that contains error information and flow control based on errors.
*/

#include "IoError.h"
#include "IoState.h"
#include "IoSeq.h"

#include "LikeMagic/Utility/TraceDb.hpp"
using namespace LM;

static const char *protoId = "Error";

IoTag *IoError_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("Error");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoError_rawClone);
	return tag;
}

IoError *IoError_proto(void *state)
{
	IoError *self = IoObject_new(state);
	IoObject_tag_(self, IoError_newTag(state));

	IoState_registerProtoWithId_((IoState*)state, self, protoId);

	{
		IoMethodTable methodTable[] = {
			{NULL, NULL}
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}

IoError *IoError_rawClone(IoError *proto)
{
	IoError *self = IoObject_rawClonePrimitive(proto);
	return self;
}

IoError *IoError_new(void *state)
{
	IoError *proto = IoState_protoWithId_((IoState*)state, protoId);
	IoObject* result = IOCLONE(proto);
    IF_TRACE_DB(trace_db->new_IoObject(result, proto, protoId, result->object->tag));
    return result;
}

/* ----------------------------------------------------------- */

IoError *IoError_newWithMessageFormat_(void *state, const char *format, ...)
{
	IoSymbol *message;

	va_list ap;
	va_start(ap, format);
	message = IoState_symbolWithUArray_copy_((IoState*)state, UArray_newWithVargs_(format, ap), 0);
	va_end(ap);

	{
		IoError *error = IoError_new(state);
		IoObject_setSlot_to_(error, IoState_symbolWithCString_((IoState*)state, (char *)("message")), message);
		return error;
	}
}

IoError *IoError_newWithCStringMessage_(IoState *state, char *cString)
{
	IoError *error = IoError_new(state);
	IoObject_setSlot_to_(error,
		IoState_symbolWithCString_(state, (char *)("message")),
		IoSeq_newWithCString_(state, cString)
	);
	return error;
}
