
//--metadoc State copyright Steve Dekorte 2002
//--metadoc State license BSD revised

#define IOSTATE_C 1
#include "IoState.h"
#undef IOSTATE_C

#include "IoObject.h"
#include "IoCall.h"
#include "IoCoroutine.h"
#include "IoSeq.h"
#include "IoNumber.h"
#include "IoCFunction.h"
#include "IoBlock.h"
#include "IoList.h"
#include "IoMap.h"
//#include "IoRange.h"
#include "IoFile.h"
#include "IoDate.h"
#include "IoDuration.h"
#include "IoSeq.h"
#include "IoMessage_parser.h"
#include "IoDynLib.h"
#include "IoWeakLink.h"
#include "IoError.h"

#include "IoSystem.h"
#include "IoCompiler.h"
#include "IoDebugger.h"
#include "IoCollector.h"
#include "IoSandbox.h"
#include "IoDirectory.h"
#include "IoProfiler.h"
//#include "IoEditLine.h"

#include "Iocaste/CShims/Exception.h"
#include "Iocaste/IoCallStack.hpp"

#include <stdlib.h>

#include <iostream>
using namespace std;

#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
using namespace Iocaste;
using namespace Iocaste::LMAdapters;

IoDirectory *IoDirectory_proto(void *state);

typedef Iocaste::IoCallStack::mark_type mark_type;

// BEGIN IoState_inline

IoObject *IOTRUE(IoObject *self)
{
	return IOSTATE->ioTrue;
}

int ISTRUE(IoObject *self)
{
	return self != IOSTATE->ioNil && self != IOSTATE->ioFalse;
}

IoObject *IOFALSE(IoObject *self)
{
	return IOSTATE->ioFalse;
}

int ISFALSE(IoObject *self)
{
	return self == IOSTATE->ioNil || self == IOSTATE->ioFalse;
}

IoObject *IOBOOL(IoObject *self, int b)
{
	return b ? IOTRUE(self) : IOFALSE(self);
}

// collector --------------------------------------------------------

IoObject *IoState_retain_(IoState *self, IoObject *v)
{
	IoObject_isReferenced_(v, 1);
	Collector_retain_(self->collector, v);
	return v;
}

void IoState_stopRetaining_(IoState *self, IoObject *v)
{
	Collector_stopRetaining_(self->collector, v);
}

void *IoState_unreferencedStackRetain_(IoState *self, IoObject *v)
{
	if (self->currentCoroutine)
	{
		Collector_value_addingRefTo_(self->collector, self->currentCoroutine, v);
	}

	self->currentIoStack->retain_data(v);
	return v;
}

void *IoState_stackRetain_(IoState *self, IoObject *v)
{
	IoObject_isReferenced_(v, 1);
	IoState_unreferencedStackRetain_(self, v);
	return v;
}

void IoState_addValue_(IoState *self, IoObject *v)
{
	Collector_addValue_(self->collector, v);
	IoState_unreferencedStackRetain_(self, v);
}

void IoState_addValueIfNecessary_(IoState *self, IoObject *v)
{
	if (v->prev)
	{
		Collector_addValue_(self->collector, v);
	}
	IoState_unreferencedStackRetain_(self, v);
}

void IoState_retainCall_(IoState *self, IoCall *v)
{
	if (v->prev)
	{
		Collector_addValue_(self->collector, v);
	}
	self->currentIoStack->retain_call(v);
}

void IoState_pushCollectorPause(IoState *self)
{
	Collector_pushPause(self->collector);
}

void IoState_popCollectorPause(IoState *self)
{
	Collector_popPause(self->collector);
}

void IoState_clearRetainStack(IoState *self)
{
	self->currentIoStack->clear();
}

uintptr_t IoState_pushRetainPool(void *self)
{
	return ((IoState*)self)->currentIoStack->push_mark(MarkReason::Unspecified);
}

void IoState_clearTopPool(void *self)
{
	((IoState *)self)->currentIoStack->clear_to_last_mark();
}

void IoState_popRetainPool(void *self)
{
	((IoState *)self)->currentIoStack->pop_mark();
}

