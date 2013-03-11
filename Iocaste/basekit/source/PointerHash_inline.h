//metadoc PointerHash copyright Steve Dekorte 2002, Marc Fauconneau 2007
//metadoc PointerHash license BSD revised
/*metadoc PointerHash description
	PointerHash - Cuckoo Hash
	keys and values are references (they are not copied or freed)
	key pointers are assumed unique
*/

#include "Common_inline.h"

#define PointerHashRecords_recordAt_(records, pos) (PointerHashRecord *)(records + (pos * sizeof(PointerHashRecord)))

/*
unsigned int PointerHash_hash(PointerHash *self, void *key)
unsigned int PointerHash_hash_more(PointerHash *self, unsigned int hash)
*/

// -----------------------------------

PointerHashRecord *PointerHash_record1_(PointerHash *self, void *k);
PointerHashRecord *PointerHash_record2_(PointerHash *self, void *k);
void *PointerHash_at_(PointerHash *self, void *k);
size_t PointerHash_count(PointerHash *self);
int PointerHashKey_hasKey_(PointerHash *self, void *key);
void PointerHash_at_put_(PointerHash *self, void *k, void *v);
void PointerHash_shrinkIfNeeded(PointerHash *self);
void PointerHashRecord_swapWith_(PointerHashRecord *self, PointerHashRecord *other);
void PointerHash_clean(PointerHash *self);

// --- enumeration --------------------------------------------------

#define POINTERHASH_FOREACH(self, pkey, pvalue, code) \
{\
	PointerHash *_self = (self);\
	unsigned char *_records = _self->records;\
	size_t _i, _size = _self->size;\
	void *pkey;\
	void *pvalue;\
	\
	for (_i = 0; _i < _size; _i ++)\
	{\
		PointerHashRecord *_record = PointerHashRecords_recordAt_(_records, _i);\
		if (_record->k)\
		{\
			pkey = _record->k;\
			pvalue = _record->v;\
			code;\
		}\
	}\
}

