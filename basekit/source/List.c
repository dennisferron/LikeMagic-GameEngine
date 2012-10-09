//metadoc List copyright Steve Dekorte 2002
//metadoc List license BSD revised

#define LIST_C
#include "List.h"
#undef LIST_C
#include <stdlib.h>

// Begin:  List_inline

size_t List_size(const List *self)
{
	return self->size;
}

void List_ifNeededSizeTo_(List *self, size_t newSize)
{
	if (newSize * sizeof(void *) >= self->memSize)
	{
		List_preallocateToSize_(self, newSize);
	}
}

void *List_rawAt_(List *self, size_t index)
{
	return self->items[index];
}


void *List_at_(const List *self, ssize_t index)
{

    /* Negative indexing is also supported. */
    if (index < 0)
    {
        index += self->size;
    }

    if (index < (ssize_t)self->size)
    {
        return self->items[index];
    }

    return (void *)NULL;
}

// --------------------------------------------

size_t List_indexOf_(List *self, void *item)
{
	LIST_FOREACH(self, i, v, if(v == item) return i);
	return -1;
}

int List_contains_(List *self, void *item)
{
	LIST_FOREACH(self, i, v, if(v == item) return 1);
	return 0;
}

void *List_append_(List *self, void *item)
{
	List_ifNeededSizeTo_(self, self->size + 1);
	self->items[self->size] = item;
	self->size ++;
	return item;
}

void List_appendSeq_(List *self, const List *otherList)
{
	LIST_FOREACH(otherList, i, v, List_append_(self, v));
}

void List_compactIfNeeded(List *self)
{
	if(self->memSize > 1024 && self->size * sizeof(void *) * 4 < self->memSize)
	{
		List_compact(self);
	}
}

void List_removeIndex_(List *self, size_t index)
{
	if (index < self->size)
	{
		if ( index != self->size - 1)
		{
			memmove(&self->items[index], &self->items[index + 1],
				   (self->size - 1 - index) * sizeof(void *));
		}

		self->size --;

		List_compactIfNeeded(self);
	}
}

void List_removeIndex_toIndex_(List *self, size_t index1, size_t index2)
{
	size_t length;

	if (index1 > self->size - 1)
	{
		index1 = self->size - 1;
	}

	if (index2 > self->size - 1)
	{
		index2 = self->size - 1;
	}

	length = index2 - index1;

	if (length <= 0)
	{
		return;
	}

	memmove(&self->items[index1], &self->items[index2],
		   (self->size - index2) * sizeof(void *));

	self->size -= length;

	List_compactIfNeeded(self);
}

void List_remove_(List *self, void *item)
{
	size_t index;

	for (index = 0; index < self->size; index ++)
	{
		if (self->items[index] == item)
		{
			List_removeIndex_(self, index);
		}
	}
}

int List_removeFirst_(List *self, void *item)
{
	size_t i, max = self->size;

	for (i = 0; i < max; i ++)
	{
		if (self->items[i] == item)
		{
			List_removeIndex_(self, i);
			return 1;
		}
	}

	return 0;
}

void List_removeLast_(List *self, void *item)
{
	size_t index = self->size - 1;

	for (index = self->size - 1; (ssize_t)index > -1; index --)
	{
		if (self->items[index] == item)
		{
			List_removeIndex_(self, index);
			break;
		}
	}
}

void List_removeItems_(List *self, List *other)
{
	LIST_FOREACH(other, i, v, List_remove_(self, v));
}

void List_at_insert_(List *self, size_t index, void *item)
{
	if (index > self->size - 1)
	{
		List_preallocateToSize_(self, index + 1);
	}
	else
	{
		List_ifNeededSizeTo_(self, self->size + 1);
	}

	memmove(&self->items[index + 1], &self->items[index],
		   (self->size - index) * sizeof(void *));

	self->items[index] = item;
	self->size ++;
}