void IoState_popRetainPool_(void *self, uintptr_t mark)
{
    IoCallStack *stack = ((IoState *)self)->currentIoStack;
    stack->pop_to_mark_point(
            *reinterpret_cast<mark_type*>(&mark));
}

void IoState_popRetainPoolExceptFor_(void *state, void *obj)
{
	IoState *self = (IoState *)state;
	self->currentIoStack->pop_mark();
	IoState_stackRetain_(self, (IoObject *)obj);
}

IoObject *IoMessage_locals_quickValueArgAt_(IoMessage *self, IoObject *locals, int n)
{
	IoMessage *m = (IoMessage *)List_at_(IOMESSAGEDATA(self)->args, n);

	if (m)
	{
		IoMessageData *md = IOMESSAGEDATA(m);
		IoObject *v = md->cachedResult;

		if (v && !md->next)
		{
			return v;
		}

		return IoMessage_locals_performOn_(m, locals, locals);
	}

	return IOSTATE->ioNil;
}

IoObject *IoMessage_locals_valueArgAt_(IoMessage *self, IoObject *locals, int n)
{
	return IoMessage_locals_quickValueArgAt_(self, locals, n);
	/*
	List *args = IOMESSAGEDATA(self)->args;
	IoMessage *m = (IoMessage *)List_at_(args, n);

	if (m)
	{
		return IoMessage_locals_performOn_(m, locals, locals);
	}

	return IOSTATE->ioNil;
	*/
}

IoObject *IoMessage_locals_firstStringArg(IoMessage *self, IoObject *locals)
{
	// special case this, since it's used for setSlot()
	List *args = IOMESSAGEDATA(self)->args;

	if (List_size(args))
	{
		IoMessage *m = (IoMessage *)List_rawAt_(args, 0);

		if (m)
		{
			IoMessageData *md = IOMESSAGEDATA(m);
			IoObject *v = md->cachedResult;

			// avoid calling IoMessage_locals, if possible

			if (v && IoObject_isSymbol(v) && (md->next == NULL))
			{
				return v;
			}
		}
	}

	return IoMessage_locals_symbolArgAt_(self, locals, 0);
}

// --------------------------

void IoState_break(IoState *self, IoObject *v)
{
	self->stopStatus = MESSAGE_STOP_STATUS_BREAK;
	self->returnValue = v;
}

void IoState_continue(IoState *self)
{
	self->stopStatus = MESSAGE_STOP_STATUS_CONTINUE;
}

void IoState_eol(IoState *self)
{
	self->stopStatus = MESSAGE_STOP_STATUS_EOL;
}

void IoState_return(IoState *self, IoObject *v)
{
	self->stopStatus = MESSAGE_STOP_STATUS_RETURN;
	self->returnValue = v;
}

void IoState_resetStopStatus(IoState *self)
{
	self->stopStatus = MESSAGE_STOP_STATUS_NORMAL;
}

int IoState_handleStatus(IoState *self)
{
	switch (self->stopStatus)
	{
		case MESSAGE_STOP_STATUS_RETURN:
			return 1;

		case MESSAGE_STOP_STATUS_BREAK:
			IoState_resetStopStatus(self);
			return 1;

		case MESSAGE_STOP_STATUS_CONTINUE:
			IoState_resetStopStatus(self);
			return 0;

		default:
			return 0;
	}
}

IoObject *IoState_stopStatusObject(IoState *self, int stopStatus)
{
	switch(stopStatus)
	{
		case MESSAGE_STOP_STATUS_NORMAL:
			return self->ioNormal;

		case MESSAGE_STOP_STATUS_BREAK:
			return self->ioBreak;

		case MESSAGE_STOP_STATUS_CONTINUE:
			return self->ioContinue;

		case MESSAGE_STOP_STATUS_RETURN:
			return self->ioReturn;

		case MESSAGE_STOP_STATUS_EOL:
			return self->ioEol;

		default:
			return self->ioNormal;
	}
}

