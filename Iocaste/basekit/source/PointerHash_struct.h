//  PointerHash.h
//  CuckooHashTable
//  Created by Steve Dekorte on 2009 04 28.

#ifndef POINTERHASH_STRUCT_DEFINED
#define POINTERHASH_STRUCT_DEFINED 1


typedef struct
{
	void *k;
	void *v;
} PointerHashRecord;

typedef struct
{
	unsigned char *records;
	size_t size;
	size_t keyCount;
	intptr_t mask;
} PointerHash;

#endif
