//metadoc CHash copyright Steve Dekorte 2009
//metadoc CHash license BSD revised
//metadoc CHash notes Suggestion to use cuckoo hash and original implementation by Marc Fauconneau

#define CHASH_C
#include "CHash.h"
#undef CHASH_C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// BEGIN CHash_inline

CHashRecord *CHash_record1_(CHash *self, void *k)
{
	// the ~ | 0x1 before the mask ensures an even pos
	size_t pos = self->hash1(k) & self->mask;
	//printf("pos1 %i/%i\n", pos, self->size);
	return CRecords_recordAt_(self->records, pos);
}

CHashRecord *CHash_record2_(CHash *self, void *k)
{
	// the | 0x1 before the mask ensures an odd pos
	size_t pos = self->hash2(k) & self->mask;
	//printf("pos2 %i/%i\n", pos, self->size);
	return CRecords_recordAt_(self->records, pos);
}

void *CHash_at_(CHash *self, void *k)
{
	CHashRecord *r;

	 r = CHash_record1_(self, k);

	if(r->k && self->equals(k, r->k))
	{
		return r->v;
	}

	r = CHash_record2_(self, k);

	if(r->k && self->equals(k, r->k))
	{
		return r->v;
	}

	return 0x0;
}

size_t CHash_count(CHash *self)
{
	return self->keyCount;
}

int CHashKey_hasKey_(CHash *self, void *key)
{
	return CHash_at_(self, key) != NULL;
}

int CHash_at_put_(CHash *self, void *k, void *v)
{
	CHashRecord *r;

	r = CHash_record1_(self, k);

	if(!r->k)
	{
		r->k = k;
		r->v = v;
		self->keyCount ++;
		return 0;
	}

	if(k == r->k || self->equals(k, r->k))
	{
		r->v = v;
		return 0;
	}

	r = CHash_record2_(self, k);

	if(!r->k)
	{
		r->k = k;
		r->v = v;
		self->keyCount ++;
		return 0;
	}

	if(k == r->k || self->equals(k, r->k))
	{
		r->v = v;
		return 0;
	}


	{
		CHashRecord x;
		x.k = k;
		x.v = v;
		return CHash_insert_(self, &x);
	}
}

void CHash_shrinkIfNeeded(CHash *self)
{
	if(self->keyCount < self->size/5)
	{
		CHash_shrink(self);
	}
}

void CHashRecord_swapWith_(CHashRecord *self, CHashRecord *other)
{
	CHashRecord tmp = *self;
	*self = *other;
	*other = tmp;
}

void CHash_clean(CHash *self)
{
	memset(self->records, 0, sizeof(CHashRecord) * self->size);
	self->keyCount = 0;
}

// END CHash_inline

CHash *CHash_new(void)
{
	CHash *self = (CHash *)io_calloc(1, sizeof(CHash));
	CHash_setSize_(self, 8);
	return self;
}

void CHash_copy_(CHash *self, const CHash *other)
{
	io_free(self->records);
	memcpy(self, other, sizeof(CHash));
	self->records = (unsigned char*)malloc(self->size * sizeof(CHashRecord));
	memcpy(self->records, other->records, self->size * sizeof(CHashRecord));
}

CHash *CHash_clone(CHash *self)
{
	CHash *other = CHash_new();
	CHash_copy_(other, self);
	return other;
}

void CHash_setSize_(CHash *self, size_t size)
{
	self->records = (unsigned char*)realloc(self->records, size * sizeof(CHashRecord));

	if(size > self->size)
	{
		memset(self->records + self->size * sizeof(CHashRecord),
			0x0, (size - self->size) * sizeof(CHashRecord));
	}

	self->size = size;

	CHash_updateMask(self);
	//CHash_show(self);
}

void CHash_updateMask(CHash *self)
{
	self->mask = (intptr_t)(self->size - 1);
}

void CHash_show(CHash *self)
{
	size_t i;

	printf("CHash records:\n");
	for(i = 0; i < self->size; i++)
	{
		CHashRecord *r = CRecords_recordAt_(self->records, i);
		printf("  %i: %p %p\n", (int)i, r->k, r->v);
	}
}

void CHash_free(CHash *self)
{
	io_free(self->records);
	io_free(self);
}