int IoState_stopStatusNumber(IoState *self, IoObject *obj)
{
	if (obj == self->ioNormal)
		return MESSAGE_STOP_STATUS_NORMAL;

	if (obj == self->ioBreak)
		return MESSAGE_STOP_STATUS_BREAK;

	if (obj == self->ioContinue)
		return MESSAGE_STOP_STATUS_CONTINUE;

	if (obj == self->ioReturn)
		return MESSAGE_STOP_STATUS_RETURN;

	if (obj == self->ioEol)
		return MESSAGE_STOP_STATUS_EOL;

	return MESSAGE_STOP_STATUS_NORMAL;
}

// END IoState_inline

void IoVMCodeInit(IoObject *context, char const * bootstrap_path);

void IoState_new_atAddress(void *address, char const * bootstrap_path)
{
	IoState *self = (IoState *)address;
	IoCFunction *cFunctionProto;
	IoSeq *seqProto;

	self->randomGen = RandomGen_new();
	RandomGen_setSeed(self->randomGen, 754905204); // no particular reason for this seed
	// collector

	self->collector = Collector_new();
	IoState_pushCollectorPause(self);

	Collector_setMarkFunc_(self->collector, (CollectorMarkFunc *)IoObject_mark);
	Collector_setWillFreeFunc_(self->collector, (CollectorWillFreeFunc *)IoObject_willFree);
	Collector_setFreeFunc_(self->collector, (CollectorFreeFunc *)IoObject_free);

	self->mainArgs   = MainArgs_new();
	self->primitives = PointerHash_new();

	self->recycledObjects = List_new();
	self->maxRecycledObjects = IOSTATE_DEFAULT_MAX_RECYCLED_OBJECTS;

	// Sandbox

	self->messageCount = 0;
	self->messageCountLimit = 0;
	self->endTime = 0;

	// symbol table

	self->symbols = CHash_new();

	CHash_setEqualFunc_(self->symbols, (CHashEqualFunc *)UArray_equals_);
	CHash_setHash1Func_(self->symbols, (CHashHashFunc *)UArray_evenHash);
	CHash_setHash2Func_(self->symbols, (CHashHashFunc *)UArray_oddHash);

	/*
	Problem:
	- there are some interdependencies here:
	- creating instances requires a retain stack
	- we need a Coroutine to use for our retainStack
	- defining any primitive methods requires Strings and CFunctions

	Solution:
	- create a temporary fake stack
	- create Object, CFunction and String protos sans methods.
	- then add methods to Object, CFunction and String
	*/

	self->currentIoStack = new IoCallStack(); // temp retain stack until coro is up

	self->objectProto = IoObject_proto(self); // need to do this first, so we have a retain stack
	//IoState_retain_(self, self->objectProto);

	self->mainCoroutine = IoCoroutine_proto(self);
    delete self->currentIoStack;
	self->currentIoStack = nullptr;
	IoState_setCurrentCoroutine_(self, self->mainCoroutine);

	seqProto = IoSeq_proto(self);

	IoState_setupQuickAccessSymbols(self);

	IoObject_rawSetProto_(seqProto, self->objectProto);

	cFunctionProto = IoCFunction_proto(self);
	self->localsUpdateSlotCFunc = IoState_retain_(self,
												  IoCFunction_newWithFunctionPointer_tag_name_(self,
												  IoObject_localsUpdateSlot, NULL, "localsUpdate"));

	IoSeq_protoFinish(seqProto);
	IoObject_protoFinish(self);
	IoCFunction_protoFinish(self);
	IoCoroutine_protoFinish(self->mainCoroutine);

	self->setSlotBlock  = IoState_retain_(self, IoObject_getSlot_(self->objectProto, SIOSYMBOL("setSlot")));

	// setup lobby

	{
		IoObject *objectProto = self->objectProto;
		IoObject *protos = IOCLONE(objectProto);
		IoObject *core = IOCLONE(objectProto);

		self->core = core;
		self->lobby = IOCLONE(objectProto);
		IoState_retain_(self, self->lobby);
		IoState_retain_(self, self->core);

		// setup namespace

		IoObject_setSlot_to_(self->lobby, SIOSYMBOL("Lobby"), self->lobby);
		IoObject_setSlot_to_(self->lobby, SIOSYMBOL("Protos"), protos);
		IoObject_setSlot_to_(protos, SIOSYMBOL("Core"), core);
		IoObject_setSlot_to_(protos, SIOSYMBOL("Addons"), IOCLONE(objectProto));

		IoObject_setSlot_to_(core, SIOSYMBOL("Compiler"),  IoCompiler_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Collector"), IoCollector_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Exception"), IocasteException_proto(self));

		// setup proto chain

		IoObject_rawSetProto_(objectProto, self->lobby);
		IoObject_rawSetProto_(self->lobby, protos);
		IoObject_rawSetProto_(protos, core);

		// add protos to namespace

		IoObject_setSlot_to_(core, SIOSYMBOL("Object"), objectProto);
		IoObject_setSlot_to_(core, SIOSYMBOL("Sequence"), seqProto);
		IoObject_setSlot_to_(core, SIOSYMBOL("Number"), IoNumber_proto(self));

		IoState_setupCachedNumbers(self);

		{
			IoObject *systemProto = IoSystem_proto(self);
			IoObject_setSlot_to_(core, SIOSYMBOL("System"), systemProto);
		}

		IoState_setupSingletons(self);
		IoState_setupCachedMessages(self);

		{
			self->debugger = IoState_retain_(self, IoDebugger_proto(self));
			IoObject_setSlot_to_(core, SIOSYMBOL("Debugger"), self->debugger);

			self->vmWillSendMessage  = IoMessage_newWithName_(self, SIOSYMBOL("vmWillSendMessage"));
			IoMessage_rawSetCachedResult_(self->nilMessage, self->ioNil);
			IoState_retain_(self, self->vmWillSendMessage);
		}

		IoObject_setSlot_to_(core, SIOSYMBOL("Block"),      IoBlock_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("List"),       IoList_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Map"),        IoMap_proto(self));
		//IoObject_setSlot_to_(core, SIOSYMBOL("Range"),      IoRange_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Coroutine"),  self->mainCoroutine);
		IoObject_setSlot_to_(core, SIOSYMBOL("Error"),      IoError_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("File"),       IoFile_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Directory"),  ::IoDirectory_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Date"),       IoDate_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Duration"),   IoDuration_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("WeakLink"),   IoWeakLink_proto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Sandbox"),    IoSandbox_proto(self));
		//IoObject_setSlot_to_(core, SIOSYMBOL("EditLine"),   IoEditLine_proto(self));