void List_at_put_(List *self, size_t index, void *item)
{
	List_ifNeededSizeTo_(self, index);
	self->items[index] = item;

	if (index + 1 > self->size)
	{
		self->size = index + 1;
	}
}

void List_swap_with_(List *self, long index1, long index2)
{
	if (index1 < 0 || index2 < 0)
	{
		return;
	}

	if (index1 != index2)
	{
		void **items = self->items;
		register void *v1 = items[index1];

		items[index1] = items[index2];
		items[index2] = v1;
	}
}

void List_reverseInPlace(List *self)
{
	register void **i = self->items;
	register void **j = i + (self->size - 1);
	register void *iv;

	while (j > i)
	{
		iv = *i;
		*i = *j;
		*j = iv;
		j --;
		i ++;
	}
}

// stack --------------------------------------------------

void List_push_(List *self, void *item)
{
	List_ifNeededSizeTo_(self, self->size + 1);
	self->items[self->size] = item;
	self->size ++;
}

void *List_pop(List *self)
{
	void *item;

	if (!self->size)
	{
		return (void *)NULL;
	}

	self->size --;
	item = self->items[self->size];
	List_compactIfNeeded(self);
	return item;
}

void *List_top(const List *self)
{
	if (!self->size)
	{
		return (void *)NULL;
	}

	return self->items[self->size - 1];
}

/* --- perform -------------------------------------------------- */

int List_removeTrueFor_(List *self, ListCollectCallback* callback)
{
	size_t getIndex = 0;
	size_t putIndex = 0;
	size_t count = self->size;
	void **items = self->items;

	while (getIndex < count)
	{
		void *item = items[getIndex];

		if (item && !((*callback)(item)))
		{
			if (getIndex!=putIndex)
			{
				items[putIndex] = item;
			}

			putIndex ++;
		}

		getIndex ++;
	}

	self->size = putIndex;

	return (int)(getIndex - putIndex);
}

void List_qsort(List *self, ListSortCallback *callback)
{
	qsort(self->items, self->size, sizeof(void *), *callback);
}

void List_qsort_r(List *self, void *context, ListSortRCallback *callback)
{
	portable_qsort_r(self->items, self->size, sizeof(void *), context, *callback);
}

void *List_bsearch(List *self, const void *key, ListSortCallback *callback)
{
	return bsearch(key, self->items, self->size, sizeof(void *), callback);
}

void *List_first(const List *self)
{
	return List_at_(self, 0);
}

void *List_last(List *self)
{
	return List_at_(self, List_size(self) - 1);
}

// End:  List_inlne

List *List_new(void)
{
	List *self = (List *)io_calloc(1, sizeof(List));
	self->size = 0;
	self->memSize = sizeof(void *)*LIST_START_SIZE;
	self->items = (void **)io_calloc(1, self->memSize);
	return self;
}

List *List_clone(const List *self)
{
	List *child = List_new();
	List_copy_(child, self);
	/*
	 List *child = cpalloc(self, sizeof(List));
	 child->items = cpalloc(self->items, self->memSize);
	 */
	return child;
}

void List_sliceInPlace(List* self, long startIndex, long endIndex, long step)
{
    List *tmp = List_new();
    ssize_t cur;
    size_t i; //, size = List_size(self);
    /* Calculating new list's size. */
    size_t slicesize = abs((int)((step < 0)
                           ? (endIndex - startIndex + 1) / step + 1
                           : (endIndex - startIndex - 1) / step + 1));
    for(cur = startIndex, i = 0; i < slicesize; cur += step, i++)
    {
        List_append_(tmp, List_at_(self, cur));
    }

    List_copy_(self, tmp);
    List_free(tmp);
}

List *List_cloneSlice(const List *self, long startIndex, long endIndex, long step)
{
	List *child = List_clone(self);
	List_sliceInPlace(child, startIndex, endIndex, step);
	return child;
}

void List_free(List *self)
{
	//printf("List_free(%p)\n", (void *)self);
	io_free(self->items);
	io_free(self);
}

