
//metadoc Object copyright Steve Dekorte 2002
//metadoc Object license BSD revised

#include "Common_inline.h"

#include "IoVMApi.h"
#include "IoState.h"
#include "PHash.h"

#define Records_recordAt_(records, pos) (PHashRecord *)(records + (pos * sizeof(PHashRecord)))

PHashRecord *PHash_record1_(PHash *self, void *k);
PHashRecord *PHash_record2_(PHash *self, void *k);
void *PHash_at_(PHash *self, void *k);
unsigned int PHash_count(PHash *self);
int PHashKey_hasKey_(PHash *self, void *key);
void PHash_at_put_(PHash *self, void *k, void *v);
void PHash_shrinkIfNeeded(PHash *self);
void PHashRecord_swapWith_(PHashRecord *self, PHashRecord *other);
void PHash_clean(PHash *self);

// --- enumeration --------------------------------------------------

#define PHASH_FOREACH(self, pkey, pvalue, code) \
{\
	PHash *_self = (self);\
	unsigned char *_records = _self->records;\
	unsigned int _i, _size = _self->size;\
	void *pkey;\
	void *pvalue;\
	\
	for (_i = 0; _i < _size; _i ++)\
	{\
		PHashRecord *_record = Records_recordAt_(_records, _i);\
		if (_record->k)\
		{\
			pkey = _record->k;\
			pvalue = _record->v;\
			code;\
		}\
	}\
}

// ------------------------------------------------------------------


#define IOOBJECT_FOREACHPROTO(self, pvar, code) \
{\
	IoObject **_proto = IoObject_protos(self); \
	while (*_proto) \
	{ \
		IoObject *pvar = *_proto; \
		code; \
		_proto++; \
	} \
}

/*
PHash *IoObject_slots(IoObject *self)
{
	IoObjectData *od = IoObject_deref(self);
	return od->slots;
}

void IoObject_slots_(IoObject *self, PHash *v)
{
	IoObjectData *od = IoObject_deref(self);
	od->slots = v;
}

IoObject **IoObject_protos(IoObject *self)
{
	IoObjectData *od = IoObject_deref(self);
	return od->protos;
}

void IoObject_protos_(IoObject *self, IoObject **v)
{
	IoObjectData *od = IoObject_deref(self);
	od->protos = v;
}
*/

/*
int IoObject_isWhite(IoObject *self)
{
	return Collector_markerIsWhite_(IOCOLLECTOR, (CollectorMarker *)self);
}

int IoObject_isGray(IoObject *self)
{
	return Collector_markerIsGray_(IOCOLLECTOR, (CollectorMarker *)self);
}

int IoObject_isBlack(IoObject *self)
{
	return Collector_markerIsBlack_(IOCOLLECTOR, (CollectorMarker *)self);
}
*/

void IoObject_createSlotsIfNeeded(IoObject *self);
void IoObject_rawRemoveAllProtos(IoObject *self);
void IoObject_shouldMark(IoObject *self);
void IoObject_shouldMarkIfNonNull(IoObject *self);
void IoObject_freeIfUnreferenced(IoObject *self);
IoObject *IoObject_addingRef_(IoObject *self, IoObject *ref);
void IoObject_inlineSetSlot_to_(IoObject *self,
										 IoSymbol *slotName,
										 IoObject *value);
IoObject *IoObject_rawGetSlot_context_(IoObject *self,
												IoSymbol *slotName,
												IoObject **context);
IoObject *IoObject_rawGetSlot_(IoObject *self, IoSymbol *slotName);
int IoObject_mark(IoObject *self);

//IoObject *IoObject_addingRef_(IoObject *self, IoObject *ref);
IOVM_API  int IoObject_hasCloneFunc_(IoObject *self, IoTagCloneFunc *func);
//IOVM_API int IoObject_hasCloneFunc_(IoObject *self, IoTagCloneFunc *func);

//IOVM_API IoObject *IoObject_activate(IoObject *self,
IoObject *IoObject_activate(IoObject *self,
									 IoObject *target,
									 IoObject *locals,
									 IoMessage *m,
									 IoObject *slotContext);
IO_METHOD(IoObject, forward);
IO_METHOD(IoObject, perform);

