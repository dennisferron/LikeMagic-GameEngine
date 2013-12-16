
#include "Iocaste/Stack.hpp"
#include "Iocaste/CShims/Stack.h"
#include "Iocaste/Stack.hpp"

#include "List.h"

#include <vector>
using namespace std;

Iocaste::Stack<void*>& get_stack(Stack const* stack)
{
    return *reinterpret_cast<Iocaste::Stack<void*>*>(stack->impl);
}

typedef Iocaste::Stack<void*>::mark_type mark_type;

// Used in IO_METHOD(IoCoroutine, ioStack)
List *Stack_asList(const Stack *self)
{
	List *list = List_new();

    Iocaste::Stack<void*> s = get_stack(self);

    for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
        List_append_(list, *rit);

	return list;
}

void Stack_do_(const Stack *self, StackDoCallback *callback)
{
    Iocaste::Stack<void*> s = get_stack(self);

    for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
        (*callback)(*rit);
}


// Used in IoCoroutine *IoCoroutine_proto(void *state)
Stack *Stack_new(void)
{
    Stack* s = new Stack();
    s->impl = new Iocaste::Stack<void*>();
    return s;
}

// Used in void IoCoroutine_free(IoCoroutine *self)
void Stack_free(Stack *self)
{
    delete reinterpret_cast<Iocaste::Stack<void*>*>(self->impl);
    delete self;
}

void Stack_clear(Stack *self)
{
    get_stack(self).clear();
}

size_t Stack_totalSize(const Stack *self)
{
    return get_stack(self).size();
}

int Stack_count(const Stack *self)
{
    return static_cast<int>(Stack_totalSize(self));
}

void Stack_push_(Stack *self, void *item)
{
    get_stack(self).push(item);
}

intptr_t Stack_pushMarkPoint(Stack *self)
{
    mark_type mark = get_stack(self).push_mark_point();
    return *reinterpret_cast<intptr_t*>(&mark);
}

void *Stack_pop(Stack *self)
{
    return get_stack(self).pop();
}

void Stack_popMark(Stack *self)
{
    get_stack(self).pop_mark();
}

int Stack_popMarkPoint_(Stack *self, intptr_t mark)
{
    get_stack(self).pop_to_mark_point(
        *reinterpret_cast<mark_type*>(&mark));

    // Always return 1 for "success" (?)
    // The return value is never checked anyway in Io's C code.
    // C Io used a chain of marks on the stack linked to each other
    // and return 0 indicated a break in the chain. However Iocaste
    // stores the marks "out of band" in a separate container than stack, and "mark" is just
    // an index into the array of marks. The only way the Iocaste version can fail is if "mark"
    // indexes memory outside the bounds of the marks vector, in which case you have far
    // bigger problems anyway.
    return 1;
}

void Stack_clearTop(Stack *self)
{
    get_stack(self).clear_to_last_mark();
}

void *Stack_top(const Stack *self)
{
    return get_stack(self).top();
}