UArray List_asStackAllocatedUArray(List *self)
{
	UArray a = UArray_stackAllocedEmptyUArray();
	a.itemType = CTYPE_uintptr_t;
	a.itemSize = sizeof(uintptr_t);
	a.size = self->size;
	a.data = (uint8_t *)(self->items);
	return a;
}

size_t List_memorySize(const List *self)
{
	return sizeof(List) + (self->size * sizeof(void *));
}

void List_removeAll(List *self)
{
	self->size = 0;
	List_compactIfNeeded(self);
}

void List_copy_(List *self, const List *otherList)
{
	if (self == otherList || (!otherList->size && !self->size))
	{
		return;
	}

	List_preallocateToSize_(self, otherList->size);
	memmove(self->items, otherList->items, sizeof(void *) * (otherList->size));
	self->size = otherList->size;
}

int List_equals_(const List *self, const List *otherList)
{
	return (self->size == otherList->size &&
		   memcmp(self->items, otherList->items, sizeof(void *) * self->size) == 0);
}

/* --- sizing ------------------------------------------------ */

void List_setSize_(List *self, size_t index)
{
	List_ifNeededSizeTo_(self, index);
	self->size = index;
}

void List_preallocateToSize_(List *self, size_t index)
{
	size_t s = index * sizeof(void *);

	if (s >= self->memSize)
	{
		size_t newSize = self->memSize * LIST_RESIZE_FACTOR;

		if (s > newSize)
		{
			newSize = s;
		}

		self->items = (void **)io_realloc(self->items, newSize);
		memset(self->items + self->size, 0, (newSize - (self->size*sizeof(void *))));
		self->memSize = newSize;
	}
}

void List_compact(List *self)
{
	self->memSize = self->size * sizeof(void *);
	self->items = (void **)io_realloc(self->items, self->memSize);
}

// -----------------------------------------------------------

void List_print(const List *self)
{
	size_t i;

	printf("List <%p> [%i bytes]\n", (void *)self, (int)self->memSize);

	for (i = 0; i < self->size; i ++)
	{
		printf("%i: %p\n", (int)i, (void *)self->items[i]);
	}

	printf("\n");
}

// enumeration -----------------------------------------

void List_do_(List *self, ListDoCallback *callback)
{
	LIST_FOREACH(self, i, v, if (v) (*callback)(v));
}

void List_do_with_(List *self, ListDoWithCallback *callback, void *arg)
{
	LIST_FOREACH(self, i, v, if (v) (*callback)(v, arg));
}

void List_mapInPlace_(List *self, ListCollectCallback *callback)
{
	void **items = self->items;
	LIST_FOREACH(self, i, v, items[i] = (*callback)(v));
}

List *List_map_(List *self, ListCollectCallback *callback)
{
	List *r = List_new();
	LIST_FOREACH(self, i, v, List_append_(r, (*callback)(v)););
	return r;
}

List *List_select_(List *self, ListSelectCallback *callback)
{
	List *r = List_new();
	LIST_FOREACH(self, i, v, if ((*callback)(v)) List_append_(r, v));
	return r;
}

void *List_detect_(List *self, ListDetectCallback *callback)
{
	LIST_FOREACH(self, i, v, if (v && (*callback)(v)) return v; );
	return NULL;
}

void *List_anyOne(const List *self)
{
	size_t i;

	if (self->size == 0)
	{
		return (void *)NULL;
	}

	if (self->size == 1)
	{
		return LIST_AT_(self, 0);
	}

	i = (rand() >> 4) % (self->size); // without the shift, just get a sequence!

	return LIST_AT_(self, i);
}

void List_shuffle(List *self)
{
	size_t i, j;

	for (i = 0; i < self->size - 1; i ++)
	{
		j = i + rand() % (self->size - i);
		List_swap_with_(self, i, j);
	}
}

void *List_removeLast(List *self)
{
	void *item = List_at_(self, self->size - 1);

	if (item)
	{
		self->size --;
		List_compactIfNeeded(self);
	}

	return item;
}