void CHash_setHash1Func_(CHash *self, CHashHashFunc *f)
{
	self->hash1 = f;
}

void CHash_setHash2Func_(CHash *self, CHashHashFunc *f)
{
	self->hash2 = f;
}

void CHash_setEqualFunc_(CHash *self, CHashEqualFunc *f)
{
	self->equals = f;
}

int CHash_insert_(CHash *self, CHashRecord *x)
{
	int n;

	for (n = 0; n < CHASH_MAXLOOP; n ++)
	{
		CHashRecord *r;

		//pos = self->hash1(x->k) & self->mask;
		//printf("1 x->k = %p-> %i\n", x->k, pos);
		r = CHash_record1_(self, x->k);
		CHashRecord_swapWith_(x, r); //x ↔ T1 [h1 (x)]
		if(x->k == 0x0) { self->keyCount ++; return 0; }

		//pos = self->hash2(x->k) & self->mask;
		//printf("2 x->k = %p-> %i\n\n", x->k, pos);
		r = CHash_record2_(self, x->k);
		CHashRecord_swapWith_(x, r); //x ↔ T2 [h2 (x)]
		if(x->k == 0x0) { self->keyCount ++; return 0; }
	}

	if(self->isResizing)
	{
		return -1;
	}

	CHash_grow(self);
	CHash_at_put_(self, x->k, x->v);
	return 0;
}

int CHash_insertRecords(CHash *self, unsigned char *oldRecords, size_t oldSize)
{
	size_t i;

	for (i = 0; i < oldSize; i ++)
	{
		CHashRecord *r = CRecords_recordAt_(oldRecords, i);

		if (r->k)
		{
			if(CHash_at_put_(self, r->k, r->v)) return 1;
		}
	}
	return 0;
}

int CHash_resizeTo_(CHash *self, size_t newSize)
{
	unsigned char *oldRecords = self->records;
	size_t oldSize = self->size;

	self->isResizing = 1;

	//printf("%p resizeTo %i/%i %i%%\n", (void *)self, self->keyCount, self->size, (int)(100.0*CHash_density(self)));

	do
	{
		self->size = newSize;
		self->records = (unsigned char*)io_calloc(1, sizeof(CHashRecord) * self->size);
		self->keyCount = 0;
		CHash_updateMask(self);
		if(CHash_insertRecords(self, oldRecords, oldSize) == 0)
		{
			self->isResizing = 0;
		}
		else
		{
			//printf("%p grow collision %i/%i\n", (void *)self, self->keyCount, self->size);
			newSize *= 2;
			io_free(self->records);
		}
	} while(self->isResizing);

	io_free(oldRecords);
	return 0;
}

void CHash_grow(CHash *self)
{
	CHash_resizeTo_(self, self->size * 2);
}

void CHash_shrink(CHash *self)
{
	//printf("%p shrink %i/%i\n", (void *)self, self->keyCount, self->size);
	//CHash_resizeTo_(self, self->size / 2);
}

void CHash_removeKey_(CHash *self, void *k)
{
	CHashRecord *r1 = CHash_record1_(self, k);
	CHashRecord *r2;

	if(r1->k && self->equals(k, r1->k))
	{
		r1->k = 0x0;
		r1->v = 0x0;
		self->keyCount --;
		CHash_shrinkIfNeeded(self);
		return;
	}

	r2 = CHash_record2_(self, k);

	if(r2->k && self->equals(k, r2->k))
	{
		r2->k = 0x0;
		r2->v = 0x0;
		self->keyCount --;
		CHash_shrinkIfNeeded(self);
		return;
	}
}

void CHash_clear(CHash *self)
{
	memset(self->records, 0x0, self->size * sizeof(CHashRecord));
	self->keyCount = 0;
	CHash_shrinkIfNeeded(self);
}

size_t CHash_size(CHash *self) // actually the keyCount
{
	return self->keyCount;
}

// ----------------------------

size_t CHash_memorySize(CHash *self)
{
	return sizeof(CHash) + self->size * sizeof(CHashRecord);
}

void CHash_compact(CHash *self)
{
}

float CHash_density(CHash *self)
{
	float kc = (float)self->keyCount;
	float size = (float)self->size;
	return kc/size;
}

