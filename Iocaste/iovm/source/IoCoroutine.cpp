
//metadoc Coroutine category Core
//metadoc Coroutine copyright Steve Dekorte 2002
//metadoc Coroutine license BSD revised
/*metadoc Coroutine description
Object wrapper for an Io coroutine.
*/

#include "IoCoroutine.h"
#include "IoObject.h"
#include "IoState.h"
#include "IoCFunction.h"
#include "IoSeq.h"
#include "IoNumber.h"
#include "IoList.h"
#include "IoBlock.h"

//#define DEBUG


#include "LikeMagic/Utility/TraceDb.hpp"
using namespace LM;


static const char *protoId = "Coroutine";

#define DATA(self) ((IoCoroutineData *)IoObject_dataPointer(self))

IoCoroutine *IoMessage_locals_coroutineArgAt_(IoMessage *self, void *locals, int n)
{
	IoObject *v = IoMessage_locals_valueArgAt_(self, (IoObject *)locals, n);
	if (!ISCOROUTINE(v)) IoMessage_locals_numberArgAt_errorForType_(self, (IoObject *)locals, n, "Coroutine");
	return v;
}

IoTag *IoCoroutine_newTag(void *state)
{
    IoTag *tag = IoTag_newWithName_(protoId);
	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoCoroutine_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoCoroutine_rawClone);
	IoTag_markFunc_(tag, (IoTagMarkFunc *)IoCoroutine_mark);
	return tag;
}

IoCoroutine *IoCoroutine_proto(void *state)
{
	IoObject *self = IoObject_new(state);

	IoObject_tag_(self, IoCoroutine_newTag(state));
	IoObject_setDataPointer_(self, io_calloc(1, sizeof(IoCoroutineData)));
	DATA(self)->ioStack = new Iocaste::IoCallStack();
    IoState_registerProtoWithId_((IoState *)state, self, protoId);

	return self;
}

void IoCoroutine_protoFinish(IoCoroutine *self)
{
	IoMethodTable methodTable[] = {
	{"ioStack", IoCoroutine_ioStack},
	{"run", IoCoroutine_run},
	{"main", IoCoroutine_main},
	{"resume", IoCoroutine_resume},
	{"isCurrent", IoCoroutine_isCurrent},
	{"currentCoroutine", IoCoroutine_currentCoroutine},
	{"implementation", IoCoroutine_implementation},
	{"setMessageDebugging", IoCoroutine_setMessageDebugging},
	{"freeStack", IoCoroutine_freeStack},
	{NULL, NULL},
	};

	IoObject_addMethodTable_(self, methodTable);
}

IoCoroutine *IoCoroutine_rawClone(IoCoroutine *proto)
{
	IoObject *self = IoObject_rawClonePrimitive(proto);
	IoObject_setDataPointer_(self, io_calloc(1, sizeof(IoCoroutineData)));
	DATA(self)->ioStack = new Iocaste::IoCallStack();
	return self;
}

IoCoroutine *IoCoroutine_new(void *state)
{
    IoObject *proto = IoState_protoWithId_((IoState *)state, protoId);
	IoObject* result = IOCLONE(proto);
    IF_TRACE_DB(trace_db->new_IoObject(result, proto, protoId, result->object->tag));
    return result;
}

void IoCoroutine_free(IoCoroutine *self)
{
	//Coro *coro = DATA(self)->cid;
	//if (coro) Coro_free(coro);
	delete DATA(self)->ioStack;
	io_free(DATA(self));
}

void IoCoroutine_mark(IoCoroutine *self)
{
    DATA(self)->ioStack->mark();
}

// raw

Iocaste::IoCallStack *IoCoroutine_rawIoStack(IoCoroutine *self)
{
	return DATA(self)->ioStack;
}

void IoCoroutine_rawShow(IoCoroutine *self)
{
	printf("TODO: IoCoroutine_rawShow\n");
	//DATA(self)->ioStack->do_(IoObject_show);
	//printf("\n");
}

void *IoCoroutine_cid(IoCoroutine *self)
{
	return 0;
}

// runTarget

void IoCoroutine_rawSetRunTarget_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("runTarget"), v);
}

IoObject *IoCoroutine_rawRunTarget(IoCoroutine *self)
{
	return IoObject_rawGetSlot_(self, IOSYMBOL("runTarget"));
}

// runMessage

void IoCoroutine_rawSetRunMessage_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("runMessage"), v);
}

IoObject *IoCoroutine_rawRunMessage(IoCoroutine *self)
{
	return IoObject_rawGetSlot_(self, IOSYMBOL("runMessage"));
}

// runLocals

void IoCoroutine_rawSetRunLocals_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("runLocals"), v);
}

IoObject *IoCoroutine_rawRunLocals(IoCoroutine *self)
{
	return IoObject_rawGetSlot_(self, IOSYMBOL("runLocals"));
}

// parent

void IoCoroutine_rawSetParentCoroutine_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("parentCoroutine"), v);
}

IoObject *IoCoroutine_rawParentCoroutine(IoCoroutine *self)
{
	return IoObject_getSlot_(self, IOSYMBOL("parentCoroutine"));
}

