
//metadoc Tag copyright Steve Dekorte 2002
//metadoc Tag license BSD revised

#define IOTAG_C 1
#include "IoTag.h"
#undef IOTAG_C

#include "IoObject.h"
#include "IoState.h"
#include <string.h>

// BEGIN IoTag_inline

// state

void IoTag_state_(IoTag *self, void *state)
{
	self->state = state;
}

void *IoTag_state(IoTag *self)
{
	return self->state;
}

// activate

void IoTag_activateFunc_(IoTag *self, IoTagActivateFunc *func)
{
	self->activateFunc = func;
}

IoTagActivateFunc *IoTag_activateFunc(IoTag *self)
{
	return self->activateFunc;
}

// clone

void IoTag_cloneFunc_(IoTag *self, IoTagCloneFunc *func)
{
	self->cloneFunc = func;
}

IoTagCloneFunc *IoTag_cloneFunc(IoTag *self)
{
	return self->cloneFunc;
}

// cleanup

void IoTag_cleanupFunc_(IoTag *self, IoTagFreeFunc *func)
{
	self->tagCleanupFunc = func;
}

IoTagCleanupFunc *IoTag_cleanupFunc(IoTag *self)
{
	return self->tagCleanupFunc;
}

// io_free

void IoTag_freeFunc_(IoTag *self, IoTagFreeFunc *func)
{
	if(func == free)
	{
		printf("IoTag_freeFunc_ called free\n");
		exit(-1);
	}

	self->freeFunc = func;
}

IoTagFreeFunc *IoTag_freeFunc(IoTag *self)
{
	return self->freeFunc;
}

// mark

void IoTag_markFunc_(IoTag *self, IoTagMarkFunc *func)
{
	self->markFunc = func;
}

IoTagMarkFunc *IoTag_markFunc(IoTag *self)
{
	return self->markFunc;
}

// compare

void IoTag_compareFunc_(IoTag *self, IoTagCompareFunc *func)
{
	self->compareFunc = func;
}

IoTagCompareFunc *IoTag_compareFunc(IoTag *self)
{
	return self->compareFunc;
}

// stream write

void IoTag_writeToStreamFunc_(IoTag *self, IoTagWriteToStreamFunc *func)
{
	self->writeToStreamFunc = func;
}

IoTagWriteToStreamFunc *IoTag_writeToStreamFunc(IoTag *self)
{
	return self->writeToStreamFunc;
}

// stream alloc

void IoTag_allocFromStreamFunc_(IoTag *self, IoTagAllocFromStreamFunc *func)
{
	self->allocFromStreamFunc = func;
}

IoTagAllocFromStreamFunc *IoTag_allocFromStreamFunc(IoTag *self)
{
	return self->allocFromStreamFunc;
}

// stream alloc

void IoTag_readFromStreamFunc_(IoTag *self, IoTagReadFromStreamFunc *func)
{
	self->readFromStreamFunc = func;
}

IoTagReadFromStreamFunc *IoTag_readFromStreamFunc(IoTag *self)
{
	return self->readFromStreamFunc;
}

// notification

void IoTag_notificationFunc_(IoTag *self, IoTagNotificationFunc *func)
{
	self->notificationFunc = func;
}

IoTagNotificationFunc *IoTag_notificationFunc(IoTag *self)
{
	return self->notificationFunc;
}

// perform

void IoTag_performFunc_(IoTag *self, IoTagPerformFunc *func)
{
	self->performFunc = func;
}

IoTagPerformFunc *IoTag_performFunc(IoTag *self)
{
	return self->performFunc;
}

// END IoTag_inline


IoTag *IoTag_new(void)
{
	IoTag *self = (IoTag *)io_calloc(1, sizeof(IoTag));
#ifdef IOMESSAGE_INLINE_PERFORM
	self->performFunc = NULL;
#else
	self->performFunc = (IoTagPerformFunc *)IoObject_perform;
#endif

	self->referenceCount = 1;
	//self->recyclableInstances = Stack_new();
	//self->maxRecyclableInstances = 10000;
	return self;
}

IoTag *IoTag_newWithName_(const char *name)
{
	IoTag *self = IoTag_new();
	IoTag_name_(self, name);
	return self;
}

void IoTag_free(IoTag *self)
{
	//printf("io_free tag %p\n", (void *)self);
	//printf("%s\n", self->name ? self->name : "NULL");
	if (--self->referenceCount > 0) {
		return;
	}

	if (self->tagCleanupFunc)
	{
		(self->tagCleanupFunc)(self);
	}

	if (self->name)
	{
		io_free(self->name);
		self->name = NULL;
	}

	//Stack_free(self->recyclableInstances);
	io_free(self);
}

int IoTag_reference(IoTag *self)
{
	return ++self->referenceCount;
}

void IoTag_name_(IoTag *self, const char *name)
{
	self->name = strcpy((char *)io_realloc(self->name, strlen(name)+1), name);
}

const char *IoTag_name(IoTag *self)
{
	return self->name;
}

void IoTag_mark(IoTag *self)
{
	/*
	if (Stack_count(self->recyclableInstances))
	{
		Stack_do_(self->recyclableInstances, (StackDoCallback *)IoObject_shouldMark);
	}
	*/
}

