//metadoc List copyright Steve Dekorte 2002
//metadoc List license BSD revised
/*metadoc List description
List is an array of void pointers.
The List is not responsible for io_freeing it's elements.
*/

#include "Common_inline.h"
#include "PortableSorting.h"

#define LIST_FOREACH(list, index, value, code) \
{ \
	const List *foreachList = list; \
	size_t index, foreachMax = foreachList->size; \
	\
	for (index = 0; index < foreachMax; index ++) \
	{ \
		void *value = foreachList->items[index]; \
		code; \
	} \
}

#define LIST_SAFEFOREACH(list, index, value, code) \
{ \
	const List *foreachList = list; \
	size_t index; \
	\
	for (index = 0; index < List_size(foreachList); index ++) \
	{ \
		void *value = List_at_(foreachList, index); \
		code; \
	} \
}

#define LIST_REVERSEFOREACH(list, index, value, code) \
{ \
	const List *foreachList = list; \
	size_t index = List_size(foreachList); \
	\
	while (index) \
	{ \
		void *value = List_at_(foreachList, (index --)); \
		code; \
	} \
}

#define LIST_SAFEREVERSEFOREACH(list, index, value, code) \
{ \
	const List *foreachList = list; \
	size_t index = List_size(foreachList); \
	\
	for (index = List_size(foreachList) - 1; index > 0; index --) \
	{ \
		void *value = List_at_(foreachList, index); \
		code; \
		if (index > List_size(foreachList) - 1) { index = List_size(foreachList) - 1; } \
	} \
}

#define LIST_DO_(list, func) \
{ \
	const List *foreachList = list; \
	size_t index, foreachMax = List_size(foreachList); \
	\
	for (index = 0; index < foreachMax; index ++) \
	{ \
		func(List_at_(foreachList, index)); \
	} \
}

size_t List_size(const List *self);
void List_ifNeededSizeTo_(List *self, size_t newSize);
void *List_rawAt_(List *self, size_t index);
void *List_at_(const List *self, ssize_t index);
size_t List_indexOf_(List *self, void *item);
int List_contains_(List *self, void *item);
void *List_append_(List *self, void *item);
void List_appendSeq_(List *self, const List *otherList);
void List_compactIfNeeded(List *self);
void List_removeIndex_(List *self, size_t index);
void List_removeIndex_toIndex_(List *self, size_t index1, size_t index2);
void List_remove_(List *self, void *item);
int List_removeFirst_(List *self, void *item);
void List_removeLast_(List *self, void *item);
void List_removeItems_(List *self, List *other);
void List_at_insert_(List *self, size_t index, void *item);
void List_at_put_(List *self, size_t index, void *item);
void List_swap_with_(List *self, long index1, long index2);
void List_reverseInPlace(List *self);

// stack --------------------------------------------------

void List_push_(List *self, void *item);
void *List_pop(List *self);
void *List_top(const List *self);

/* --- perform -------------------------------------------------- */

int List_removeTrueFor_(List *self, ListCollectCallback* callback);
void List_qsort(List *self, ListSortCallback *callback);
void List_qsort_r(List *self, void *context, ListSortRCallback *callback);
void *List_bsearch(List *self, const void *key, ListSortCallback *callback);
void *List_first(const List *self);
void *List_last(List *self);