// result

void IoCoroutine_rawSetResult_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("result"), v);
}

IoObject *IoCoroutine_rawResult(IoCoroutine *self)
{
	return IoObject_getSlot_(self, IOSYMBOL("result"));
}

// exception

void IoCoroutine_rawRemoveException(IoCoroutine *self)
{
	IoObject_removeSlot_(self, IOSYMBOL("exception"));
}

void IoCoroutine_rawSetException_(IoCoroutine *self, IoObject *v)
{
	IoObject_setSlot_to_(self, IOSYMBOL("exception"), v);
}

IoObject *IoCoroutine_rawException(IoCoroutine *self)
{
	return IoObject_getSlot_(self, IOSYMBOL("exception"));
}

// ioStack

IO_METHOD(IoCoroutine, ioStack)
{
	/*doc Coroutine ioStack
	Returns List of values on this coroutine's stack.
	*/

	List *list = List_new();

	Iocaste::IoCallStack* call_stack = DATA(self)->ioStack;

    for (auto iter = call_stack->rbegin(); iter != call_stack->rend(); ++iter)
    {
        IoObject* io_obj = *iter;
        List_append_(list, io_obj);
    }

	return IoList_newWithList_(IOSTATE, list);
}

void IoCoroutine_rawReturnToParent(IoCoroutine *self)
{
	IoCoroutine *parent = IoCoroutine_rawParentCoroutine(self);

	if (parent && ISCOROUTINE(parent))
	{
		IoCoroutine_rawResume(parent);
	}
	else
	{
		if (self == IOSTATE->mainCoroutine)
		{
			printf("IoCoroutine error: attempt to return from main coro\n");
			//exit(-1);
		}
	}

	if (!ISNIL(IoCoroutine_rawException(self)))
	{
		IoCoroutine_rawPrintBackTrace(self);
	}

	printf("IoCoroutine error: unable to auto abort coro %p by resuming parent coro %s_%p\n",
			(void *)self, IoObject_name(parent), (void *)parent);
	//exit(-1);
}

void IoCoroutine_coroStart(void *context) // Called by Coro_Start()
{
	IoCoroutine *self = (IoCoroutine *)context;
	IoObject *result;

	IoState_setCurrentCoroutine_(IOSTATE, self);
	//printf("%p-%p start\n", (void *)self, (void *)DATA(self)->cid);
	result = IoMessage_locals_performOn_(IOSTATE->mainMessage, self, self);

	IoCoroutine_rawSetResult_(self, result);
	IoCoroutine_rawReturnToParent(self);
}

IO_METHOD(IoCoroutine, freeStack)
{
	/*doc Coroutine freeStack
	Frees all the internal data from the receiver's stack. Returns self.
	*/

	IoCoroutine *current = IoState_currentCoroutine(IOSTATE);
	return self;
}

IO_METHOD(IoCoroutine, main)
{
	IoObject *runTarget  = IoCoroutine_rawRunTarget(self);
	IoObject *runLocals  = IoCoroutine_rawRunLocals(self);
	IoObject *runMessage = IoCoroutine_rawRunMessage(self);

	if (runTarget && runLocals && runMessage)
	{
		return IoMessage_locals_performOn_(runMessage, runLocals, runTarget);
	}
	else
	{
		printf("IoCoroutine_main() missing needed parameters\n");
	}

	return IONIL(self);
}

Coro *IoCoroutine_rawCoro(IoCoroutine *self)
{
    return 0;
}

void IoCoroutine_clearStack(IoCoroutine *self)
{
	DATA(self)->ioStack->clear();
}

void IoCoroutine_rawRun(IoCoroutine *self)
{
	IoObject *result;

	IoObject *runTarget  = IoCoroutine_rawRunTarget(self);
	IoObject *runLocals  = IoCoroutine_rawRunLocals(self);
	IoObject *runMessage = IoCoroutine_rawRunMessage(self);

    result = IoMessage_locals_performOn_(runMessage, runLocals, runTarget);

	IoCoroutine_rawSetResult_(self, result);
}

IO_METHOD(IoCoroutine, run)
{
	/*doc Coroutine run
	Runs receiver and returns self.
	*/

	IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
	IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
	IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);

    return IoMessage_locals_performOn_(runMessage, runLocals, runTarget);
}

void IoCoroutine_try(IoCoroutine *self, IoObject *target, IoObject *locals, IoMessage *message)
{
	IoCoroutine *currentCoro = (IoCoroutine *)IoState_currentCoroutine((IoState *)IOSTATE);
	IoCoroutine_rawSetRunTarget_(self, target);
	IoCoroutine_rawSetRunLocals_(self, locals);
	IoCoroutine_rawSetRunMessage_(self, message);
	IoCoroutine_rawSetParentCoroutine_(self, currentCoro);
	IoCoroutine_rawRun(self);
}

IoCoroutine *IoCoroutine_newWithTry(void *state,
									IoObject *target,
									IoObject *locals,
									IoMessage *message)
{
	IoCoroutine *self = IoCoroutine_new(state);
	IoCoroutine_try(self, target, locals, message);
	return self;
}

// methods

