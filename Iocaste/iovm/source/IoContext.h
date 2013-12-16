
//metadoc Context copyright Steve Dekorte 2002
//metadoc Context license BSD revised

#ifndef IOCONTEXT_DEFINED
#define IOCONTEXT_DEFINED 1

#include "IoObject_struct.h"


typedef struct
{
	void *self;       // activationContext
	void *locals;     // currentContext
	void *message;
	void *slotContext;
} IoContext;

#define IOCONTEXT(self, locals, message) ((IoContext *){self, locals, message})

/*

#define SELF	(context->self)
#define LOCALS	(context->locals)
#define MESSAGE (context->message)

example:

	IO_METHOD(IoDuration, days);

becomes:

	IoObject *IoDuration_days(IoContext *context);
*/

#endif