#if !defined(__SYMBIAN32__)
		IoObject_setSlot_to_(core, SIOSYMBOL("DynLib"),     IoDynLib_proto(self));
#endif

		//self->store =
		//IoObject_setSlot_to_(core, SIOSYMBOL("Store"),      self->store);
		IoObject_setSlot_to_(core, SIOSYMBOL("CFunction"),  cFunctionProto);
		IoObject_setSlot_to_(core, SIOSYMBOL("Profiler"),  IoProfiler_proto(self));

		self->localsProto = IoState_retain_(self, IoObject_localsProto(self));
		IoObject_setSlot_to_(core, SIOSYMBOL("Locals"),  self->localsProto);

		self->stopStatus = MESSAGE_STOP_STATUS_NORMAL;
		self->returnValue = self->ioNil;

		IoState_clearRetainStack(self);

		IoState_popCollectorPause(self);

		//Collector_collect(self->collector);

		//io_show_mem("before IoVMCodeInit");
		IoVMCodeInit(core, bootstrap_path);

		//io_show_mem("after IoVMCodeInit");
		//Collector_collect(self->collector);
		//io_show_mem("after Collector_collect");

		//IoState_popCollectorPause(self);
		IoState_clearRetainStack(self);

		//Collector_check(self->collector);
		Collector_collect(self->collector);
		//io_show_mem("after IoState_clearRetainStack and Collector_collect");
		IoState_setupUserInterruptHandler(self);
	}
}

