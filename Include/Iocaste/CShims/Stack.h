//metadoc Stack copyright Steve Dekorte 2002
//metadoc Stack license BSD revised
/*metadoc Stack description
	Stack - array of void pointers
	supports setting marks - when a mark is popped,
	all stack items above it are popped as well

	Designed to optimize push, pushMark and popMark
	at the expense of pop (since pop requires a mark check)
*/

#ifndef STACK_DEFINED
#define STACK_DEFINED 1

#include "Common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "List.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (StackDoCallback)(void *);
//typedef void (StackDoOnCallback)(void *, void *);

typedef struct
{
	void* impl;
} Stack;

//#define Stack_popCallback_(self, callback) self->popCallback = callback;

/*
BASEKIT_API Stack *Stack_clone(const Stack *self);
BASEKIT_API void Stack_copy_(Stack *self, const Stack *other);

BASEKIT_API size_t Stack_memorySize(const Stack *self);
BASEKIT_API void Stack_compact(Stack *self);

BASEKIT_API void Stack_resize(Stack *self);

BASEKIT_API void Stack_popToMark_(Stack *self, intptr_t mark);

// not high performance

BASEKIT_API void Stack_makeMarksNull(Stack *self);
BASEKIT_API Stack *Stack_newCopyWithNullMarks(const Stack *self);
BASEKIT_API void Stack_do_on_(const Stack *self, StackDoOnCallback *callback, void *target);

*/

// Used in IO_METHOD(IoCoroutine, ioStack)
BASEKIT_API List *Stack_asList(const Stack *self);

// Used in IoCoroutine *IoCoroutine_proto(void *state)
BASEKIT_API Stack *Stack_new(void);

// Used in void IoCoroutine_free(IoCoroutine *self)
BASEKIT_API void Stack_free(Stack *self);


//#include "Stack_inline.h"
 void Stack_do_(const Stack *self, StackDoCallback *callback);
 void Stack_clear(Stack *self);
 size_t Stack_totalSize(const Stack *self);
 int Stack_count(const Stack *self);
 void Stack_push_(Stack *self, void *item);
 intptr_t Stack_pushMarkPoint(Stack *self);
 void *Stack_pop(Stack *self);
 void Stack_popMark(Stack *self);
 int Stack_popMarkPoint_(Stack *self, intptr_t mark);
 void Stack_clearTop(Stack *self);
 void *Stack_top(const Stack *self);

//void *Stack_at_(const Stack *self, int i);
//BASEKIT_API void Stack_do_on_(const Stack *self, StackDoOnCallback *callback, void *target);


#ifdef __cplusplus
}
#endif
#endif
