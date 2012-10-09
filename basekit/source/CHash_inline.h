//metadoc CHash copyright Steve Dekorte 2009
//metadoc CHash license BSD revised
/*metadoc CHash description
	CHash - Cuckoo Hash
	keys and values are references (they are not copied or freed)
*/

#include "Common_inline.h"

#define CRecords_recordAt_(records, pos) (CHashRecord *)(records + (pos * sizeof(CHashRecord)))

CHashRecord *CHash_record1_(CHash *self, void *k);
CHashRecord *CHash_record2_(CHash *self, void *k);
void *CHash_at_(CHash *self, void *k);
size_t CHash_count(CHash *self);
int CHashKey_hasKey_(CHash *self, void *key);
int CHash_at_put_(CHash *self, void *k, void *v);
void CHash_shrinkIfNeeded(CHash *self);
void CHashRecord_swapWith_(CHashRecord *self, CHashRecord *other);
void CHash_clean(CHash *self);

// --- enumeration --------------------------------------------------

#define CHASH_FOREACH(self, pkey, pvalue, code) \
{\
	CHash *_self = (self);\
	unsigned char *_records = _self->records;\
	size_t _i, _size = _self->size;\
	void *pkey;\
	void *pvalue;\
	\
	for (_i = 0; _i < _size; _i ++)\
	{\
		CHashRecord *_record = CRecords_recordAt_(_records, _i);\
		if (_record->k)\
		{\
			pkey = _record->k;\
			pvalue = _record->v;\
			code;\
		}\
	}\
}