void IoState_setupQuickAccessSymbols(IoState *self)
{
	self->activateSymbol     = IoState_retain_(self, SIOSYMBOL("activate"));
	self->callSymbol         = IoState_retain_(self, SIOSYMBOL("call"));
	self->forwardSymbol      = IoState_retain_(self, SIOSYMBOL("forward"));
	self->noShufflingSymbol  = IoState_retain_(self, SIOSYMBOL("__noShuffling__"));
	self->opShuffleSymbol    = IoState_retain_(self, SIOSYMBOL("opShuffle"));
	//self->performSymbol    = IoState_retain_(self, SIOSYMBOL("perform"));
	//self->referenceIdSymbol    = IoState_retain_(self, SIOSYMBOL("referenceId"));
	self->semicolonSymbol    = IoState_retain_(self, SIOSYMBOL(";"));
	self->selfSymbol         = IoState_retain_(self, SIOSYMBOL("self"));
	self->setSlotSymbol      = IoState_retain_(self, SIOSYMBOL("setSlot"));
	self->setSlotWithTypeSymbol  = IoState_retain_(self, SIOSYMBOL("setSlotWithType"));
	self->stackSizeSymbol    = IoState_retain_(self, SIOSYMBOL("stackSize"));
	self->typeSymbol         = IoState_retain_(self, SIOSYMBOL("type"));
	self->updateSlotSymbol   = IoState_retain_(self, SIOSYMBOL("updateSlot"));
}

void IoState_setupSingletons(IoState *self)
{
	IoObject *core = self->core;
	// nil

	self->ioNil = IOCLONE(self->objectProto);
	IoObject_setSlot_to_(core, SIOSYMBOL("nil"), self->ioNil);
	//IoObject_setSlot_to_(core, self->noShufflingSymbol, self->ioNil);
	IoObject_setSlot_to_(core, SIOSYMBOL("Message"), IoMessage_proto(self));
	IoObject_setSlot_to_(core, SIOSYMBOL("Call"),  IoCall_proto(self));

	self->nilMessage  = IoMessage_newWithName_(self, SIOSYMBOL("nil"));
	IoMessage_rawSetCachedResult_(self->nilMessage, self->ioNil);
	IoState_retain_(self, self->nilMessage);

	// true

	self->ioTrue = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("true"), self->ioTrue);
	IoObject_setSlot_to_(self->ioTrue, SIOSYMBOL("type"), SIOSYMBOL("true"));
	IoState_retain_(self, self->ioTrue);

	// false

	self->ioFalse = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("false"), self->ioFalse);
	IoObject_setSlot_to_(self->ioFalse, SIOSYMBOL("type"), SIOSYMBOL("false"));
	IoState_retain_(self, self->ioFalse);

	// Flow control: Normal
	self->ioNormal = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("Normal"), self->ioNormal);
	IoObject_setSlot_to_(self->ioNormal, SIOSYMBOL("type"), SIOSYMBOL("Normal"));
	IoState_retain_(self, self->ioNormal);

	// Flow control: Break
	self->ioBreak = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("Break"), self->ioBreak);
	IoObject_setSlot_to_(self->ioBreak, SIOSYMBOL("type"), SIOSYMBOL("Break"));
	IoState_retain_(self, self->ioBreak);

	// Flow control: Continue
	self->ioContinue = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("Continue"), self->ioContinue);
	IoObject_setSlot_to_(self->ioContinue, SIOSYMBOL("type"), SIOSYMBOL("Continue"));
	IoState_retain_(self, self->ioContinue);

	// Flow control: Return
	self->ioReturn = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("Return"), self->ioReturn);
	IoObject_setSlot_to_(self->ioReturn, SIOSYMBOL("type"), SIOSYMBOL("Return"));
	IoState_retain_(self, self->ioReturn);

	// Flow control: Eol
	self->ioEol = IoObject_new(self);
	IoObject_setSlot_to_(core, SIOSYMBOL("Eol"), self->ioEol);
	IoObject_setSlot_to_(self->ioEol, SIOSYMBOL("type"), SIOSYMBOL("Eol"));
	IoState_retain_(self, self->ioEol);
}