IoObject *IoCoroutine_rawResume(IoCoroutine *self)
{
    /*
	if(DATA(self)->cid)
	{
		IoCoroutine *current = IoState_currentCoroutine(IOSTATE);
		IoState_setCurrentCoroutine_(IOSTATE, self);
		//printf("IoCoroutine resuming %p\n", (void *)self);
		Coro_switchTo_(IoCoroutine_rawCoro(current), IoCoroutine_rawCoro(self));

		//IoState_setCurrentCoroutine_(IOSTATE, current);
	}
	else
	{
		//printf("IoCoroutine_rawResume: can't resume coro that hasn't been run - so running it\n");
		IoCoroutine_rawRun(self);
	}
    */
	return self;
}

IO_METHOD(IoCoroutine, resume)
{
	/*doc Coroutine resume
	Yields to the receiver. Runs the receiver if it is not running yet.
	Returns self.
	*/

	return IoCoroutine_rawResume(self);
}

IO_METHOD(IoCoroutine, implementation)
{
	/*doc Coroutine implementation
	Returns coroutine implementation type: "fibers", "ucontext" or "setjmp"
	*/

	//return IOSYMBOL(CORO_IMPLEMENTATION);

	return IOSYMBOL("nothing");
}

IO_METHOD(IoCoroutine, isCurrent)
{
	/*doc Coroutine isCurrent
	Returns true if the receiver is currently running coroutine.
	*/

	IoObject *v = IOBOOL(self, self == IoState_currentCoroutine(IOSTATE));
	return v;
}

IO_METHOD(IoCoroutine, currentCoroutine)
{
	/*doc Coroutine currentCoroutine
	Returns currently running coroutine in Io state.
	*/

	return IoState_currentCoroutine(IOSTATE);
}

// stack trace

int IoCoroutine_rawIoStackSize(IoCoroutine *self)
{
	return (int)DATA(self)->ioStack->size();
}

void IoCoroutine_rawPrint(IoCoroutine *self)
{
    /*
	Coro *coro = DATA(self)->cid;

	if (coro)
	{
		printf("Coroutine_%p with cid %p ioStackSize %i\n",
				(void *)self,
				(void *)coro,
				(int)Stack_count(DATA(self)->ioStack));
	}
	*/
}

// debugging

int IoCoroutine_rawDebuggingOn(IoCoroutine *self)
{
	return DATA(self)->debuggingOn;
}

IO_METHOD(IoCoroutine, setMessageDebugging)
{
	/*doc Coroutine setMessageDebugging(aBoolean)
	Turns on message level debugging for this coro. When on, this
	coro will send a vmWillSendMessage message to the Debugger object before
	each message send and pause itself. See the Debugger object documentation
	for more information.
	*/

	IoObject *v = IoMessage_locals_valueArgAt_(m, locals, 0);

	DATA(self)->debuggingOn = ISTRUE(v);
	IoState_updateDebuggingMode(IOSTATE);

	return self;
}

IoObject *IoObject_performWithDebugger(IoCoroutine *self, IoObject *locals, IoMessage *m)
{
	IoState *state = IOSTATE;
	IoObject *currentCoroutine = IoState_currentCoroutine(state);

	if (IoCoroutine_rawDebuggingOn(currentCoroutine))
	{
		IoObject *debugger = state->debugger; // stack retain it?

		if (debugger)
		{
			IoObject_setSlot_to_(debugger, IOSYMBOL("messageCoroutine"), currentCoroutine);
			IoObject_setSlot_to_(debugger, IOSYMBOL("messageSelf"), self);
			IoObject_setSlot_to_(debugger, IOSYMBOL("messageLocals"), locals);
			IoObject_setSlot_to_(debugger, IOSYMBOL("message"), m);

			{
				IoObject *context;
				IoCoroutine *c = IoObject_rawGetSlot_context_(debugger, IOSYMBOL("debuggerCoroutine"), &context);
				IOASSERT(c, "Debugger needs a debuggerCoroutine slot");
				IoCoroutine_rawResume(c);
			}
		}
	}

	return IoObject_perform(self, locals, m);
}

void IoCoroutine_rawPrintBackTrace(IoCoroutine *self)
{
	IoObject *e = IoCoroutine_rawException(self);
	IoMessage *caughtMessage = IoObject_rawGetSlot_(e, IOSYMBOL("caughtMessage"));

	if (IoObject_rawGetSlot_(e, IOSYMBOL("showStack"))) // sanity check
	{
		IoState_on_doCString_withLabel_(IOSTATE, e, "showStack", "[Coroutine]");
	}
	else
	{
		IoSymbol *error = IoObject_rawGetSlot_(e, IOSYMBOL("error"));

		if (error)
		{
			fputs(CSTRING(error), stderr);
			fputs("\n", stderr);
		}
		else
		{
			fputs("error: [missing error slot in Exception object]\n", stderr);
		}

		if (caughtMessage)
		{
			UArray *ba = IoMessage_asMinimalStackEntryDescription(caughtMessage);
			fputs(UArray_asCString(ba), stderr);
			fputs("\n", stderr);
			UArray_free(ba);
		}
	}
}
