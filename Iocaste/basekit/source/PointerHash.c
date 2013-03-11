//metadoc PointerHash copyright Steve Dekorte 2002
//metadoc PointerHash license BSD revised
//metadoc PointerHash notes Suggestion to use cuckoo hash and original implementation by Marc Fauconneau

#define POINTERHASH_C
#include "PointerHash.h"
#undef POINTERHASH_C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// BEGIN PointerHash_inline

/*
unsigned int PointerHash_hash(PointerHash *self, void *key)
{
	intptr_t k = (intptr_t)PointerHashKey_value(key);
	return k^(k>>4);
}

unsigned int PointerHash_hash_more(PointerHash *self, unsigned int hash)
{
	return hash ^ (hash >> self->log2tableSize);
}
*/

// -----------------------------------

PointerHashRecord *PointerHash_record1_(PointerHash *self, void *k)
{
	// the ~| 0x1 before the mask ensures an odd pos
	intptr_t kk = (intptr_t)k;
	size_t pos = ((kk^(kk>>4)) | 0x1) & self->mask;
	return PointerHashRecords_recordAt_(self->records, pos);
}

PointerHashRecord *PointerHash_record2_(PointerHash *self, void *k)
{
	// the | 0x1 before the mask ensures an even pos
	intptr_t kk = (intptr_t)k;
	//size_t pos = (((kk^(kk/33)) << 1)) & self->mask;
	size_t pos = (kk << 1) & self->mask;
	return PointerHashRecords_recordAt_(self->records, pos);
}

void *PointerHash_at_(PointerHash *self, void *k)
{
	PointerHashRecord *r;

	r = PointerHash_record1_(self, k);
	if(k == r->k) return r->v;

	r = PointerHash_record2_(self, k);
	if(k == r->k) return r->v;

	return 0x0;
}

size_t PointerHash_count(PointerHash *self)
{
	return self->keyCount;
}

int PointerHashKey_hasKey_(PointerHash *self, void *key)
{
	return PointerHash_at_(self, key) != NULL;
}

void PointerHash_at_put_(PointerHash *self, void *k, void *v)
{
	PointerHashRecord *r;

	r = PointerHash_record1_(self, k);

	if(!r->k)
	{
		r->k = k;
		r->v = v;
		self->keyCount ++;
		return;
	}

	if(r->k == k)
	{
		r->v = v;
		return;
	}

	r = PointerHash_record2_(self, k);

	if(!r->k)
	{
		r->k = k;
		r->v = v;
		self->keyCount ++;
		return;
	}

	if(r->k == k)
	{
		r->v = v;
		return;
	}

	{
	PointerHashRecord x;
	x.k = k;
	x.v = v;
	PointerHash_insert_(self, &x);
	}
}

void PointerHash_shrinkIfNeeded(PointerHash *self)
{
	if(self->keyCount < self->size/8)
	{
		PointerHash_shrink(self);
	}
}

void PointerHashRecord_swapWith_(PointerHashRecord *self, PointerHashRecord *other)
{
	PointerHashRecord tmp = *self;
	*self = *other;
	*other = tmp;
}

void PointerHash_clean(PointerHash *self)
{
	memset(self->records, 0, sizeof(PointerHashRecord) * self->size);
	self->keyCount = 0;
}

// END PointerHash_inline

PointerHash *PointerHash_new(void)
{
	PointerHash *self = (PointerHash *)io_calloc(1, sizeof(PointerHash));
	PointerHash_setSize_(self, 8);
	return self;
}

void PointerHash_copy_(PointerHash *self, const PointerHash *other)
{
	io_free(self->records);
	memcpy(self, other, sizeof(PointerHash));
	self->records = malloc(self->size * sizeof(PointerHashRecord));
	memcpy(self->records, other->records, self->size * sizeof(PointerHashRecord));
}

PointerHash *PointerHash_clone(PointerHash *self)
{
	PointerHash *other = PointerHash_new();
	PointerHash_copy_(other, self);
	return other;
}

void PointerHash_setSize_(PointerHash *self, size_t size)
{
	self->records = realloc(self->records, size * sizeof(PointerHashRecord));

	if(size > self->size)
	{
		memset(self->records + self->size * sizeof(PointerHashRecord),
			0x0, (size - self->size) * sizeof(PointerHashRecord));
	}

	self->size = size;

	PointerHash_updateMask(self);
}

void PointerHash_updateMask(PointerHash *self)
{
	self->mask = (intptr_t)(self->size - 1);
}

void PointerHash_show(PointerHash *self)
{
	size_t i;

	printf("PointerHash records:\n");
	for(i = 0; i < self->size; i++)
	{
		PointerHashRecord *r = PointerHashRecords_recordAt_(self->records, i);
		printf("  %i: %p %p\n", (int)i, r->k, r->v);
	}
}

void PointerHash_free(PointerHash *self)
{
	io_free(self->records);
	io_free(self);
}

void PointerHash_insert_(PointerHash *self, PointerHashRecord *x)
{
	int n;

	for (n = 0; n < POINTERHASH_MAXLOOP; n ++)
	{
		PointerHashRecord *r;

		r = PointerHash_record1_(self, x->k);
		PointerHashRecord_swapWith_(x, r);
		if(x->k == 0x0) { self->keyCount ++; return; }

		r = PointerHash_record2_(self, x->k);
		PointerHashRecord_swapWith_(x, r);
		if(x->k == 0x0) { self->keyCount ++; return; }
	}

	PointerHash_grow(self);
	PointerHash_at_put_(self, x->k, x->v);
}

void PointerHash_insertRecords(PointerHash *self, unsigned char *oldRecords, size_t oldSize)
{
	size_t i;

	for (i = 0; i < oldSize; i ++)
	{
		PointerHashRecord *r = PointerHashRecords_recordAt_(oldRecords, i);

		if (r->k)
		{
			PointerHash_at_put_(self, r->k, r->v);
		}
	}
}

void PointerHash_resizeTo_(PointerHash *self, size_t newSize)
{
	unsigned char *oldRecords = self->records;
	size_t oldSize = self->size;
	self->size = newSize;
	self->records = io_calloc(1, sizeof(PointerHashRecord) * self->size);
	self->keyCount = 0;
	PointerHash_updateMask(self);
	PointerHash_insertRecords(self, oldRecords, oldSize);
	io_free(oldRecords);
}

void PointerHash_grow(PointerHash *self)
{
	PointerHash_resizeTo_(self, self->size * 2);
}

void PointerHash_shrink(PointerHash *self)
{
	PointerHash_resizeTo_(self, self->size / 2);
}

void PointerHash_removeKey_(PointerHash *self, void *k)
{
	PointerHashRecord *r;

	r = PointerHash_record1_(self, k);
	if(r->k == k)
	{
		r->k = 0x0;
		r->v = 0x0;
		self->keyCount --;
		PointerHash_shrinkIfNeeded(self);
		return;
	}

	r = PointerHash_record2_(self, k);
	if(r->k == k)
	{
		r->k = 0x0;
		r->v = 0x0;
		self->keyCount --;
		PointerHash_shrinkIfNeeded(self);
		return;
	}
}

size_t PointerHash_size(PointerHash *self) // actually the keyCount
{
	return self->keyCount;
}

// ----------------------------

size_t PointerHash_memorySize(PointerHash *self)
{
	return sizeof(PointerHash) + self->size * sizeof(PointerHashRecord);
}

void PointerHash_compact(PointerHash *self)
{
}