void IoState_setupCachedMessages(IoState *self)
{
	self->asStringMessage = IoMessage_newWithName_(self, SIOSYMBOL("asString"));
	IoState_retain_(self, self->asStringMessage);

	self->collectedLinkMessage = IoMessage_newWithName_(self, SIOSYMBOL("collectedLink"));
	IoState_retain_(self, self->collectedLinkMessage);

	self->compareMessage = IoMessage_newWithName_(self, SIOSYMBOL("compare"));
	IoState_retain_(self, self->compareMessage);

	//self->doStringMessage = IoMessage_newWithName_(self, SIOSYMBOL("doString"));
	//IoState_retain_(self, self->doStringMessage);

	self->initMessage = IoMessage_newWithName_(self, SIOSYMBOL("init"));
	IoState_retain_(self, self->initMessage);

	self->mainMessage = IoMessage_newWithName_(self, SIOSYMBOL("main"));
	IoState_retain_(self, self->mainMessage);

	self->opShuffleMessage = IoMessage_newWithName_(self, self->opShuffleSymbol);
	IoState_retain_(self, self->opShuffleMessage);

	self->printMessage = IoMessage_newWithName_(self, SIOSYMBOL("print"));
	IoState_retain_(self, self->printMessage);

	self->referenceIdForObjectMessage = IoMessage_newWithName_(self, SIOSYMBOL("referenceIdForObject"));
	IoState_retain_(self, self->referenceIdForObjectMessage);

	self->objectForReferenceIdMessage = IoMessage_newWithName_(self, SIOSYMBOL("objectForReferenceId"));
	IoState_retain_(self, self->objectForReferenceIdMessage);

	self->runMessage = IoMessage_newWithName_(self, SIOSYMBOL("run"));
	IoState_retain_(self, self->runMessage);

	self->willFreeMessage = IoMessage_newWithName_(self, SIOSYMBOL("willFree"));
	IoState_retain_(self, self->willFreeMessage);

	self->yieldMessage = IoMessage_newWithName_(self, SIOSYMBOL("yield"));
	IoState_retain_(self, self->yieldMessage);

	self->didFinishMessage = IoMessage_newWithName_(self, SIOSYMBOL("didFinish"));
	IoState_retain_(self, self->didFinishMessage);
}

IO_METHOD(IoObject, initBindings)
{
	IOSTATE->bindingsInitCallback(IOSTATE, self);
	return self;
}

void IoState_init(IoState *self)
{
	if (self->bindingsInitCallback)
	{
		IoState_pushCollectorPause(self);
		self->bindingsInitCallback(self, self->core);
		IoState_popCollectorPause(self);
		IoState_clearRetainStack(self);
	}
}

/*
IoObject_registerAsProto(IoObject *self)
{
	IoState_registerProtoWithNamed_(IOSTATE, self, IoObject_name(self));
}

void IoState_registerProtoWithNamed_(IoState *self, IoObject *proto, const char *name)
{
	if (PointerHash_at_(self->primitives, (void *)name))
	{
		printf("Error registering proto: %s\n", IoObject_name(proto));
		IoState_fatalError_(self, "IoState_registerProtoWithFunc_() Error: attempt to add the same proto twice");
	}

	IoState_retain_(self, proto);
	PointerHash_at_put_(self->primitives, (void *)func, proto);
	//printf("registered %s\n", IoObject_name(proto));
}
*/

void IoState_registerProtoWithFunc_(IoState *self, IoObject *proto, const char *v)
{
	IoState_registerProtoWithId_(self, proto, v);
}

IOVM_API void IoState_registerProtoWithId_(IoState *self, IoObject *proto, const char *v)
{
    IoVM* vm = static_cast<IoVM*>(self);
    Primitives& primitives = vm->primitives;
    TypeIndex index = primitives.indexOf(string(v));

    if (primitives.get(index))
	{
		printf("Error registering proto: %s\n", IoObject_name(proto));
		IoState_fatalError_(self, "IoState_registerProtoWithFunc_() Error: attempt to add the same proto twice");
	}

	IoState_retain_(self, proto);
	primitives.add(index, proto);
	cout << "Registered proto " << v << " with TypeIndex " << index.get_id() << endl;
}

IoObject *IoState_protoWithName_(IoState *self, const char *name)
{
    IoVM* vm = static_cast<IoVM*>(self);
    Primitives& primitives = vm->primitives;
    TypeIndex index = primitives.indexOf(string(name));
    return primitives.get(index);
}

List *IoState_tagList(IoState *self) // caller must io_free returned List
{
    IoVM* vm = static_cast<IoVM*>(self);
    Primitives& primitives = vm->primitives;
    std::vector<IoObject*> objs = primitives.toList();
    List *tags = List_new();
	POINTERHASH_FOREACH(self->primitives, k, proto, List_append_(tags, IoObject_tag((IoObject *)proto)));
	return tags;
}

void IoState_done(IoState *self)
{
	// this should only be called from the main coro from outside of Io

	List *tags = IoState_tagList(self); // need to get the tags before we io_free the protos

	self->maxRecycledObjects = 0;

	Collector_freeAllValues(self->collector); // io_free all objects known to the collector
	Collector_free(self->collector);

	List_do_(tags, (ListDoCallback *)IoTag_free);
	List_free(tags);

	PointerHash_free(self->primitives);
	CHash_free(self->symbols);

	//LIST_DO_(self->recycledObjects, IoObject_dealloc); // Old comment: "this does not work now that objects and marks are separate"
	{
        const List *foreachList = self->recycledObjects;
        size_t index, foreachMax = List_size(foreachList);

        for (index = 0; index < foreachMax; index++)
        {
            IoObject_dealloc((IoObject*)List_at_(foreachList, index));
        }
    }

	List_free(self->recycledObjects);
	List_free(self->cachedNumbers);

	RandomGen_free(self->randomGen);
	MainArgs_free(self->mainArgs);
}

void IoState_free(IoState *self)
{
	IoState_done(self);
	io_free(self);
}

IoObject *IoState_lobby(IoState *self)
{
	return self->lobby;
}

void IoState_setLobby_(IoState *self, IoObject *obj)
{
	self->lobby = obj;
}

void MissingProtoError(void)
{
	printf("missing proto\n");
}

IoObject *IoState_protoWithId_(IoState *self, const char *v)
{
	IoObject *proto = IoState_protoWithName_(self, v);

	//printf("IoState_protoWithId_(self, %s)\n", v);

	if (!proto)
	{
		printf("IoState fatal error: missing proto '%s'", v);
		IoState_fatalError_(self, "IoState_protoWithId_() Error: missing proto with id");
	}

	return proto;
}

// command line ------------------------------------------------

void IoState_argc_argv_(IoState *self, int argc, const char *argv[])
{
	IoList *args = IoList_new(self);
	int i;

	for (i = 1; i < argc; i ++)
	{
		IoList_rawAppend_(args, SIOSYMBOL(argv[i]));
	}

	{
		IoObject *system = IoObject_getSlot_(self->lobby, SIOSYMBOL("System"));
		IoObject_setSlot_to_(system, SIOSYMBOL("args"), args);
	}

	MainArgs_argc_argv_(self->mainArgs, argc, argv);
}

// store -------------------------------------------------------

IoObject *IoState_objectWithPid_(IoState *self, PID_TYPE pid)
{
	return self->ioNil;
}

// doString -------------------------------------------------------

IoObject *IoState_rawOn_doCString_withLabel_(IoState *self,
									IoObject *target,
									const char *s,
									const char *label)
{
	IoMessage *m = IoMessage_newFromText_label_(self, s, label);
	return IoMessage_locals_performOn_(m, target, target);
}

// CLI ---------------------------------------------------------

void IoState_rawPrompt(IoState *self)
{
	int max = 1024 * 16;
	char *s = (char*)io_calloc(1, max);
	IoObject *result;

	for (;;)
	{
		fputs("Io> ", stdout);
		fflush(stdout);
		fgets(s, max, stdin);

		if (feof(stdin))
		{
			break;
		}

		result = IoState_rawOn_doCString_withLabel_(self, self->lobby, s, "IoState_rawPrompt()");

		fputs("==> ", stdout);
		IoObject_print(result);
		fputs("\n", stdout);
	}

	io_free(s);
}

void IoState_runCLI(IoState *self)
{
	IoObject *result = IoState_on_doCString_withLabel_(self, self->lobby, "CLI run", "IoState_runCLI()");

	//IoObject *e = IoCoroutine_rawException(self->currentCoroutine);

	//if (e != self->ioNil)
	//{
	//	self->exitResult = -1;
	//}
	//else

	if (!self->shouldExit && ISNUMBER(result))
	{
		self->exitResult = CNUMBER(result);
	}
}

IOVM_API int IoState_exitResult(IoState *self)
{
	return self->exitResult;
}
